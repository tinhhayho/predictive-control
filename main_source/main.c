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

// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
__interrupt void cpu_timer0_isr(void);

// Prototype statements for functions found within this file.
void Gpio_setup1(void);


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
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2806x_PieCtrl.c file.
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
   EDIS;


// Step 4. Initialize all the Device Peripherals:
// This function is found in F2806x_InitPeripherals.c
   InitCpuTimers();
   ConfigCpuTimer(&CpuTimer0, 90, 1000000);
// config interrupt
   // periphral level
   CpuTimer0Regs.TCR.all = 0x4000;

   // PIE level
   PieCtrlRegs.PIEIER1.bit.INTx7 =  1;

   // CPU level
   IER |= M_INT1;
   // ENABLE GLOBAL INTERRUPT
   EINT;
   ERTM;
// Step 5. User specific code:

   while(1);
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
//===========================================================================
// No more.
//===========================================================================

