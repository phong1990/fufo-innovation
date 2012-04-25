#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
// Define some constant.
#define	PWM_PORT	PORTE		// PWM port 
#define	PWM_TRIS	TRISE		// PWM TRIS
#define	PWM_LAT		LATE		// Thanh ghi chot cac tin hieu PWM
#define FOSC		7372800		// 7.3728Mhz Crystal 
#define	Fcy			1843200		// Fcy = 1/Tcy = MIPS = (Fosc * PLLx) / 4
#define	Fpwm		100			// FPWM Frequency for each PWM pin in a pair. This value  
								// is PWM period (or Tpwm), which equal to 1/Fpwm. 
								// Tpwm = 1/Fpwm = 1/100 = 0.01(s) = 10(ms)
								// 
								// Most of the DC ESC accept Fpwm = 50Hz as standard.
								// In some documents, the ESC standard for PWM is writen as Tpwm = 20ms. 
								//
								// If we use the LOW and HIGH PWM pin respectively, the PWM period for each
								// ESC will be equal to 10x2=20ms. Although in the second half of the period, 
								// ESC will not recieve any signal (assumed the logic is equal to 0).
								// This is not a problem since we are only generate Pulse Width for the first
								// 1 to 2 ms.
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
								//				log(2*1843200/100)
								// Resolution = __________________
								//					log(2)
								//
								// Resolution = 15.16...
								//
#define PTMRprescal	1			// PWM Prescaler in this application is 1:1.
								// But in order to make this setting work, the PTCKPS bits of PTCON must be 00



// declare some init function
void Init_PORTS(void);
void Init_MCPWM(void);
bit Change_PWM(int PIN_number, bit UP);
int P1H_level = 0;
int P1L_level = 0;
int P2H_level = 0;
int P2L_level = 0;
int P3H_level = 0;
int P3L_level = 0;

//Chuong trinh chinh
int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	Init_ADC10();			//Khoi tao module ADC
	while (1) Nop();        // Do not need to do anything
}


//Chuong trinh con khoi tao cac cong I/O, de xuat cac tin hieu PWM, va doc tin
//hieu dieu chinh cua bien tro tai AN0
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
											// PTPER = 1 * 1843200/100 - 1 = 18431 
	PWMCON1 = 0x0733;		// PWMCON1: 0000 0111 0011 0011
							// Or:
							// PTMOD3: 1 (Independent PWM3 Output)
							// PTMOD2: 1 (Independent PWM2 Output)
							// PTMOD1: 1 (Independent PWM1 Output)
							// PEN3H : 0 (Disable PWM pin 3H)
							// PEN2H : 1 (enable PWM pin 2H)
							// PEN1H : 1 (enable PWM pin 1H)
                           	// PEN3L : 0 (Disable PWM pin 3L)
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

	PDC1 = PTPER/100*10;	// PWM1 = 10% (1ms)
	PDC2 = PTPER/100*15;	// PWM2 = 15% (1.5 ms) 
	PDC3 = PTPER/100*20;    // PWM3 = 20% (20 ms)

	PWMCON2 = 0x0000;		// PWMCON2: 0000 0000 0000 0000
							// Or:
							// SEVOPS: 000 ( Postscaler 1:1 for The PWM special event trigger)
							// OSYNC: 0
							// UDIS: 0 (The PWM update lockout feature disabled)

	PTCON = 0x8000;			// PTCON: 1000 0000 0000 0000 
							// Or:
							// PTEN: 1 (enable PWM)
							// PTSIDL: 0 (the PWM module will continue to operate in CPU Idle mode)
							// PTCKPS: 00 (prescaler 1:1)
							// PTOPS: 00 (postscaler 1:1)
							// PTMOD: 00 (Free Running mode)
}

// return 1 if success
bit Change_PWM(int PIN_number, bit UP){
	switch (PIN_number){
		case 11:	// PIN 1H
			if (UP)
				P1H_level += 
			break;
		case 12: 	// PIN 1L
			break;
		case 21:  	// PIN 2H
			break;
		case 22: 	// PIN 2L
			break;
		case 31: 	// PIN 3H
			break;
		case 32: 	// PIN 3L
			break;
	}
}

