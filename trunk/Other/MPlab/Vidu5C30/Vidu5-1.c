/*******************************************************************************
;	Vidu5-1.c la chuong trinh viet bang C30 de chay tren mot dsPIC			   *
;	Chuong trinh thuc hien viec sau: Doc tin hieu analog vao tu AN0, dieu	   *
;	chinh do rong xung ra tai chan RE0, RE2, va RE4 mot cach tuong ung.		   *
;*******************************************************************************

;	Tac gia				: Nguyen Quang Nam									   *

;	Don vi				: PIC Viet Nam										   *

;	Ten tap tin			: Vidu5-1.c											   *

;	Ngay				: 27/08/2006										   *

;	Phien ban			: 0.01												   *

;	Nhung tap tin can thiet khac: p30F4012.gld, p30f4012.h					   *

;	Cong cu duoc dung:	MPLAB 7.31											   *
;						C30 2.02 SE											   *
;						ASM30 2.14											   *
;						LNK30 2.14											   *
------------------------------------------------------------------------------*/
#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & FRC_PLL4);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy	8000000				//Tan so thuc thi lenh
#define	Fpwm	40000			//Tan so PWM = 40 kHz

//Cac prototype cho cac chuong trinh con
void Init_PORTS(void);
void Init_MCPWM(void);
void Init_ADC10(void);

//Cac bien toan cuc
unsigned int ADCValue;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	Init_ADC10();			//Khoi tao module ADC
	while (1) Nop();
}

//Chuong trinh con khoi tao cac cong I/O, de xuat cac tin hieu PWM, va doc tin
//hieu dieu chinh cua bien tro tai AN0
void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0xFFC0;		//Cac tin hieu PWM nam tai RE0..RE5
	TRISB = 0x0001;			//Chan RB0 la ngo vao analog AN0, cac chan khac
							//la ngo ra
}

//Chuong trinh con khoi tao module chuyen doi A/D, doc ngo vao AN0
void Init_ADC10(void) {
	ADPCFG = 0xFFFE;		//Cac chan khac la digital, chan AN0/RB0 la analog
	ADCON1 = 0x0060;		//Module PWM cham dut lay mau va kich hoat
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

//Chuong trinh con khoi tao module PWM
void Init_MCPWM(void) {
	PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 40 kHz
	SEVTCMP = PTPER;
	PWMCON1 = 0x070F;		//Chi dung cac chan PxL, mot cach doc lap
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 0x0064;			//Khoi tao PWM1, 2, va 3 la 25%
	PDC2 = 0x0064;
	PDC3 = 0x0064;
	PWMCON2 = 0x0F00;		//Postscale = 1:16
	PTCON = 0x8000;			//Kich hoat module PWM
}

//Trinh phuc vu ngat cho ADC
void _ISR _ADCInterrupt(void)
{
	ADCValue = ADCBUF0 >> 1;		//Chi lay 9-bit cao nhat cua ket qua ADC
	PDC1 = ADCValue;		//Cap nhat cac thanh ghi dem chu ky nhiem vu
	PDC2 = ADCValue;
	PDC3 = ADCValue;
	_ADIF = 0;
}
