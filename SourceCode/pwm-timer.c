#include <p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

#define Fcy (7372800/4)
#define Fpwm 50

volatile unsigned int timer1_count;
volatile unsigned int timer2_count;

void Init_MCPWM(void);

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	_LATE0 = 0;
	T1CONbits.TON = 0; 		//timer 1 off.
//	if ( timer1_count == 0 )
//		T1CONbits.TON = 0; 		//timer 1 off.
//	else
//		{
//		TMR1 = 0;
//		timer1_count--;
//		}
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;
	_LATE0 = 1;
	//T1CONbits.TON = 1;		//timer 1 on
	
	setup_TMR1();

//	
//	if ( timer2_count == 0 )
//		{
//			T2CONbits.TON = 0; 		//timer 2 off.
//		}
//	else
//		{
//		TMR2 = 0;
//		timer2_count--;
//		}
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 2764;		//set timer preset 1.5 ms
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T1IF = 0;		//interupt flag clear
    IEC0bits.T1IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T1CONbits.TON = 1;		//timer 1 on
	return;
}

void setup_TMR2(void)
{
	IPC1bits.T2IP = 6;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = 36864;			// 20 ms	
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 1;		//timer 2 on
	return;
}

void delay_tmr1(unsigned int delay)
{
	timer1_count = delay;
	setup_TMR1();		
	while(timer1_count);
}

void delay_tmr2(unsigned int delay)
{
	timer2_count = delay;
	setup_TMR2();		
	while(timer2_count);
}


int main (void){
	LATE = 0;
	TRISE = 0xFEC0;
	//Init_MCPWM();
	//setup_TMR1();
	setup_TMR2();
	while (1) {
//		delay_tmr2(10);
//		_LATE8 = 1;
//		delay_tmr2(10);
//		_LATE8 = 0;		
	}
}

void Init_MCPWM(void) {
	//PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 40 kHz
	PWMCON1 = 0x070F;		//Chi dung cac chan PxL, mot cach doc lap
	OVDCON = 0xFF00;		//Khong dung overdrive
	//PDC1 = 0;			//Khoi tao PWM1, 2, va 3 la 25%
	//PDC2 = 2765;
	PTCON = 0x8000;			//Kich hoat module PWM
}
