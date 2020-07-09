//###########################################################################
//
// FILE:	F2806x_Gpio.c
//
// TITLE:	F2806x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
// modify again : NGUYEN TRUNG TINH
// email : tinhhayho@gmail.com
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
//#include "F2806x_Examples.h"   // F2806x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
   EALLOW;

   // Each GPIO pin are:
   // a) a GPIO output : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
   // b) SCIA PIN 7 AND PIN 12
   // c) ADCINA1, ADCINA2, ADCINB1, ADCINB2
   // d)
   // By default, all are GPIO Inputs
   // GPIO for control IGBT
   GpioCtrlRegs.GPAPUD.all |= 0x00000FFF;
   GpioCtrlRegs.GPAMUX1.all |= 0x00FFFFFF;
   GpioDataRegs.GPACLEAR.all |= 0x00000FFF;
   GpioCtrlRegs.GPADIR.all |= 0x00000FFF;
   //test cpu_timer, use c2000 lauchPad led d10 and led d9
   GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0; // enable pullup on GPIO34
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34  = GPIO34
   GpioDataRegs.GPBSET.bit.GPIO34 = 1; // output latch  = high
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; // GPIO34 = output
   GpioCtrlRegs.GPBPUD.bit.GPIO39 = 0; // enable pullup on GPIO34
   GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO34  = GPIO34
   GpioDataRegs.GPBSET.bit.GPIO39 = 0; // output latch  = high
   GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1; // GPIO34 = output
   // scia configure
   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
   GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 3; // asynch input GPIO7 (SCIRXDA)
   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2; // configure GPIO7 for SCIRXDA
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2; // configrue GPIO12 for SCITXDA

   //adc gipo configure refer to page 130 
   //disable het ta ca cac AIO khhong su dung 2/4/6/10/12/14
   GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;
   GpioCtrlRegs.AIOMUX1.bit.AIO4 = 2;
   GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;
   GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;
   GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;
   GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;

   EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
