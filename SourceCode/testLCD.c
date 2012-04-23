#include "p30f4012.h"

	_FOSC(CSW_FSCM_OFF & FRC_PLL4);		//Clock = 7,3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF);
	_FGS(CODE_PROT_OFF);
	
#define	ms_count	30			//So dem tuong ung voi 1 ms, cho timer 1

#define	LCD_EN	LATB1			//Tin hieu Enable cho LCD, chan RB1
#define	LCD_RS	LATB0			//Tin hieu Reset cho LCD, chan RB0
#define	LCD_DAT1	LATB2			//Cac tin hieu Data cho LCD, chan RB2..RB5 (D4..D7)
#define	LCD_DAT2	LATB3
#define	LCD_DAT3	LATB4
#define	LCD_DAT4	LATB5

#define	LCD_clear	0x01		//Xoa man hinh LCD
#define	LCD_home	0x02		//Tro ve dau dong
#define	LCD_normal	0x06		//Che do nhap du lieu binh thuong
#define	LCD_normal_s	0x07	//Che do nhap du lieu binh thuong, dich man hinh
#define	LCD_off 	0x08		//Tat man hinh
#define	LCD_on	 	0x0C		//Bat man hinh
#define	LCD_on_crsr 0x0E		//Bat man hinh va con tro
#define	LCD_on_blink 0x0F		//Bat man hinh va con tro (nhap nhay)
#define	LCD_4b2l	0x28		//Che do 2 dong, giao tiep 4 bit du lieu
#define	LCD_homeL1	0x80		//Ve dau dong 1
#define	LCD_homeL2	0xC0		//Ve dau dong 2

//Cac function cho cac chuong trinh con
void Init_PORTS(void);				//Khoi tao cac cong I/O
void Init_TMR1(void);				//Khoi tao Timer 1
void Delay_ms(unsigned int);		//Tao tre mot so ms
void Init_LCD(void);				//Khoi tao LCD
void LCD_cmd4(unsigned char);		//Xuat lenh ra LCD qua giao tiep 4-bit
void LCD_dat4(unsigned char);		//Xuat du lieu ra LCD qua giao tiep 4-bit


//Bang hang so trong ROM
const unsigned char __attribute__ ((space(psv), address (0x0800))) 
	//Chuoi ky tu se xuat ra LCD
	Chuoi1[]="Hello world!\0";		//Chuoi ky tu se duoc xuat ra LCD

//Cac bien toan cuc
unsigned char time_out, idx;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_TMR1();				//Khoi tao cho TMR1
	Init_PORTS();				//Khoi tao cac cong I/O
	_PSV=1;
	PSVPAG = __builtin_psvpage(Chuoi1);
	idx = 0;
	Delay_ms(50);
	Init_LCD();
	Delay_ms(500);
	while (Chuoi1[idx]) {		//Xuat chuoi ra dong thu nhat cua LCD
		LCD_dat4(Chuoi1[idx++]);
		Delay_ms(1);
	};
	LCD_cmd4(LCD_homeL2);
	Delay_ms(1);
	idx = 0;
	while (Chuoi1[idx]) {		//Xuat chuoi ra dong thu hai cua LCD
		LCD_dat4(Chuoi1[idx++]);
		Delay_ms(1);
	};
	while (1) {			//Vong lap chinh
	};
}

//Chuong trinh con khoi tao Timer 1
//TMR1 duoc dung de dem so ms troi qua, o muc xung 8 Mips (fcy = 8 MHz)
//------------------------------------------------------------------------------
void Init_TMR1(void) {
	TMR1 = 0;			//Xoa so dem trong TMR1
	PR1 = ms_count;		//TMR1 tran moi ms
	_T1IF = 0;			//Xoa co ngat cua Timer 1
	T1CON = 0x0020;		//Dung fcy lam clock, prescale = 1:64, tat Timer 1
	_T1IE = 1;			//Cho phep ngat Timer 1
}

//Chuong trinh con khoi tao cac cong I/O, de noi voi LED
//------------------------------------------------------------------------------
void Init_PORTS(void) {
	LATBbits.LCD_DAT1 = 0;		//Xoa cac bit chot du lieu LCD
	LATBbits.LCD_DAT2 = 0;
	LATBbits.LCD_DAT3 = 0;
	LATBbits.LCD_DAT4 = 0;
	_TRISB2 = 0;		//Cac chan du lieu LCD la ngo ra
	_TRISB3 = 0;
	_TRISB4 = 0;
	_TRISB5 = 0;
	LATBbits.LCD_EN = 0;
	_TRISB1 = 0;			//RB1 la ngo ra, noi vao Enable cua LCD
	LATBbits.LCD_RS = 0;
	_TRISB0 = 0;			//RB0 la ngo ra, noi vao Reset cua LCD
}

//Chuong trinh con delay bang timer 1, nhan 1 tham so la so ms can delay
//------------------------------------------------------------------------------
void Delay_ms(unsigned n) {
	PR1 = n*ms_count;			//Dat nguong tran vao PR1
	time_out = 0;				//Xoa co het thoi gian cho
	T1CONbits.TON = 1;			//Bat timer 1
	while (time_out == 0);		//Cho den khi het thoi gian cho
	T1CONbits.TON = 0;			//Tat timer 1
	TMR1 = 0;
}

//Chuong trinh con khoi tao module LCD
//------------------------------------------------------------------------------
void Init_LCD(void) {
	LCD_cmd4(LCD_4b2l);			//Dat che do giao tiep 4-bit, man hinh 2 dong
	Delay_ms(1);
	LCD_cmd4(LCD_off);			//Tat man hinh
	Delay_ms(1);
	LCD_cmd4(LCD_normal);		//Che do nhap du lieu binh thuong
	Delay_ms(1);
	LCD_cmd4(LCD_on_blink);		//Bat man hinh, hien con tro nhap nhay
	Delay_ms(1);
	LCD_cmd4(LCD_clear);		//Xoa man hinh
	Delay_ms(5);
}

//Chuong trinh con xuat lenh o che do 4 bit
//------------------------------------------------------------------------------
void LCD_cmd4(unsigned char cmd) {
	unsigned i;
	LATBbits.LCD_RS = 0;		//Dat che do xuat lenh
	//temp1 = LATBbits.LCD_DAT1;	//Lay trang thai hien thoi cua LCD_DAT1
	LATBbits.LCD_DAT1 = ((cmd >> 7) % 2);	//Xuat 4 bit cao(bit8)
	//temp1 = LATBbits.LCD_DAT2;	//Lay trang thai hien thoi cua LCD_DAT2
	LATBbits.LCD_DAT2 = ((cmd >> 6) % 2);	//Xuat 4 bit cao(bit7)
	//temp1 = LATBbits.LCD_DAT3;	//Lay trang thai hien thoi cua LCD_DAT3
	LATBbits.LCD_DAT3 = ((cmd >> 5) % 2);	//Xuat 4 bit cao(bit6)
	//temp1 = LATBbits.LCD_DAT4;	//Lay trang thai hien thoi cua LCD_DAT4
	LATBbits.LCD_DAT4 = ((cmd >> 4) % 2);	//Xuat 4 bit cao(bit5)
	LATBbits.LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++);	//keo dai toi thieu 1 us
	LATBbits.LCD_EN = 0;
	//temp1 = LATBbits.LCD_DAT1;	//Lay trang thai hien thoi cua LCD_DAT1
	LATBbits.LCD_DAT1 = ((cmd >> 3) % 2);	//Xuat 4 bit thap(bit4)
	//temp1 = LATBbits.LCD_DAT2;	//Lay trang thai hien thoi cua LCD_DAT2
	LATBbits.LCD_DAT2 = ((cmd >> 2) % 2);	//Xuat 4 bit thap(bit3)
	//temp1 = LATBbits.LCD_DAT3;	//Lay trang thai hien thoi cua LCD_DAT3
	LATBbits.LCD_DAT3 = ((cmd >> 1) % 2);	//Xuat 4 bit thap(bit2)
	//temp1 = LATBbits.LCD_DAT4;	//Lay trang thai hien thoi cua LCD_DAT4
	LATBbits.LCD_DAT4 = (cmd % 2);	//Xuat 4 bit thap(bit1)
	LATBbits.LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++);	//keo dai toi thieu 1 us
	LATBbits.LCD_EN = 0;
}

//Chuong trinh con xuat du lieu o che do 4 bit
//------------------------------------------------------------------------------
void LCD_dat4(unsigned char dat) {
	unsigned i;
	LATBbits.LCD_RS = 1;		//Dat che do xuat du lieu
	//temp2 = LATBbits.LCD_DAT1;	//Lay trang thai hien thoi cua LCD_DAT1
	LATBbits.LCD_DAT1 = ((dat >> 7) % 2);	//Xuat 4 bit cao(bit8)
	//temp2 = LATBbits.LCD_DAT2;	//Lay trang thai hien thoi cua LCD_DAT2
	LATBbits.LCD_DAT2 = ((dat >> 6) % 2);	//Xuat 4 bit cao(bit7)
	//temp2 = LATBbits.LCD_DAT3;	//Lay trang thai hien thoi cua LCD_DAT3
	LATBbits.LCD_DAT3 = ((dat >> 5) % 2);	//Xuat 4 bit cao(bit6)
	//temp2 = LATBbits.LCD_DAT4;	//Lay trang thai hien thoi cua LCD_DAT4
	LATBbits.LCD_DAT4 = ((dat >> 4) % 2);	//Xuat 4 bit cao(bit5)
	LATBbits.LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++);	//keo dai toi thieu 1 us
	LATBbits.LCD_EN = 0;
	//temp2 = LATBbits.LCD_DAT1;	//Lay trang thai hien thoi cua LCD_DAT1
	LATBbits.LCD_DAT1 = ((dat >> 3) % 2);	//Xuat 4 bit thap(bit4)
	//temp2 = LATBbits.LCD_DAT2;	//Lay trang thai hien thoi cua LCD_DAT2
	LATBbits.LCD_DAT2 = ((dat >> 2) % 2);	//Xuat 4 bit thap(bit3)
	//temp2 = LATBbits.LCD_DAT3;	//Lay trang thai hien thoi cua LCD_DAT3
	LATBbits.LCD_DAT3 = ((dat >> 1) % 2);	//Xuat 4 bit thap(bit2)
	//temp2 = LATBbits.LCD_DAT4;	//Lay trang thai hien thoi cua LCD_DAT4
	LATBbits.LCD_DAT4 = (dat % 2);	//Xuat 4 bit thap(bit1)
	LATBbits.LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++);	//keo dai toi thieu 1 us
	LATBbits.LCD_EN = 0;
}

//Chuong trinh xu ly ngat Timer 1
//------------------------------------------------------------------------------
void _ISR _T1Interrupt(void) {
	_T1IF = 0;			//Xoa co ngat
	time_out = 1;
}


