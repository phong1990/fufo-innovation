/*******************************************************************************
;	Vidu5-2.c la chuong trinh viet bang C30 de chay tren mot dsPIC			   *
;	Chuong trinh thuc hien viec sau: Doc tin hieu analog vao tu AN0 sau moi	   *
;	giay, truyen ket qua ve may tinh qua cong RS232.						   *
;*******************************************************************************

;	Tac gia				: Nguyen Quang Nam									   *

;	Don vi				: PIC Viet Nam										   *

;	Ten tap tin			: Vidu5-2.c											   *

;	Ngay				: 28/08/2006										   *

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
#define	Fcy	8000000				//Tan so thuc thi lenh
#define	baud	38400			//Toc do baud cua RS232

//Cac prototype cho cac chuong trinh con
void Init_PORTS(void);
void Init_ADC10(void);
void Init_TMR1(void);
void Init_UART1(void);

//Cac bien toan cuc
unsigned int ADCValue, flag, idx;
unsigned char HexTable[] = "0123456789ABCDEF";

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_TMR1();			//Khoi tao Timer 1
	Init_ADC10();			//Khoi tao module ADC
	Init_UART1();			//Khoi tao module UART1
	flag = 0;
	while (1) {
		if (flag) {						//Neu co ket qua moi thi xuat ket qua
			idx = (ADCValue >> 8);		//Nibble cao nhat (chi co 2 bit)
			U1TXREG = HexTable[idx];	//Chuyen thanh ky tu tuong ung
			while (!U1STAbits.TRMT);	//Cho den khi truyen xong ky tu
			idx = ((ADCValue >> 4) & 0x000F);	//Nibble thu hai
			U1TXREG = HexTable[idx];	//Chuyen thanh ky tu tuong ung
			while (!U1STAbits.TRMT);	//Cho den khi truyen xong ky tu
			idx = (ADCValue & 0x000F);	//Nibble thap nhat
			U1TXREG = HexTable[idx];	//Chuyen thanh ky tu tuong ung
			while (!U1STAbits.TRMT);	//Cho den khi truyen xong ky tu
			U1TXREG = 0x0A;				//Cap ky tu CR, LF
			while (!U1STAbits.TRMT);	//Cho den khi truyen xong ky tu
			U1TXREG = 0x0D;
			flag = 0;					//Xoa co bao hieu co ket qua moi
		};
	};
}

//Chuong trinh con khoi tao cac cong I/O, de xuat cac tin hieu PWM, va doc tin
//hieu dieu chinh cua bien tro tai AN0
void Init_PORTS(void) {
	TRISB = 0x0001;			//Chan RB0 la ngo vao analog AN0, cac chan khac
							//la ngo ra
}

//Chuong trinh con khoi tao Timer 1, tran sau moi 1 giay o muc xung 8 Mips
void Init_TMR1(void) {
	TMR1 = 0;				//Xoa so dem trong TMR1
	PR1 = 0x7A12;			//Nguong tran la 1 giay ung voi clock = 32 MHz
	_T1IF = 0;				//Xoa co ngat cua Timer 1
	T1CON = 0x8030;			//Dung fcy lam clock, prescale = 1:256
	_T1IE = 1;				//Cho phep ngat khi Timer 1 tran
}

//Chuong trinh con khoi tao module chuyen doi A/D, doc ngo vao AN0
void Init_ADC10(void) {
	ADPCFG = 0xFFFE;		//Cac chan khac la digital, chan AN0/RB0 la analog
	ADCON1 = 0x00E0;		//Module ADC cham dut lay mau va kich hoat
							//viec chuyen doi A/D
	ADCON2 = 0;
	ADCHS = 0;				//Kenh 0 doc tin hieu giua AN0 va AVss
	ADCSSL = 0;				//Khong quet cac ngo vao
	ADCON3 = 0x1F03;		//Dung 31 TAD cho lay mau, dung clock he thong,
							//TAD = 2xTcy = 250 ns
	_ADIF = 0;				//Xoa co ngat ADC
	_ADIE = 1;				//Cho phep ngat ADC
	_ASAM = 1;				//Tu dong lay mau
}

//Chuong trinh con khoi tao module UART1
void Init_UART1(void) {
	U1MODE = 0x8000;		//Main I/O, 8-bit, no parity, 1 stop bit
	U1STA = 0x0400;			//bit10=UTXEN
	U1BRG = (((Fcy/baud)/16)-1);	//38400 bps @ Fcy = 8 MHz
}

//Chuong trinh xu ly ngat Timer 1
void _ISR _T1Interrupt(void) {
	_ADON = 1;				//Bat module ADC
	_T1IF = 0;				//Xoa co ngat
}

//Trinh phuc vu ngat cho ADC
void _ISR _ADCInterrupt(void)
{
	ADCValue = ADCBUF0;		//Lay ket qua ADC vao bien ADCValue
	_ADON = 0;				//Tat module ADC
	flag = 1;				//Bat co bao hieu co ket qua moi
	_ADIF = 0;
}
