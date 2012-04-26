#include <p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);
	// based on: http://lordvon64.blogspot.com/2011/02/easy-pulse-width-modulation-pwm-with.html
	// This code make a software PWM pulse with 1.5ms duty circle and 20ms period at RE0
	// while lighting up a led at RE8
	
#define Fcy (7372800/4)

volatile unsigned int timer1_count;
volatile unsigned int timer2_count;

void Init_MCPWM(void);

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	PORTE = 0x0100 	// output LOW on RE0, HIGH on RE8
	T1CONbits.TON = 0; 		//timer 1 off.
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;
	PORTE = 0x0101 	// output HIGH on RE0, HIGH on RE8	
	setup_TMR1();	// Run timer1 until it first 1.5ms interrupt after this momment.
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 2765;				//set timer preset 1.5 ms
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

void init_PWM_2timer(void){
	setup_TMR2(); // interrupt every 20ms
}

int main (void){
	TRISE = 0x0000; // Port E is a output port 
	PORTE = 0x0100	// output HIGH on RE8, low on RE0
	init_PWM_2timer(); // setup timer 2 for 20ms, timer1 for 1.5ms
	while (1) {	
	}
}

