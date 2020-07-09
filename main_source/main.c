//###########################################################################
// Description:
//! \addtogroup f2806x_example_list
//! <h1>GPIO Setup (gpio_setup)</h1>
//!
//! This example Configures the 2806x GPIO into two different configurations
//! This code is verbose to illustrate how the GPIO could be setup.In a real
//! application, lines of code can be combined for improved code size and 
//! efficiency.
//!
//! This example only sets-up the GPIO.. nothing is actually done with
//! the pins after setup.
//!
//! In general:
//!   - All pullup resistors are enabled.  For ePWMs this may not be desired.
//!   - Input qual for communication ports (eCAN, SPI, SCI, I2C) is asynchronous
//!   - Input qual for Trip pins (TZ) is asynchronous
//!   - Input qual for eCAP and eQEP signals is synch to SYSCLKOUT
//!   - Input qual for some I/O's and interrupts may have a sampling window
//
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <math.h>
// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
Uint16   LoopCount = 0;
Uint16   ErrorCount = 0;
Uint16   AdcValue1, AdcValue2, AdcValue3, AdcValue4;

Clarke_infor clarke = \
{
   {1.0f, 1.0f, 1.0f}, // i adc
   {0.0f ,0.0f, 0.0f}, // i(k+1)
   {0.0f, 0.0f}, // i transform
   {0.0f, 0.0f}, // i(k+1) transform
   {50.0f ,50.0f}, // uc adc
   {0.0f, 0.0f} // uc(k+1)
};
Clarke_infor *Pclarke = &clarke;
State_info state = \
{
   {0.0f ,0.0f}, // i(k+2) ref
   {0.0f, 0.0f}, // i(k+2) predictive
   1,        // state
   {0.0f, 0.0f} // uc(k+2)
} ;
State_info *Pstate = &state;
Control_signal csignal = \
{
   1,
   0.0f
};
Control_signal *PCsignal = &csignal;

extern float32 Vreal[27];
extern float32 Vimag[27];
extern Uint16  output_signal[27][6];
extern Uint16 state_p_n[27][6];
Uint16 Vdc = 100;
Uint16 counter = 0;
/*
    he so (1 - R*Ts/L)
    he so (Ts /L)
    he so (Ts/C)
*/
float32 coefficient1 = 0.99; // modify when run
float32 coefficient2 = 0.0016666666f;
float32 coefficient3 = 0.022727272727f;
float32 g_opt  ;
// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void SciaTxFifoIsr(void);
__interrupt void SciaRxFifoIsr(void);
__interrupt void AdcInt1Isr(void);
__interrupt void AdcInt2Isr(void);
void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2806x_SysCtrl.c file.
   InitSysCtrl();
// Step 2. Initalize GPIO:
// This example function is found in the F2806x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   // InitGpio(); Skipped for this example
   InitGpio();
// Step 3. Clear all interrupts and initialize PIE vector table:
// please refer to page 170 technical manual
// Disable CPU interrupts ( global interrupt)
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2806x_DefaultIsr.c.
// This function is found in F2806x_PieVect.c.
   InitPieVectTable();
   // re-mapping vector interrupt
   EALLOW;
   PieVectTable.TINT0 = &cpu_timer0_isr;
   PieVectTable.SCIRXINTA =&SciaRxFifoIsr;
   PieVectTable.SCITXINTA = &SciaTxFifoIsr;
   PieVectTable.ADCINT1 = &AdcInt1Isr;
   PieVectTable.ADCINT2 = &AdcInt2Isr;
   EDIS;

   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
   InitFlash();
// Step 4. Initialize all the Device Peripherals:
// This function is found in F2806x_InitPeripherals.c
   InitCpuTimers();
//   ConfigCpuTimer(&CpuTimer0, 90, 1000000);
   InitSci();
   InitAdc();
//   ConfigCpuTimer(&CpuTimer0, 90, 1000000);
//  config interrupt
   // periphral level
/*
   da duoc modify trong step 4 
*/
   // PIE level
   PieCtrlRegs.PIEIER1.bit.INTx7 =  1; // cpu timer 0
   PieCtrlRegs.PIEIER9.bit.INTx1 = 1; //scia rxd
   PieCtrlRegs.PIEIER9.bit.INTx2 = 1; // scia txd
   PieCtrlRegs.PIEIER1.bit.INTx2 =1;
   PieCtrlRegs.PIEIER1.bit.INTx1 =1;
   // CPU level
   IER |= M_INT1|M_INT9;
   // ENABLE GLOBAL INTERRUPT
   EINT;
   ERTM;
// Step 5. User specific code:
Uint32 timer;
int dem =0;
   // START TIMER0
   CpuTimer0Regs.TCR.bit.TSS = 0;
//   CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
   while(1 /*thay bang dieu kien adc complete  */)
       {
          if (counter >= 400) { counter = 0;}
          g_opt = 3.40282347e+38F;
          
          /*
          to Predictive I*(k+1)
          lookup table 
          caculate sinf and cosf
          iref(k+2) =  sinf( t_current + 2*Ts)
          */

         //Pstate->Iclarke2_r[0] = sinf(counter*0.00005f + 0.0001f);
         //Pstate->Iclarke2_r[0] = sinf(counter*0.00005f + 0.0001f);
         // bien doi clarke - 2 sensor 3 pha can bang
         Pclarke->Iclarke[0] = Pclarke->I[0];  // iamphe  = ia
         Pclarke->Iclarke[1] = 0.5773502692f*Pclarke->I[0] + 1.154700538f*Pclarke->I[1] ;
         // du doan k + 1 cua i (amphabeta)
         Pclarke->Iclarke1[0] = coefficient1*Pclarke->Iclarke[0] + coefficient2*Vreal[PCsignal->state_v]*Vdc;
         Pclarke->Iclarke1[1] = coefficient1*Pclarke->Iclarke[1] + coefficient2*Vimag[PCsignal->state_v]*Vdc;
         // du doan k + 1 cua uc
         Pclarke->Uc1[0] = Pclarke->Uc[0] + \
         coefficient3*(-state_p_n[Pstate->state_i][0]*Pclarke->I[0]  \
                       -state_p_n[Pstate->state_i][2]*Pclarke->I[1]  \
                       -state_p_n[Pstate->state_i][4]*Pclarke->I[2]);
         //
         Pclarke->Uc1[1] = Pclarke->Uc[1] + \
         coefficient3*(state_p_n[Pstate->state_i][1]*Pclarke->I[0] + \
                       state_p_n[Pstate->state_i][3]*Pclarke->I[1] + \
                       state_p_n[Pstate->state_i][5]*Pclarke->I[2]);
         // du doan k +1 cua i (abc)
         Pclarke->I1[0] = Pclarke->Iclarke1[0];
         Pclarke->I1[1] = -0.5f*Pclarke->Iclarke1[0] + 0.8660254038f*Pclarke->Iclarke1[1];
         Pclarke->I1[2] = -0.5f*Pclarke->Iclarke1[0] - 0.8660254038f*Pclarke->Iclarke1[1];
         int i ;
         // tim g toi uu
         for (i = 0; i < 27; i++)
         {
            // dong dien
            Pstate->Iclarke2_p[0] = coefficient1*Pclarke->Iclarke1[0] + \
                                    coefficient2*Vreal[i]*Vdc;
            Pstate->Iclarke2_p[1] = coefficient1*Pclarke->Iclarke1[1] + \
                                    coefficient2*Vimag[i]*Vdc;     
            // dien ap tu
            Pstate->Uc2[0] = Pclarke->Uc1[0] + \
            coefficient3*(-state_p_n[i][0]*Pclarke->I1[0] - \
                           state_p_n[i][2]*Pclarke->I1[1] - \
                           state_p_n[i][4]*Pclarke->I1[2]);  
            Pstate->Uc2[1] = Pclarke->Uc1[1] + \
            coefficient3*( state_p_n[i][1]*Pclarke->I1[0] + \
                           state_p_n[i][3]*Pclarke->I1[1] + \
                           state_p_n[i][5]*Pclarke->I1[2]);  
            // ham muc tieu
            PCsignal->g = fabsf(Pstate->Iclarke2_r[0] - Pstate->Iclarke2_p[0]) + \
                fabsf(Pstate->Iclarke2_r[1] - Pstate->Iclarke2_p[1]) + \
                fabsf(Pstate->Uc2[1] - Pstate->Uc2[0]);
                if (PCsignal->g < g_opt) { g_opt = PCsignal->g; PCsignal->state_v = i ;}
         }
         __asm ("      ESTOP0");
         if(dem ==0) { timer = CpuTimer0Regs.TIM.all ; dem++;}
       }
}

// interrupt service routing
__interrupt void cpu_timer0_isr(void)
{
    CpuTimer0.InterruptCount++;
    GpioDataRegs.GPBTOGGLE.bit.GPIO34 =1;
    GpioDataRegs.GPBTOGGLE.bit.GPIO39 = 1;
    // thong bao ngat nay de co the tiep tuc nhan them ngat
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
 __interrupt void SciaTxFifoIsr(void)
 {

 }
 __interrupt void SciaRxFifoIsr(void)
 {

 }
__interrupt void AdcInt1Isr(void)
{
   // chep ket qua convert
   AdcValue1 = AdcResult.ADCRESULT0;
   AdcValue2 = AdcResult.ADCRESULT1;
   // kich hoat SOC2
   AdcRegs.ADCSOCFRC1.bit.SOC2 = 1;

   // clear ADCINT1 flag for next SOC
   AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
   // acknowledge interrupt to PIE
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}
__interrupt void AdcInt2Isr(void)
{
   AdcValue3 = AdcResult.ADCRESULT2;
   AdcValue4 = AdcResult.ADCRESULT3;
   // clear ADCINT1 flag for next SOC
   AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
   // acknowledge interrupt to PIE
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//===========================================================================
// No more.
//===========================================================================

