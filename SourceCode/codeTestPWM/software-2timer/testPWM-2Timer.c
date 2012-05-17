#include <p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

#define Fcy (7372800/4)
#define Fpwm 50

volatile unsigned int timer3_count;
volatile unsigned int PR1_value;

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 1843;		//set timer preset 1 ms
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T1IF = 0;		//interupt flag clear
    IEC0bits.T1IE = 1;  	//Enable Timer1 Interrupt Service Routine
	//T1CONbits.TON = 1;		//timer 1 on
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

void setup_TMR3(void)
{
	IPC1bits.T3IP = 5;  	//highest priority interrupt
	T3CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR3 = 0;
	PR3 = 1843;				// 1 ms	
	IFS0bits.T3IF = 0;		//interupt flag clear
    IEC0bits.T3IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T3CONbits.TON = 1;		//timer 2 on
	return;
}

void delay_tmr3(unsigned int delay)
{
	timer3_count = delay;
	setup_TMR3();		
	while(timer3_count);
}

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	_LATE0 = 0;
	T1CONbits.TON = 0; 		//timer 1 off.
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;
	_LATE0 = 1;
	//setup_TMR1();
	T1CONbits.TON = 1;		//timer 1 on.
}

void __attribute__((__interrupt__ , auto_psv)) _T3Interrupt (void)
{
	IFS0bits.T3IF = 0;
	if ( timer3_count == 0 )
		{
			T3CONbits.TON = 0; 		//timer 2 off.
		}
	else
		{
		TMR3 = 0;
		timer3_count--;
		}
}
int main (void){
	LATE = 0;
	TRISE = 0;
	PR1_value = 1843;		// setup PR1 1ms
	setup_TMR2();
	setup_TMR1();
	//delay_tmr3(5000);
	//PR1_value = 2765;		// cho tang len 1.5 ms
	while (1) {
		_LATE8 = 1;
		delay_tmr3(1000);
		_LATE8 = 0;
		delay_tmr3(1000);
	}
}