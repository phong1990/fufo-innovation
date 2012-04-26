#include <p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

	// based on: http://www.rcgroups.com/forums/showthread.php?t=1532008
	// This code make a software PWM pulse with 1.5ms duty circle and 20ms period at RE0
	// while lighting up a led at RE8
#define Fcy 1843200 // =(7372800/4)

volatile unsigned int timer1_count;
volatile unsigned int timer2_count;

void Init_MCPWM(void);


void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;	// clear interrupt flag manually	
	T2CONbits.TON = 0;	//timer 2 off
	if (PR2 == 34099){
		PR2 = 2765;		// HIGH on 1.5 ms
		PORTE = 0x0101 	// output HIGH on RE0, HIGH on RE8	
	}else{
		PR2 = 34099		// LOW on 18.5 ms
		PORTE = 0x0100 	// output LOW on RE0, HIGH on RE8
	}
	T2CONbits.TON = 1;		//timer 2 on

}


void setup_TMR2(void)
{
	IPC1bits.T2IP = 6;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = 34099;			// 18.5 ms	for downtime
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 1;		//timer 2 on
	return;
}

void delay_tmr2(unsigned int delay)
{
	timer2_count = delay;
	setup_TMR2();		
	while(timer2_count);
}

void Init_PWM_Timer2(void){	
	setup_TMR2(); // LOW on RE0 for 18.5 ms
}
int main (void){
	TRISE = 0x0000; // Port E is a output port 
	PORTE = 0x0100	// output HIGH on RE8, low on RE0
	Init_PWM_Timer2(); // start the software PWM. which is output HIGH 1.5ms then LOW 18.5ms in a loop
	while (1) {
	}
}