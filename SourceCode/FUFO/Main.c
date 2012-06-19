#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "PWM/pwmControl.h"
#include "Bluetooth/Bluetooth.h"
#include "UART/UART.h"
#include "Control/Control.h"
#include "math.h"
#include "FUFO.h"


	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)
unsigned int userInputFlag = 0;

//Cac prototype cho cac chuong trinh con
void initFUFO(void);

//Cac bien toan cuc
unsigned char receiOK[25];
unsigned int index = 0;


//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	initFUFO();
	fufoCmd4LCD(LCD_CLEAR);
	fufoOutputChar("Welcome to FUFO");
	fufoDelayMs(300);
	T2CONbits.TON = 1;		//timer 2 on
	while(1){
		fufoCmd4LCD(LCD_CLEAR);
		fufoDelayMs(5);
		fufoOutputChar("Thrust: ");
		fufoOutputInt(getThrustRate());
		fufoCmd4LCD(LCD_HOMEL2);
		fufoOutputInt(PDC2);
//		if (IFS0bits.U1RXIF == 1){
//			IFS0bits.U1RXIF = 0;
//		 	fufoOutputChar("interrup");
//		} else fufoOutputChar("bang 0");
		if (userInputFlag == 0){
			getInstruction();
			userInputFlag = getUserInput();
		}
	}
}

//Ham khoi tao cac chuong trinh cua FUFO
void initFUFO(void){
	fufoInitLCDPorts();
	fufoDelayMs(10);
	fufoInitLCD();
	fufoDelayMs(10);
	fufoOutputChar("Please wait");
	fufoCmd4LCD(LCD_HOMEL2);
	initPWM(1843);		// khoi tao PWM voi tan so thuc thi lenh Fcy;
							// do rong xung ban dau 1ms (1843).
	fufoDelayMs(200);
	fufoOutputChar("...");
	fufoDelayMs(500);
	fufoOutputChar("....");
	fufoInitUART();
	fufoDelayMs(200);
	fufoOutputChar("....");
	initTMR2();
//	fufoInitBluetooth(receiOK);
//	testConnectBluetooth(receiOK);
}

void initTMR2(void){
	IPC1bits.T2IP = 7;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = 36864;		
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 0;		//timer 2 on
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{	
	TMR2 = 0;
	//T2CONbits.TON = 0;		//timer 2 off
	controlFUFO();
	if(userInputFlag == 1){
		
		_RE8 = 1;
		index++;
		if(index == 25){
			index = 0;
			userInputFlag = 0;
			_RE8 = 0;
		}
	}
	//T2CONbits.TON = 1;
	IFS0bits.T2IF = 0;	// clear interrupt flag manually
}