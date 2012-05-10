#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define FOSC		7372800		// 7.3728Mhz Crystal 
#define	Fcy			1843200		// Fcy = 1/Tcy = MIPS = (Fosc * PLLx) / 4
								//                    =  (7372800 * 1)/4 = 1843200
#define	Fpwm		50			// FPWM Frequency for each PWM pin in a pair. This value  
								// is PWM period (or Tpwm), which equal to 1/Fpwm. 
								// Tpwm = 1/Fpwm = 1/50 = 0.02(s) = 20(ms)
								// 
								// Most of the DC ESC accept Fpwm = 50Hz as standard.
								// In some documents, the ESC standard for PWM is writen as Tpwm = 20ms. 
								//
								// Another thing to consider is the Resolution of PWM
								//
								//              log(2*Tpwm/Tcy)
								// Resolution = _______________
								//					log(2)
								// Which Tcy = 1/Fcy and Tpwm = 1/Fpwm, the equation now is:
								//
								//              log(2*Fcy/Fpwm)
								// Resolution = _______________
								//					log(2)
								//
								//				log(2*1843200/50)
								// Resolution = __________________
								//					log(2)
								//
								// Resolution = 16.16... (bits)
								//
								
#define PTMRprescal	1			// PWM Prescaler in this application is 1:1.
								// But in order to make this setting work, the PTCKPS bits of PTCON must be 00
volatile unsigned int timer1_count;			

void Init_PORTS(void);
void Init_MCPWM(void);
void setup_TMR1(void);

int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	while (1) Nop();
}

void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0xFFC0;		// 1111 1111 1100 0000 Set output in RE0, RE1, RE2, RE3, RE4, RE5
}

//Chuong trinh con khoi tao module PWM
void Init_MCPWM(void) {
	PTPER = PTMRprescal * Fcy / Fpwm - 1;	// PTPER is used to determine the PWM period
											// Tcy = 1/Fcy = 1/1843200
    										// Tpwm = 1/ Fpwm
    										// PTPER = Tpwm * PTMRprescal * 1/Tcy - 1;
											// PTPER = PTMRprescal * Fcy/Fpwm - 1
											// PTPER = 1 * 1843200/50 - 1 = 36863 

	PWMCON1 = 0x0707;		// PWMCON1: 0000 0111 0000 0111
							// Or:
							// PTMOD3: 1 (Independent PWM3 Output)
							// PTMOD2: 1 (Independent PWM2 Output)
							// PTMOD1: 1 (Independent PWM1 Output)
							// PEN3H : 0 (Disable PWM pin 3H)
							// PEN2H : 0 (Disable PWM pin 2H)
							// PEN1H : 0 (Disable PWM pin 1H)
                           	// PEN3L : 1 (enable PWM pin 3L)
							// PEN2L : 1 (enable PWM pin 2L)
							// PEN1L : 1 (enable PWM pin 1L)
	OVDCON = 0x3F00;		// ODVCON: 0011 1111 0000 0000
							// Or: Do not use Override
							// POVD3H: 1
							// POVD3L: 1
							// POVD2H: 1
							// POVD2L: 1
							// POVD1H: 1
							// POVD1L: 1
							// POUT3H: 0
							// POUT3L: 0
							// POUT2H: 0
							// POUT2L: 0
							// POUT1H: 0
							// POUT1L: 0
							
	// The LS bit of a duty cycle register determines whether the
	// PWM edge occurs in the beginning. Thus, the PWM
	// resolution is effectively doubled. 
	// In other words, the PDCn value should be double to reach the desired PWM.
	PDC1 = 3687;			//Khoi tao ESC1 chay o 1ms
	PDC2 = 5530;			//Khoi tao ESC3 chay o 1.5ms
	PTCON = 0x8000;			// PTCON: 1000 0000 0000 0000 
							// Or:
							// PTEN: 1 (enable PWM)
							// PTSIDL: 0 (the PWM module will continue to operate in CPU Idle mode)
							// PTCKPS: 00 (prescaler 1:1)
							// PTOPS: 00 (postscaler 1:1)
							// PTMOD: 00 (Free Running mode)
}

void setup_TMR1(void)
{
	IPC0bits.T1IP = 7;		//highest priority interrupt
	T1CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR1 = 0;
	PR1 = 1843;		//set timer preset 1 ms
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T1IF = 0;		//interupt flag clear
    IEC0bits.T1IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T1CONbits.TON = 1;		//timer 1 on
	return;
}
