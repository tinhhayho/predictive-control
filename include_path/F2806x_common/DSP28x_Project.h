
//###########################################################################
//
// FILE:   DSP28x_Project.h
//
// TITLE:  DSP28x Project Headerfile and Examples Include File
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $
// $Release Date: February  2, 2016 $
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef DSP28x_PROJECT_H
#define DSP28x_PROJECT_H

#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions
#include "F2806x_Device.h"      // F2806x Headerfile Include File
#include "F2806x_Examples.h"   	// F2806x Examples Include File
typedef struct ClarkeInFor
{
   float32 I[3] ;  // cap nhat boi ADC
   float32 I1[3];
   float32 Iclarke[2];  // cap nhat trong qua trinh uoc luong
   float32 Iclarke1[2]; // qua trinh uoc luong
   float32 Uc[2]; // cap nhat boi ADC
   float32 Uc1[2]; // qua trinh uoc luong
} Clarke_infor;

typedef struct StateInFor
{
   float32 Iclarke2_r[2]; 
   float32 Iclarke2_p[2];
   Uint16 state_i;
   float32 Uc2[2];
} State_info;

typedef struct ControlSignal
{
   Uint16 state_v; // vectro khong gian thu may
   float32 g;
} Control_signal;
#endif  // end of DSP28x_PROJECT_H definition

