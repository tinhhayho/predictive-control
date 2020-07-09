//###########################################################################
//
// FILE:	F2806x_Sci.c
//
// TITLE:	F2806x SCI Initialization & Support Functions.
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
// InitSci:
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{
    // 1 stop bit, no loopback
    // no parity, 8 char bit
    // idle-line mode protocol selected
    SciaRegs.SCICCR.all = 0x0007;
    //enable TX, RX, internal SCICLK
    //Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL1.all = 0x0003;
    // ngat nhan moi byte va ngat truyen ca 1 dong byte
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;
    SciaRegs.SCIFFTX.bit.TXFFIENA = 1;
    //9600
    SciaRegs.SCIHBAUD = 0x0001;
    SciaRegs.SCILBAUD = 0x0024;
    // enable FIFO 
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all  = 0x0;
    // Relinquish SCI from Reset
    SciaRegs.SCICTL1.all = 0x0023;
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET =1;
}
void SciEnable(void)
{
        // enable sci
    SciaRegs.SCICTL1.bit.TXENA =1;
    SciaRegs.SCICTL1.bit.RXENA = 1;
    SciaRegs.SCICTL1.bit.SWRESET =1;
}

void SciDisable(void)
{
    
    // wait for end of tx  == (txempty==1) 
    while (SciaRegs.SCICTL2.bit.TXEMPTY)
    {
    }
    // disable the FIFO

    // disable the UART
    
}

//---------------------------------------------------------------------------
// Example: InitSciGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation.
// Comment out other unwanted lines.


void scia_xmit(int a)
{
    // doi fifo emty roi moi truyen vao ki tu moi
    while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
    SciaRegs.SCITXBUF = a;
}

void scia_msg(char *msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}


void scia_fifo_init(void)
{
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all  = 0x0;
}


//===========================================================================
// End of file.
//===========================================================================
