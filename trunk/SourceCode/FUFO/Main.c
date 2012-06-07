#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "PWM/pwmControl.h"
#include "Bluetooth/Bluetooth.h"
#include "UART/UART.h"
#include "Control/Control.h"
#include "math.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)
#define Fcy		(7372800/4)			//Tan so thuc thi lenh

//Cac prototype cho cac chuong trinh con
void initFUFO(void);

//Cac bien toan cuc
unsigned char receiOK[25];

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	initFUFO();
	while(1){
		fufoCmd4LCD(LCD_CLEAR);
		fufoDelayMs(50);
		fufoOutputInt(PDC1);
		fufoOutputInt(PDC2);
		fufoDelayMs(50);
		fufoCmd4LCD(LCD_HOMEL2);
		fufoOutputInt(PDC3);
		fufoOutputInt(PR4);
		fufoDelayMs(500);
		ControlFUFO();
		
	}
}

//Ham khoi tao cac chuong trinh cua FUFO
void initFUFO(void){
	initPWM(Fcy, 1843);		// khoi tao PWM voi tan so thuc thi lenh Fcy;
							// do rong xung ban dau 1ms (1843).
	fufoDelayMs(500);
	fufoInitUART();
	fufoDelayMs(10);
	fufoInitLCDPorts();
	fufoDelayMs(10);
	fufoInitLCD();
	fufoDelayMs(10);
	fufoInitBluetooth(receiOK);
	testConnectBluetooth(receiOK);
}

