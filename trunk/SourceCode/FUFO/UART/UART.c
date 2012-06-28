//Communication dspic30f4012 with BlueTooth module (HC-06-S) in UART
#include "p30f4012.h"
#include "UART.h"
#include "../Control/Control.h"
#include "../FUFO.h"

#define UARTWRITE 0
#define UARTREAD 1

//Initialize UART module
void fufoInitUART(void) {
	U1MODE = 0x8400;		//Main I/O, 8-bit, no parity, 1 stop bit
//	_U1RXIE = 1;
	U1STA = 0x0400;			//bit10=UTXEN
	U1BRG = ((((FOSC*PLL/4)/UARTBAUD)/16)-1);	//38400 bps @ FOSC = 7372800 Hz	
}

//
void fufoSendIntUART(int i) {
}

//Send a char by UART
void fufoSendCharUART(unsigned char c) {	
	U1TXREG = c;
	while(!U1STAbits.TRMT);
}

//Send a String by UART
void fufoSendStringUART(unsigned char *s) {
	int idx = 0;
	while(s[idx]) {
		fufoSendCharUART(s[idx++]);
	}
}

//Receive a Char by UART
unsigned char fufoReceiveUART(void) {
	while(!U1STAbits.URXDA);
    return U1RXREG;
}
