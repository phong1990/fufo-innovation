#include	<p30f4012.h>
#include	"mainLCD.h"

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy			(7372800/4)		//Tan so thuc thi lenh
#define	Fpwm		50		//Tan so PWM = 40 kHz

void Init_PORTS(void);
void Init_MCPWM(void);
void Init_ADC10(void);

//Cac bien toan cuc
unsigned int ADCValue;
unsigned int max;
volatile unsigned int timer2_count;
volatile unsigned int timer2_value;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	Init_ADC10();			//Khoi tao module ADC
	LCD_Init();
	//timer2_value = 1843;
	max = 0;
	while (1){
		_LATE8 = 1;
		delay_tmr2(1000);
		//Init_LCD();
		_LATE8 = 0;
		delay_tmr2(1000);
		//xuatint1(ADCValue);	
		//xuatint1(PDC1);
		xuat1("dc roi!!!");
//		if (max == 0){
//			delay_tmr2(1000);
//			PDC1 += 50;
//			if (PDC1 > 6000) max = 1; 	// da len toi max
//		} else {
//			delay_tmr2(1000);
//			PDC1 -= 36;
//			if (PDC1 < 3700) max = 0;	// da xuong min
//		}
		
	} Nop();
}

//Chuong trinh con khoi tao cac cong I/O, de xuat cac tin hieu PWM, va doc tin
//hieu dieu chinh cua bien tro tai AN0
void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0;		//Cac tin hieu PWM nam tai RE0..RE5
	TRISB = 0x0001;			//Chan RB0 la ngo vao analog AN0, cac chan khac
							//la ngo ra
}

//Chuong trinh con khoi tao module chuyen doi A/D, doc ngo vao AN0
void Init_ADC10(void) {
	ADPCFG = 0xFFFE;		//Cac chan khac la digital, chan AN0/RB0 la analog
	ADCON1 = 0x00E0;		// tu dong kich hoat lay mau.
	//ADCON1 = 0x0060;		//Module PWM cham dut lay mau va kich hoat
							//viec chuyen doi A/D
//	ADCON1 = 0x0040;		//Timer 3 cham dut lay mau va kich hoat
							//viec chuyen doi A/D
	ADCON2 = 0;
	ADCHS = 0;				//Kenh 0 doc tin hieu giua AN0 va AVss
	ADCSSL = 0;				//Khong quet cac ngo vao
	ADCON3 = 0x0103;		//Dung 1 TAD cho lay mau, dung clock he thong,
							//TAD = 2xTcy = 250 ns
/*	TMR3 = 0;				//Xoa thanh ghi dem cua Timer 3
	PR3 = 0x03E8;			//Nguong delay cho TMR3 la khoang 1 ms
	T2CON = 0x8010;			//Prescale = 1:8, bat cho TMR3 chay
*/
	_ADIF = 0;				//Xoa co ngat ADC
	_ADIE = 1;				//Cho phep ngat ADC
	_ADON = 1;				//Bat module ADC
	_ASAM = 1;				//Khoi dong che do tu dong lay mau
}

void Init_MCPWM(void) {
	PTPER = 4608;	//Dat thanh ghi chu ky voi tan so PWM = 50Hz
							//Cong thuc tinh PTPER = (Fcy/(Fpwm*prescaler))-1
							//voi Fcy va Fpwm nhu tren va Prescaler la 1:1 thi PTPER = 36863 (0x8D43)
							//Cong thuc tinh resolution : log(2*Fcy/Fpwm)/log(2)
							//O day resolution la 16 (0xFFFF)
	SEVTCMP = PTPER;
	PWMCON1 = 0x070F;		//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 3686;			//Khoi tao ESC1 chay o 1ms
	PDC2 = 5530;			//Khoi tao ESC3 chay o 1.5ms
	PTCON = 0x8000;			//Kich hoat module PWM
}

//Trinh phuc vu ngat cho ADC
void _ISR _ADCInterrupt(void)
{
	ADCValue = ADCBUF0 >> 1;		//Chi lay 9-bit cao nhat cua ket qua ADC
	PDC1 = 3686 + (6*ADCValue) + (6*ADCValue/5);
	_ADIF = 0;
}

void setup_TMR2(void)
{
	IPC1bits.T2IP = 6;		//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 1 prescale = 1
	TMR2 = 0;
	PR2 = 1843;//timer2_value;		//set timer preset 1ms
	//T1CON = 0x0000;			//internal Tcy/1 clock
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 1;		//timer 1 on
	return;
}

void delay_tmr2(unsigned int delay)
{
	timer2_count = delay;
	setup_TMR2();	
	while(timer2_count);
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	
	IFS0bits.T2IF = 0;
	if ( timer2_count == 0 )
		T2CONbits.TON = 0; 		//timer 1 off.
	else
		{
		TMR2 = 0;
		timer2_count--;
		}
}