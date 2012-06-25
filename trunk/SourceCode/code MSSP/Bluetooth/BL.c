//Define Bluetooth module
#include "BL.h"
#include "../UART/UART.h"

void fufoInitBluetooth(unsigned char *s){
	fufoSendStringUART(ATMODE);
//	*s = fufoReceiveUART();
//	*(s+1) = fufoReceiveUART();
	fufoSendStringUART(ATB6);
//	*(s+2) = fufoReceiveUART();
//	*(s+3) = fufoReceiveUART();
//	*(s+4) = fufoReceiveUART();
//	*(s+5) = fufoReceiveUART();
//	*(s+6) = fufoReceiveUART();
//	*(s+7) = fufoReceiveUART();
//	*(s+8) = fufoReceiveUART();
	fufoSendStringUART(ATNAME);
//	*(s+9) = fufoReceiveUART();
//	*(s+10) = fufoReceiveUART();
//	*(s+11) = fufoReceiveUART();
//	*(s+12) = fufoReceiveUART();
//	*(s+13) = fufoReceiveUART();
//	*(s+14) = fufoReceiveUART();
//	*(s+15) = fufoReceiveUART();
//	*(s+16) = fufoReceiveUART();
//	*(s+17) = fufoReceiveUART();
	fufoSendStringUART(ATPIN);
//	*(s+18) = fufoReceiveUART();
//	*(s+19) = fufoReceiveUART();
//	*(s+20) = fufoReceiveUART();
//	*(s+21) = fufoReceiveUART();
//	*(s+22) = fufoReceiveUART();
//	*(s+23) = fufoReceiveUART();
//	*(s+24) = fufoReceiveUART();
//	*(s+25) = fufoReceiveUART();
	
}
