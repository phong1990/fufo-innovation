#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy			1843200		//Tan so thuc thi lenh     Fcy = (Fosc*PLLz)/4 = 7372800*1/4
#define	Fpwm		50			//Tan so PWM = 50Hz vi 50Hz la tan so hoat dong cua ESC
								
volatile unsigned int timer1_count;			

void Init_PORTS(void);
void Init_MCPWM(void);
void setup_TMR1(void);

int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	while (1) {
//		delay_tmr1(3000);
//		PDC1 += 100;	
	}Nop();
}

void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0xFFC0;		//Cac tin hieu PWM nam tai RE0..RE5
}

//Chuong trinh con khoi tao module PWM
void Init_MCPWM(void) {
	PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 50Hz
							//Cong thuc tinh PTPER = (Fcy/(Fpwm*prescaler))-1
							//voi Fcy va Fpwm nhu tren va Prescaler la 1:1 thi PTPER = 36863 (0x8D43)
							//Cong thuc tinh resolution : log(2*Fcy/Fpwm)/log(2)
							//O day resolution la 16 (0xFFFF)
	PWMCON1 = 0x070F;		//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 1843;			//Khoi tao ESC1 chay o 1ms
	PDC2 = 2765;			//Khoi tao ESC3 chay o 1.5ms
	PTCON = 0x8000;			//Kich hoat module PWM
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

void delay_tmr1(unsigned int delay)
{
	timer1_count = delay;
	setup_TMR1();		
	while(timer1_count);
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