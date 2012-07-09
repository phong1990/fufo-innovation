//Define Bluetooth module
#include "../FUFO.h"


void fufoInitBluetooth(unsigned char *s){
	
	fufoSendStringUART(ATMODE);
	fufoSendStringUART(ATB6);
	fufoSendStringUART(ATNAME);
	fufoSendStringUART(ATPIN);	
}

void testConnectBluetooth(unsigned char *receiOK){
	fufoCmd4LCD(LCD_CLEAR);
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
	
	fufoCmd4LCD(LCD_CLEAR);
	fufoDelayMs(1);
}

unsigned char fufoReceiveCmd(void) {
	
}
