#include "p30f4012.h"
#include "../Delay/DelayTMR1.h"
#include "pwmControl.h"

unsigned int PR4_value;
unsigned int periodValue;

void initPWMPort(void){
	PWM_LAT = 0;
	PWM_TRIS = 0;
}

int initPWM(unsigned int Fcy,unsigned int initDutyCycleValue){
	periodValue = Fcy/Fpwm - 1;
	PR4_value = initDutyCycleValue;
	initPWMPort();
	initPWMHardware(initDutyCycleValue);
	initPWMSoftware();
	PTCON = 0x8000;			//Kich hoat module PWM
	_RE5 = 1;
	T4CONbits.TON = 1;		//timer 4 on
	return PDC1;
}

void initPWMHardware(unsigned int initDutyCycleValue){
	PTPER = periodValue;
	PWMCON1 = 0x070F;			//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;			//Khong dung overdrive
	PDC1 = initDutyCycleValue*2;			//Khoi tao ESC1 chay o 1ms
	PDC2 = initDutyCycleValue*2;			//Khoi tao ESC3 chay o 1ms
	PDC3 = initDutyCycleValue*2;			//Khoi tao ESC5 chay o 1ms
}

void initPWMSoftware(void){
	IPC5bits.T4IP = 7;  	//highest priority interrupt
	T4CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR4 = 0;
	PR4 = PR4_value;		
	IFS1bits.T4IF = 0;		//interupt flag clear
    IEC1bits.T4IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T4CONbits.TON = 0;		//timer 2 off
}

void __attribute__((__interrupt__ , auto_psv)) _T4Interrupt (void)
{
	IFS1bits.T4IF = 0;	// clear interrupt flag manually	
	T4CONbits.TON = 0;	//timer 4 off
	if (PR4 == (periodValue - PR4_value)){
		PR4 = PR4_value;		// HIGH on 1 ms
		_RE5 = 1;
	}else{
		PR4 = periodValue - PR4_value;		// LOW on 2.5 ms
		_RE5 = 0;
	}
	T4CONbits.TON = 1;		//timer 4 on
}