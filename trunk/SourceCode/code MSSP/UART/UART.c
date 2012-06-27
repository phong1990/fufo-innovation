//Communication dspic30f4012 with BlueTooth module (HC-06-S) in UART
#include "p30f4012.h"
#include "UART.h"

#define UARTWRITE 0
#define UARTREAD 1
#define FOSC 8000000
#define PLL 8

//Initialize UART module
void fufoInitUART(void) {
	U1MODE = 0x8400;		//Main I/O, 8-bit, no parity, 1 stop bit
	U1STA = 0x0400;			//bit10=UTXEN
	IPC2bits.U1RXIP = 3;
	IFS0bits.U1TXIF = 0;	//Clear transfer interrupt flag
	IEC0bits.U1TXIE = 0;	//Enable transfer interrupt
	IFS0bits.U1RXIF = 0;	//Clear receive interrupt flag
	IEC0bits.U1RXIE = 0;	//Enable receive interrupt
	U1BRG = ((((FOSC*PLL/4)/UARTBAUD)/16)-1);	//38400 bps @ FOSC = 8 MHz	
}

//Send a char by UART
void fufoSendCharUART(unsigned char c) {	
	U1TXREG = c;
	while(!U1STAbits.TRMT);
}

//Send a String by UART
void fufoSendStringUART(unsigned char *s) {
	int idx = 0;
	while(s[idx] != '\0') {
		fufoSendCharUART(s[idx++]);
	}
}
//Send a Int by UART
void fufoSendIntUART(int a) {
	unsigned char aArr[7];
    int idx = 0;
	if(a < 0) {
    	a *= -1;
    }
    while((a % 10) >= 0 && a > 0){
		if(idx == 3) {
			aArr[idx++] = '.';
		}
        aArr[idx++] = (char)((int)'0'+(a % 10));
        //aArr[idx++] = '0'+(a % 10);
        a /= 10;
	}
	while(idx < 7) {
		aArr[idx++] = '0';
	}
	if(aArr[3] == '0') {
			aArr[3] = '.';
	}
    while(idx > 0){
        fufoSendCharUART(aArr[--idx]);
    }
}

//Send a Long by UART
void fufoSendLongUART(long a) {
	unsigned char aArr[7];
    int idx = 0;
	if(a < 0) {
    	a *= -1;
    }
    while((a % 10) >= 0 && a > 0){
		if(idx == 3) {
			aArr[idx++] = '.';
		}
        aArr[idx++] = (char)((long)'0'+(a % 10));
        //aArr[idx++] = '0'+(a % 10);
        a /= 10;
	}
	while(idx < 7) {
		aArr[idx++] = '0';
	}
	if(aArr[3] == '0') {
			aArr[3] = '.';
	}
    while(idx > 0){
        fufoSendCharUART(aArr[--idx]);
    }
}

//Receive a Char by UART
unsigned char fufoReceiveUART(void) {
	while(!U1STAbits.URXDA); 
    return U1RXREG;
}
