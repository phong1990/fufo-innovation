#include "p30f4012.h"

#define	ms_count	30			//So dem tuong ung voi 1 ms, cho timer 1

#define	LCD_EN	_LATB1			//Tin hieu Enable cho LCD, chan RB1
#define	LCD_RS	_LATD1			//Tin hieu Reset cho LCD, chan RB0
#define	LCD_DAT1	_LATB2			//Cac tin hieu Data cho LCD, chan RB2..RB5 (D4..D7)
#define	LCD_DAT2	_LATB3
#define	LCD_DAT3	_LATB4
#define	LCD_DAT4	_LATB5

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
void InitLCD_PORTS(void);				//Khoi tao cac cong I/O
void Init_TMR1(void);				//Khoi tao Timer 1
void Delay_ms(unsigned int);		//Tao tre mot so ms
void Init_LCD(void);				//Khoi tao LCD
void LCD_cmd4(unsigned char);		//Xuat lenh ra LCD qua giao tiep 4-bit
void LCD_dat4(unsigned char);		//Xuat du lieu ra LCD qua giao tiep 4-bit

//unsigned char Chuoi[];		//Chuoi ky tu se duoc xuat ra LCD

//Cac bien toan cuc
unsigned int time_out, idx;

//------------------------------------------------------------------------------

void LCD_Init(void){
	Init_TMR1();				//Khoi tao cho TMR1
	InitLCD_PORTS();				//Khoi tao cac cong I/O
	Delay_ms(50);
	Init_LCD();
	Delay_ms(500);
	idx = 0;
}

void xuat1(unsigned char Chuoi1[]){
	while (Chuoi1[idx]) {		//Xuat chuoi ra dong thu nhat cua LCD
		LCD_dat4(Chuoi1[idx++]);
		Delay_ms(1);
	}
}

void xuatint1(unsigned int a) {
    unsigned char aArr[] = "Array";
    int idx = 0;
    while((a % 10) >= 0 && a > 0){
        aArr[idx++] = (char)((int)'0'+(a % 10));
        //aArr[idx++] = '0'+(a % 10);
        a /= 10;
	 }
    while(idx > 0){
        LCD_dat4(aArr[--idx]);
		Delay_ms(1);
    }
}

void xuat2(unsigned char Chuoi2[]){
	LCD_cmd4(LCD_homeL2);
	Delay_ms(10);
	idx = 0;
	while (Chuoi2[idx]) {		//Xuat chuoi ra dong thu hai cua LCD
		LCD_dat4(Chuoi2[idx++]);
		Delay_ms(10);
	}	
}

void LCD_int4(unsigned int dat) {
	unsigned i;
	LCD_RS = 1;		//Dat che do xuat du lieu
	LCD_DAT4 = ((dat & 0x80) >> 7);	//Xuat 4 bit cao(bit8)
	LCD_DAT3 = ((dat & 0x40) >> 6);	//Xuat 4 bit cao(bit7)
	LCD_DAT2 = ((dat & 0x20) >> 5);	//Xuat 4 bit cao(bit6)
	LCD_DAT1 = ((dat & 0x10) >> 4);	//Xuat 4 bit cao(bit5)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;

	LCD_DAT4 = ((dat & 0x08) >> 3);	//Xuat 4 bit thap(bit4)
	LCD_DAT3 = ((dat & 0x04) >> 2);	//Xuat 4 bit thap(bit3)
	LCD_DAT2 = ((dat & 0x02) >> 1);	//Xuat 4 bit thap(bit2)
	LCD_DAT1 = (dat & 0x01);	//Xuat 4 bit thap(bit1)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;	
}

//Chuong trinh con khoi tao Timer 1
//TMR1 duoc dung de dem so ms troi qua, o muc xung 7,3728/4 Mips (fcy = 7,3728/4 MHz)
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
void InitLCD_PORTS(void) {
	LCD_DAT1 = 0;		//Xoa cac bit chot du lieu LCD
	LCD_DAT2 = 0;
	LCD_DAT3 = 0;
	LCD_DAT4 = 0;
	_TRISB2 = 0;		//Cac chan du lieu LCD la ngo ra
	_TRISB3 = 0;
	_TRISB4 = 0;
	_TRISB5 = 0;
	LCD_EN = 0;
	_TRISB1 = 0;			//RB1 la ngo ra, noi vao Enable cua LCD
	LCD_RS = 0;
	_TRISD1 = 0;			//RB0 la ngo ra, noi vao Reset cua LCD
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
	LCD_cmd4(LCD_home);			//Tro ve dau dong, lenh nay bat buoc gui cho lcd
	Delay_ms(1);
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
	LCD_RS = 0;		//Dat che do xuat lenh
	LCD_DAT4 = ((cmd & 0x80) >> 7);	//Xuat 4 bit cao(bit8)
	LCD_DAT3 = ((cmd & 0x40) >> 6);	//Xuat 4 bit cao(bit7)
	LCD_DAT2 = ((cmd & 0x20) >> 5);	//Xuat 4 bit cao(bit6)
	LCD_DAT1 = ((cmd & 0x10) >> 4);	//Xuat 4 bit cao(bit5)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;
	LCD_DAT4 = ((cmd & 0x08) >> 3);	//Xuat 4 bit thap(bit4)
	LCD_DAT3 = ((cmd & 0x04) >> 2);	//Xuat 4 bit thap(bit3)
	LCD_DAT2 = ((cmd & 0x02) >> 1);	//Xuat 4 bit thap(bit2)
	LCD_DAT1 = (cmd & 0x01);	//Xuat 4 bit thap(bit1)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;
}

//Chuong trinh con xuat du lieu o che do 4 bit
//------------------------------------------------------------------------------
void LCD_dat4(unsigned char dat) {
	unsigned i;
	LCD_RS = 1;		//Dat che do xuat du lieu
	LCD_DAT4 = ((dat & 0x80) >> 7);	//Xuat 4 bit cao(bit8)
	LCD_DAT3 = ((dat & 0x40) >> 6);	//Xuat 4 bit cao(bit7)
	LCD_DAT2 = ((dat & 0x20) >> 5);	//Xuat 4 bit cao(bit6)
	LCD_DAT1 = ((dat & 0x10) >> 4);	//Xuat 4 bit cao(bit5)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;

	LCD_DAT4 = ((dat & 0x08) >> 3);	//Xuat 4 bit thap(bit4)
	LCD_DAT3 = ((dat & 0x04) >> 2);	//Xuat 4 bit thap(bit3)
	LCD_DAT2 = ((dat & 0x02) >> 1);	//Xuat 4 bit thap(bit2)
	LCD_DAT1 = (dat & 0x01);	//Xuat 4 bit thap(bit1)
	LCD_EN = 1;		//Tao xung Enable
	for (i = 0; i < 2; i++)
		for (i = 0; i < 255; i++);	//keo dai toi thieu 1 us
	LCD_EN = 0;	
}

//Chuong trinh xu ly ngat Timer 1
//------------------------------------------------------------------------------
void _ISR _T1Interrupt(void) {
	_T1IF = 0;			//Xoa co ngat
	time_out = 1; 
}


