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
//###########################################################################

#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

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

   // Each GPIO pin can be:
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs
   GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0; // enable pullup on GPIO34
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34  = GPIO34
   GpioDataRegs.GPBSET.bit.GPIO34 = 1; // output latch  = high
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1; // GPIO34 = output
   //
   GpioCtrlRegs.GPBPUD.bit.GPIO39 = 0; // enable pullup on GPIO34
   GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0; // GPIO34  = GPIO34
   GpioDataRegs.GPBSET.bit.GPIO39 = 0; // output latch  = high
   GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1; // GPIO34 = output
   //
   EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
