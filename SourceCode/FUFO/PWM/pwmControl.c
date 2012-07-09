#include "../FUFO.h"

unsigned int PR4_value;
unsigned int periodValue;
unsigned int initDCValue;
int a = 1000;
unsigned int PWM_per_thrust = Fcy/100000;
void initPWMPort(void){
	PWM_LAT = 0;
	PWM_TRIS = 0;
}

void initPWM(void){
	periodValue = Fcy/(Fpwm*4);
	initDCValue = ((float)periodValue*Fpwm)/1000;
	PR4_value = initDCValue;
	initPWMPort();
	initPWMHardware();
	initPWMSoftware();
	_PTEN = 1;				// PWM time base is ON
	_RE5 = 1;
	T4CONbits.TON = 1;		//timer 4 on
}

void initPWMHardware(void){
	PTPER = 2499;
	PWMCON1 = 0x070F;			//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;			//Khong dung overdrive
	_PTSIDL = 0;			// PWM time base runs in CPU Idle mode
	_PTOPS = 0x0000;			// 1:1 Postscale
	_PTCKPS = 0x10;			// PWM time base input clock period is 16 Tcy  (1:16 prescale)
	_PTMOD = 0x00;			// PWM time base operates in a free running mode
	PDC1 = 2000;			//Khoi tao ESC1 chay o 1ms
	PDC2 = initDCValue*2;			//Khoi tao ESC3 chay o 1ms
	PDC3 = calcTimeMS(1)*2/16;			//Khoi tao ESC5 chay o 1ms
	_PTEN = 0;				// PWM time base is OFF
}

void initPWMSoftware(void){
	IPC5bits.T4IP = 6;  	//highest priority interrupt
	T4CONbits.TCKPS = 0x00;	// timer 2 prescale = 1
	TMR4 = 0;
	PR4 = PR4_value;		
	IFS1bits.T4IF = 0;		//interupt flag clear
    IEC1bits.T4IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T4CONbits.TON = 0;		//timer 2 off
}

void setPWM1(unsigned int Thrust1, int PID_Motor1, int motor1){
	PDC1 = (initDCValue + Thrust1*PWM_per_thrust + PID_Motor1 + motor1*40)*2 + PWM_per_thrust*2;
}

void setPWM2(unsigned int Thrust2, int PID_Motor2, int motor2){
	PDC2 = (initDCValue + Thrust2*PWM_per_thrust + PID_Motor2 + motor2*40)*2;
}

void setPWM3(unsigned int Thrust3, int PID_Motor3, int motor3){
	PDC3 = (initDCValue + Thrust3*PWM_per_thrust + PID_Motor3 + motor3*40)*2 + PWM_per_thrust*24;
}

void setPWM4(unsigned int Thrust4, int PID_Motor4, int motor4){
	PR4_value = initDCValue + Thrust4*PWM_per_thrust + PID_Motor4 + motor4*40 + PWM_per_thrust*7;
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