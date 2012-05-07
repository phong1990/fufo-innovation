#include "mainLCD.h"

unsigned char a;

//Chuong trinh chinh
int main(void) {
	LCD_Init();
	LATE = 0;
	TRISE = 0;
	a = 12;
	xuat1("Hello ajino");
	//xuat2(a);
	while (1) {			//Vong lap chinh
		Delay_ms(1000);
		_LATE8 = 1;
		Delay_ms(1000);
		_LATE8 = 0;
	}
}