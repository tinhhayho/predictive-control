//###########################################################################
//
// FILE:   F2806x_Sci.h
//
// TITLE:  F2806x Device SCI Register Definitions.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V151 $   
// $Release Date: February  2, 2016 $   
// $Copyright: Copyright (C) 2011-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
// modify again : Nguyen Trung Tinh
// 7/2020
//###########################################################################

#ifndef F2806x_SCI_H
#define F2806x_SCI_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// SCI Individual Register Bit Definitions:

struct SCICCR_BITS {     // bits description
	Uint16	SCICHAR:3;			// 2:0	Character length control
	Uint16	ADDRIDLE_MODE:1;	// 3	ADDR/IDLE Mode control
	Uint16	LOOPBKENA:1;		// 4	Loop Back enable
	Uint16	PARITYENA:1;		// 5	Parity enable
	Uint16	PARITY:1;			// 6	Even or Odd Parity
	Uint16	STOPBITS:1;			// 7	Number of Stop Bits
	Uint16	rsvd1:8;			// 15:8	Reserved
};

union SCICCR_REG {
	Uint16 all;
	struct SCICCR_BITS	bit;
};

struct SCICTL1_BITS {     // bits description
	Uint16	RXENA:1;			// 0	SCI receiver enable
	Uint16	TXENA:1;			// 1	SCI transmitter enable
	Uint16	SLEEP:1;			// 2	SCI sleep
	Uint16	TXWAKE:1;			// 3	Transmitter wakeup method
	Uint16	rsvd1:1;			// 4	Reserved
	Uint16	SWRESET:1;			// 5	Software reset
	Uint16	RXERRINTENA:1;		// 6	Recieve interrupt enable
	Uint16	rsvd2:9;			// 15:7	Reserved
};

union SCICTL1_REG {
	Uint16 all;
	struct SCICTL1_BITS	bit;
};

struct SCICTL2_BITS {     // bits description
	Uint16	TXINTENA:1;			// 0	Transmit interrupt enable
	Uint16	RXBKINTENA:1;		// 1	Receiver-buffer break enable
	Uint16	rsvd1:4;			// 5:2	Reserved
	Uint16	TXEMPTY:1;			// 6	Transmitter empty flag
	Uint16	TXRDY:1;			// 7	Transmitter ready flag
	Uint16	rsvd2:8;			// 15:8	Reserved
};

union SCICTL2_REG {
	Uint16 all;
	struct SCICTL2_BITS	bit;
};

struct SCIRXST_BITS {     // bits description
	Uint16	rsvd1:1;		// 0	Reserved
	Uint16	RXWAKE:1;		// 1	Receiver wakeup detect flag
	Uint16	PE:1;			// 2	Parity error flag
	Uint16	OE:1;			// 3	Overrun error flag
	Uint16	FE:1;			// 4	Framing error flag
	Uint16	BRKDT:1;		// 5	Break-detect flag
	Uint16	RXRDY:1;		// 6	Receiver ready flag
	Uint16	RXERROR:1;		// 7	Receiver error flag
	Uint16	rsvd2:8;		// 15:8	Reserved
};

union SCIRXST_REG {
	Uint16 all;
	struct SCIRXST_BITS	bit;
};

struct SCIRXBUF_BITS {     // bits description
	Uint16	RXDT:8;			// 7:0  	Receive word
	Uint16	rsvd1:6;		// 13:8	Reserved
	Uint16	SCIFFPE:1;		// 14 	SCI PE error in FIFO mode
	Uint16	SCIFFFE:1;		// 15	SCI FE error in FIFO mode
};

union SCIRXBUF_REG {
	Uint16 all;
	struct SCIRXBUF_BITS	bit;
};

struct SCIFFTX_BITS {     // bits description
	Uint16	TXFFIL:5;			// 4:0	Interrupt level
	Uint16	TXFFIENA:1;			// 5	Interrupt enable
	Uint16	TXFFINTCLR:1;		// 6	Clear INT flag
	Uint16	TXFFINT:1;			// 7	INT flag
	Uint16	TXFFST:5;			// 12:8	FIFO status
	Uint16	TXFIFOXRESET:1;		// 13	FIFO reset
	Uint16	SCIFFENA:1;			// 14	Enhancement enable
	Uint16	SCIRST:1;			// 15	SCI reset rx/tx channels
};

union SCIFFTX_REG {
	Uint16 all;
	struct SCIFFTX_BITS	bit;
};

struct SCIFFRX_BITS {     // bits description
	Uint16	RXFFIL:5;			// 4:0	Interrupt level
	Uint16	RXFFIENA:1;			// 5	Interrupt enable
	Uint16	RXFFINTCLR:1;		// 6	Clear INT flag
	Uint16	RXFFINT:1;			// 7	INT flag
	Uint16	RXFFST:5;			// 12:8 	FIFO status
	Uint16	RXFIFORESET:1;		// 13	FIFO reset
	Uint16	RXFFOVRCLR:1;		// 14	Clear overflow
	Uint16	RXFFOVF:1;			// 15	FIFO overflow
};

union SCIFFRX_REG {
	Uint16 all;
	struct SCIFFRX_BITS	bit;
};

struct SCIFFCT_BITS {     // bits description
	Uint16	FFTXDLY:8;		// 7:0	FIFO transmit delay
	Uint16	rsvd1:5;		// 12:8	Reserved
	Uint16	CDC:1;			// 13	Auto baud mode enable
	Uint16	ABDCLR:1;		// 14	Auto baud clear
	Uint16	ABD:1;			// 15	Auto baud detect
};

union SCIFFCT_REG {
	Uint16 all;
	struct SCIFFCT_BITS	bit;
};

struct SCIPRI_BITS {     // bits description
	Uint16	rsvd1:3;		// 2:0	Reserved
	Uint16	FREE:1;			// 3	Free emulation suspend mode
	Uint16	SOFT:1;			// 4	Soft emulation suspend mode
	Uint16	rsvd2:3;		// 7:5	Reserved
	Uint16	rsvd3:8;		// 15:8	Reserved
};

union SCIPRI_REG {
	Uint16 all;
	struct SCIPRI_BITS	bit;
};

struct SCI_REGS {
	union	SCICCR_REG		SCICCR;		// Communications control register
	union	SCICTL1_REG		SCICTL1;	// Control register 1
	Uint16	SCIHBAUD;					// Baud rate (high) register
	Uint16	SCILBAUD;					// Baud rate (low) register
	union	SCICTL2_REG		SCICTL2;	// Control register 2
	union	SCIRXST_REG		SCIRXST;	// Recieve status register
	Uint16					SCIRXEMU;	// Recieve emulation buffer register
	union	SCIRXBUF_REG	SCIRXBUF;	// Recieve data buffer
	Uint16					rsvd1;		// Reserved
	Uint16					SCITXBUF;	// Transmit data buffer
	union	SCIFFTX_REG		SCIFFTX;	// FIFO transmit register
	union	SCIFFRX_REG		SCIFFRX;	// FIFO recieve register
	union	SCIFFCT_REG		SCIFFCT;	// FIFO control register
	Uint16					rsvd2;		// Reserved
	Uint16					rsvd3;		// Reserved
	union	SCIPRI_REG		SCIPRI;		// FIFO Priority control
};
// user declarations 
// based on uart.h drivelib
/*
	please contact tinhhayho@gmail.com for more details(2020)

*/
//*****************************************************************************
//
// Values that can be passed to UARTIntEnable, UARTIntDisable, and UARTIntClear
// as the ulIntFlags parameter, and returned from UARTIntStatus.
//
//*****************************************************************************
#define UART_INT_RXERR          0x01
#define UART_INT_RXRDY_BRKDT    0x02
#define UART_INT_TXRDY          0x04
#define UART_INT_TXFF           0x08
#define UART_INT_RXFF           0x10

//*****************************************************************************
//
// Values that can be passed to UARTConfigSetExpClk as the ulConfig parameter
// and returned by UARTConfigGetExpClk in the pulConfig parameter.
// Additionally, the UART_CONFIG_PAR_* subset can be passed to
// UARTParityModeSet as the ulParity parameter, and are returned by
// UARTParityModeGet.
//
//*****************************************************************************
#define UART_CONFIG_WLEN_MASK   0x00000007  // Mask for extracting word length
#define UART_CONFIG_WLEN_8      0x00000007  // 8 bit data
#define UART_CONFIG_WLEN_7      0x00000006  // 7 bit data
#define UART_CONFIG_WLEN_6      0x00000005  // 6 bit data
#define UART_CONFIG_WLEN_5      0x00000004  // 5 bit data
#define UART_CONFIG_STOP_MASK   0x00000080  // Mask for extracting stop bits
#define UART_CONFIG_STOP_ONE    0x00000000  // One stop bit
#define UART_CONFIG_STOP_TWO    0x00000080  // Two stop bits
#define UART_CONFIG_PAR_MASK    0x00000060  // Parity Mask
#define UART_CONFIG_PAR_NONE    0x00000000  // No parity
#define UART_CONFIG_PAR_EVEN    0x00000060  // Even parity
#define UART_CONFIG_PAR_ODD     0x00000020  // Odd parity
#define UART_CONFIG_PAR_ONE     0x00000020  // Parity bit is one
#define UART_CONFIG_PAR_ZERO    0x00000060  // Parity bit is zero

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ulTxLevel parameter and
// returned by UARTFIFOLevelGet in the pulTxLevel.
//
//*****************************************************************************
#define UART_FIFO_TX1_8         0x00000001  // Transmit interrupt at 1/4 Full
#define UART_FIFO_TX2_8         0x00000002  // Transmit interrupt at 1/2 Full
#define UART_FIFO_TX4_8         0x00000003  // Transmit interrupt at 3/4 Full
#define UART_FIFO_TX6_8         0x00000004  // Transmit interrupt Full

//*****************************************************************************
//
// Values that can be passed to UARTFIFOLevelSet as the ulRxLevel parameter and
// returned by UARTFIFOLevelGet in the pulRxLevel.
//
//*****************************************************************************
#define UART_FIFO_RX1_8         0x00000001  // Receive interrupt at 1/4 Full
#define UART_FIFO_RX2_8         0x00000002  // Receive interrupt at 1/2 Full
#define UART_FIFO_RX4_8         0x00000003  // Receive interrupt at 3/4 Full
#define UART_FIFO_RX6_8         0x00000004  // Receive interrupt at Full

//*****************************************************************************
//
// Values that can be passed to UARTDMAEnable() and UARTDMADisable().
//
//*****************************************************************************
#define UART_DMA_ERR_RXSTOP     0x00000004  // Stop DMA receive if UART error
#define UART_DMA_TX             0x00000002  // Enable DMA for transmit
#define UART_DMA_RX             0x00000001  // Enable DMA for receive

//*****************************************************************************
//
// Values returned from UARTRxErrorGet().
//
//*****************************************************************************
#define UART_RXERROR_OVERRUN    0x00000008
#define UART_RXERROR_BREAK      0x00000020
#define UART_RXERROR_PARITY     0x00000004
#define UART_RXERROR_FRAMING    0x00000010

//*****************************************************************************
//
// Values that can be passed to UARTHandshakeOutputsSet() or returned from
// UARTHandshakeOutputGet().
//
//*****************************************************************************
#define UART_OUTPUT_RTS         0x00000800
#define UART_OUTPUT_DTR         0x00000400

//*****************************************************************************
//
// Values that can be returned from UARTHandshakeInputsGet().
//
//*****************************************************************************
#define UART_INPUT_RI           0x00000100
#define UART_INPUT_DCD          0x00000004
#define UART_INPUT_DSR          0x00000002
#define UART_INPUT_CTS          0x00000001

//*****************************************************************************
//
// Values that can be passed to UARTTxIntModeSet() or returned from
// UARTTxIntModeGet().
//
//*****************************************************************************
#define UART_TXINT_MODE_FIFO_M  0x0000001F
#define UART_TXINT_MODE_EOT     0x00000000



//---------------------------------------------------------------------------
// Sci External References & Function Declarations:
//


extern volatile struct SCI_REGS SciaRegs;
extern volatile struct SCI_REGS ScibRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of F2806x_SCI_H definition
//===========================================================================
// End of file.
//===========================================================================
