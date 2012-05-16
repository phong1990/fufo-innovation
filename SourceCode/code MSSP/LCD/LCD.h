//Definition LCD1602
#include "p30f4012.h"

#define	LCD_EN		_LATB1			//Pin controls enable signal for LCD, pin RB1
#define	LCD_RS		_LATB0			//Pin controls reset signal for LCD, pin RB0

#define	LCD_DAT1	_LATB2			//Pins control data for LCD, chan RB2..RB5 (D4..D7)
#define	LCD_DAT2	_LATB3
#define	LCD_DAT3	_LATB4
#define	LCD_DAT4	_LATB5

#define	LCD_CLEAR		0x01		//Clear the screen
#define	LCD_HOME		0x02		//Return to top of line
#define	LCD_NORMAL		0x06		//Normal mode
#define	LCD_NORMAL_S	0x07		//Normal mode with shift screen
#define	LCD_OFF 		0x08		//Turn off the screen
#define	LCD_ON	 		0x0C		//Turn on the screen
#define	LCD_ON_CRSR 	0x0E		//Turn on the screen and cursor
#define	LCD_ON_BLINK 	0x0F		//Turn on the screen and blink cursor
#define	LCD_4B2L		0x28		//2 lines and 4 bits communication mode
#define	LCD_HOMEL1		0x80		//Return to top of the first line
#define	LCD_HOMEL2		0xC0		//Return to top of the second line

void fufoInitLCDPorts(void);						//Initialize I/O ports
void fufoInitLCD(void);								//Initialize LCD
void fufoCmd4LCD(unsigned char);					//Output command to LCD by 4-bit mode
void fufoDat4LCD(unsigned char);					//Output data to LCD by 4-bit mode
void fufoOutputChar(unsigned char data[]);			//Output data in char type
void fufoOutputInt(unsigned int a);					//Output data in int type
