#include <p33fj12gp202.h>

	_FOSC(POSCMD_XT);
	_FWDT(FWDTEN_ON);
//	_FBORPOR(PBOR_OFF & MCLR_EN);
	//_FGS(CODE_PROT_OFF);

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	_LATB0 = 0;
	T1CONbits.TON = 0; 		//timer 1 off.
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;
	_LATB0 = 1;	
	_LATB1 = 1;
	setup_TMR1();
	setup_TMR3();
}

void __attribute__((__interrupt__ , auto_psv)) _T3Interrupt (void)
{
	IFS0bits.T3IF = 0;
	_LATB1 = 0;	
	T3CONbits.TON = 0; 	//timer 3 off.
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 30000;		//set timer preset 2ms
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

void setup_TMR3(void)
{
	IPC2bits.T3IP = 7;		//highest priority interrupt
	T3CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR3 = 0;
	PR3 = 2765;		//set timer preset 1.5 ms
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T3IF = 0;		//interupt flag clear
    IEC0bits.T3IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T3CONbits.TON = 1;		//timer 3 on
	return;
}

int main (void){
	LATB = 0;
	TRISB = 0;
	//TRISE = 0xFEC0;
	//Init_MCPWM();
	//setup_TMR1();
	setup_TMR2();
	while (1) {
		//_LATB0 = 1;	
	}
}