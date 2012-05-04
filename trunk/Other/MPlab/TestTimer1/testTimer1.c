#include <p30f4012.h>

//	_FOSC(CSW_FSCM_OFF & FRC_PLL4);
//	_FWDT(WDT_OFF);
//	_FBORPOR(PBOR_OFF & MCLR_EN);
//	_FGS(CODE_PROT_OFF);

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

#define Fcy (7372800/4)
#define Fpwm 50

volatile unsigned int timer1_count;

void Init_MCPWM(void);

void __attribute__((__interrupt__ , auto_psv)) _T1Interrupt (void)
{

		IFS0bits.T1IF = 0;

	if ( timer1_count == 0 )
		T1CONbits.TON = 0; 		//timer 1 off.
	else
		{
		TMR1 = 0;
		timer1_count--;
		}
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 1843;		//set timer preset
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T1IF = 0;		//interupt flag clear
    IEC0bits.T1IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T1CONbits.TON = 1;		//timer 1 on
	return;
}

void delay_tmr1(unsigned int delay)
{
	timer1_count = delay;
	setup_TMR1();		
	while(timer1_count);
}

int main (void){
	LATE = 0;
	TRISE = 0xFEC0;
	Init_MCPWM();
	while (1) {
		PDC1 += 50;
		delay_tmr1(100);
		_LATE8 = 1;
		delay_tmr1(100);
		_LATE8 = 0;
		if(PDC1 == PTPER){
			PDC1 = 0;
		}
		
	}
}

void Init_MCPWM(void) {
	PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 40 kHz
	PWMCON1 = 0x070F;		//Chi dung cac chan PxL, mot cach doc lap
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 0;			//Khoi tao PWM1, 2, va 3 la 25%
	PDC2 = 2765;
	PTCON = 0x8000;			//Kich hoat module PWM
}
