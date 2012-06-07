//Define Bluetooth module
#include "Bluetooth.h"
#include "../UART/UART.h"
#include "../LCD/LCD.h"


void fufoInitBluetooth(unsigned char *s){
	fufoSendStringUART(ATMODE);
	*s = fufoReceiveUART();
	*(s+1) = fufoReceiveUART();
	fufoSendStringUART(ATB6);
	*(s+2) = fufoReceiveUART();
	*(s+3) = fufoReceiveUART();
	*(s+4) = fufoReceiveUART();
	*(s+5) = fufoReceiveUART();
	*(s+6) = fufoReceiveUART();
	*(s+7) = fufoReceiveUART();
	*(s+8) = fufoReceiveUART();
	fufoSendStringUART(ATNAME);
	*(s+9) = fufoReceiveUART();
	*(s+10) = fufoReceiveUART();
	*(s+11) = fufoReceiveUART();
	*(s+12) = fufoReceiveUART();
	*(s+13) = fufoReceiveUART();
	*(s+14) = fufoReceiveUART();
	*(s+15) = fufoReceiveUART();
	*(s+16) = fufoReceiveUART();
	*(s+17) = fufoReceiveUART();
	fufoSendStringUART(ATPIN);
	*(s+18) = fufoReceiveUART();
	*(s+19) = fufoReceiveUART();
	*(s+20) = fufoReceiveUART();
	*(s+21) = fufoReceiveUART();
	*(s+22) = fufoReceiveUART();
	*(s+23) = fufoReceiveUART();
	*(s+24) = fufoReceiveUART();
	*(s+25) = fufoReceiveUART();
	
}

void testConnectBluetooth(unsigned char *receiOK){
	int idx = 0;
	while(idx < 2) {
		fufoDat4LCD(receiOK[idx++]);
		fufoDelayMs(1);
	}
	while(idx < 9) {
		fufoDat4LCD(receiOK[idx++]);
		fufoDelayMs(1);
	}
		fufoCmd4LCD(LCD_HOMEL2);
		fufoDelayMs(1);
	while(idx < 18) {
		fufoDat4LCD(receiOK[idx++]);
		fufoDelayMs(1);
	}
	while(idx < 26) {
		fufoDat4LCD(receiOK[idx++]);
		fufoDelayMs(1);
	}
	fufoDelayMs(5000);
	fufoCmd4LCD(LCD_CLEAR);
	fufoDelayMs(1);
}

unsigned char fufoReceiveCmd(void) {
	
}
