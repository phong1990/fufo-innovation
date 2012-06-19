#include "p30f4012.h"
#include "../Delay/DelayTMR1.h"
#include "pwmControl.h"
#include "../FUFO.h"

unsigned int PR4_value;
unsigned int periodValue;
unsigned int initDCValue;

void initPWMPort(void){
	PWM_LAT = 0;
	PWM_TRIS = 0;
}

void initPWM(unsigned int DCValue){
	periodValue = Fcy/Fpwm - 1;
	initDCValue = DCValue;
	PR4_value = initDCValue;
	initPWMPort();
	initPWMHardware();
	initPWMSoftware();
	PTCON = 0x8000;			//Kich hoat module PWM
	_RE5 = 1;
	T4CONbits.TON = 1;		//timer 4 on
}

void initPWMHardware(){
	PTPER = periodValue;
	PWMCON1 = 0x070F;			//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;			//Khong dung overdrive
	PDC1 = initDCValue*2;			//Khoi tao ESC1 chay o 1ms
	PDC2 = initDCValue*2;			//Khoi tao ESC3 chay o 1ms
	PDC3 = initDCValue*2;			//Khoi tao ESC5 chay o 1ms
}

void initPWMSoftware(void){
	IPC5bits.T4IP = 6;  	//highest priority interrupt
	T4CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR4 = 0;
	PR4 = PR4_value;		
	IFS1bits.T4IF = 0;		//interupt flag clear
    IEC1bits.T4IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T4CONbits.TON = 0;		//timer 2 off
}

void setPWM1(unsigned int Thrust1, unsigned int PID_Motor1){
	PDC1 = (initDCValue + Thrust1*19 + PID_Motor1)*2 + 38;
}

void setPWM2(unsigned int Thrust2, unsigned int PID_Motor2){
	PDC2 = (initDCValue + Thrust2*19 + PID_Motor2)*2;
}

void setPWM3(unsigned int Thrust3, unsigned int PID_Motor3){
	PDC3 = (initDCValue + Thrust3*19 + PID_Motor3)*2 + 456;
}

void setPWM4(unsigned int Thrust4, unsigned int PID_Motor4){
	PR4_value = initDCValue + 114 + Thrust4*19 + PID_Motor4;
}

void __attribute__((__interrupt__ , auto_psv)) _T4Interrupt (void)
{
	TMR4 = 0;	
//	T4CONbits.TON = 0;	//timer 4 off
	if (PR4 == (periodValue - PR4_value)){
		PR4 = PR4_value;		// HIGH on 1 ms
		_RE5 = 1;
	}else{
		PR4 = periodValue - PR4_value;		// LOW on 2.5 ms
		_RE5 = 0;
	}
//	T4CONbits.TON = 1;		//timer 4 on
	IFS1bits.T4IF = 0;	// clear interrupt flag manually
}