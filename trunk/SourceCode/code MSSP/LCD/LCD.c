//Definition LCD1602
#include "p30f4012.h"
#include "LCD.h"
#include "../Delay/DelayTMR1.h"


//---------------------functions--------------------------------------

//Initialize I/O ports
void fufoInitLCDPorts(void) {
	LCD_DAT1 = 0;
	LCD_DAT2 = 0;
	LCD_DAT3 = 0;
	LCD_DAT4 = 0;
	_TRISB2 = 0;
	_TRISB3 = 0;
	_TRISB4 = 0;
	_TRISB5 = 0;
	LCD_EN = 0;
	_TRISB1 = 0;
	LCD_RS = 0;
	_TRISB0 = 0;
}

//Initialize LCD
void fufoInitLCD(void) {
	fufoCmd4LCD(LCD_HOME);			//Return to top of the line, this command have to be sent to lcd
	fufoDelayMs(1);
	fufoCmd4LCD(LCD_4B2L);			//2 lines and 4 bits communication mode
	fufoDelayMs(1);
	fufoCmd4LCD(LCD_OFF);			//Turn off the screen
	fufoDelayMs(1);
	fufoCmd4LCD(LCD_NORMAL);		//Normal mode

	fufoDelayMs(1);
	fufoCmd4LCD(LCD_ON_BLINK);		//Turn on the screen and the blink cursor
	fufoDelayMs(1);
	fufoCmd4LCD(LCD_CLEAR);		//Clear the screen
	fufoDelayMs(5);
}

//Output command to LCD by 4-bit mode
void fufoCmd4LCD(unsigned char cmd) {
	LCD_RS = 0;		//Output command mode
	LCD_DAT4 = ((cmd & 0x80) >> 7);	//Output 4 high bits(bit8)
	LCD_DAT3 = ((cmd & 0x40) >> 6);	//Output 4 high bits(bit7)
	LCD_DAT2 = ((cmd & 0x20) >> 5);	//Output 4 high bits(bit6)
	LCD_DAT1 = ((cmd & 0x10) >> 4);	//Output 4 high bits(bit5)
	LCD_EN = 1;		//Create enable pulse
	fufoDelayUs(20);	//Delay 2 us at least
	LCD_EN = 0;
	LCD_DAT4 = ((cmd & 0x08) >> 3);	//Output 4 low bits(bit4)
	LCD_DAT3 = ((cmd & 0x04) >> 2);	//Output 4 low bits(bit3)
	LCD_DAT2 = ((cmd & 0x02) >> 1);	//Output 4 low bits(bit2)
	LCD_DAT1 = (cmd & 0x01);	//Output 4 low bits(bit1)
	LCD_EN = 1;		//Create enable pulse
	fufoDelayUs(20);	//Delay 2 us at least
	LCD_EN = 0;
}

//Output data to LCD by 4-bit mode
void fufoDat4LCD(unsigned char dat) {
	LCD_RS = 1;		//Dat che do xuat du lieu
	LCD_DAT4 = ((dat & 0x80) >> 7);	//Output 4 high bits(bit8)
	LCD_DAT3 = ((dat & 0x40) >> 6);	//Output 4 high bits(bit7)
	LCD_DAT2 = ((dat & 0x20) >> 5);	//Output 4 high bits(bit6)
	LCD_DAT1 = ((dat & 0x10) >> 4);	//Output 4 high bits(bit5)
	LCD_EN = 1;		//Create enable pulse
	fufoDelayUs(20);	//Delay 2 us at least
	LCD_EN = 0;
	LCD_DAT4 = ((dat & 0x08) >> 3);	//Output 4 low bits(bit4)
	LCD_DAT3 = ((dat & 0x04) >> 2);	//Output 4 low bits(bit3)
	LCD_DAT2 = ((dat & 0x02) >> 1);	//Output 4 low bits(bit2)
	LCD_DAT1 = (dat & 0x01);	//Output 4 low bits(bit1)
	LCD_EN = 1;		//Create enable pulse
	fufoDelayUs(20);	//Delay 2 us at least
	LCD_EN = 0;	
}

//Output data in char type
void fufoOutputChar(unsigned char data[]){
	fufoDelayMs(10);
	int idx = 0;
	while (data[idx]) {
		fufoDat4LCD(data[idx++]);
		fufoDelayMs(10);
	}	
}

//Output data in int type
void fufoOutputInt(unsigned int a) {
    unsigned char aArr[] = "Array";
    int idx = 0;
    while((a % 10) >= 0 && a > 0){
        aArr[idx++] = (char)((int)'0'+(a % 10));
        //aArr[idx++] = '0'+(a % 10);
        a /= 10;
	 }
    while(idx > 0){
        fufoDat4LCD(aArr[--idx]);
		fufoDelayMs(10);
    }
}
