#include <p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

	// based on: http://www.rcgroups.com/forums/showthread.php?t=1532008
	// This code make a software PWM pulse with 1.5ms duty circle and 20ms period at RE0
	// while lighting up a led at RE8
#define Fcy 1843200 // =(7372800/4)

volatile unsigned int PR2_value;
volatile unsigned int timer1_count;

void Init_MCPWM(void);


void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;	// clear interrupt flag manually	
	T2CONbits.TON = 0;	//timer 2 off
	if (PR2 == (36864 - PR2_value)){
		PR2 = PR2_value;		// HIGH on 1 ms
		PORTE = 0x0101; 	// output HIGH on RE0, HIGH on RE8	
	}else{
		PR2 = 36864 - PR2_value;		// LOW on 19ms
		PORTE = 0x0100; 	// output LOW on RE0, HIGH on RE8
	}
	T2CONbits.TON = 1;		//timer 2 on

}

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{
	IFS0bits.T1IF = 0;
	if ( timer1_count == 0 )
		{
			T1CONbits.TON = 0; 		//timer 1 off.
		}
	else
		{
		TMR1 = 0;
		timer1_count--;
		}
}

void setup_TMR2(void)
{
	IPC1bits.T2IP = 7;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = 36864 - PR2_value;			// 19 ms	for downtime
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 1;		//timer 2 on
	return;
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;  	//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR1 = 0;
	PR1 = 1843;			// 19 ms	for downtime
	IFS0bits.T1IF = 0;		//interupt flag clear
    IEC0bits.T1IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T1CONbits.TON = 1;		//timer 2 on
	return;
}

void delay_tmr1(unsigned int delay)
{
	timer1_count = delay;
	setup_TMR1();		
	while(timer1_count);
}

void Init_PWM_Timer2(void){	
	setup_TMR2(); // LOW on RE0 for 18.5 ms
}
int main (void){
	TRISE = 0x0000; // Port E is a output port 
	PORTE = 0x0100;	// output HIGH on RE8, low on RE0
	PR2_value = 1843;
	Init_PWM_Timer2(); // start the software PWM. which is output HIGH 1ms then LOW 19ms in a loop
	while (1) {
		delay_tmr1(3000);
		PR2_value += 100;
	}Nop();
}