#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "PWM/pwmControl.h"
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
unsigned int PDC;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	initFUFO();
	while(1){
		fufoCmd4LCD(LCD_CLEAR);
		fufoDelayMs(1000);
		_RE8 = 0;
		fufoOutputInt(PDC);
		fufoDelayMs(1000);
		_RE8 = 1;
	}
}

//Ham khoi tao cac chuong trinh cua FUFO
void initFUFO(void){
	PDC = initPWM(Fcy, 1843);		// khoi tao PWM voi tan so thuc thi lenh Fcy;
							// do rong xung ban dau 1ms (1843).
	fufoInitLCDPorts();
	fufoDelayMs(10);
	fufoInitLCD();
	fufoDelayMs(10);
}