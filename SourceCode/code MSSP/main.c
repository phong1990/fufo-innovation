//Communication dspic30f4012 with ADXL345 in I2C
#include "p30f4012.h"
#include "ADXL345_accel/ADXL345.h"
#include "L3G4200D_gyro/L3G4200D.h"
#include "Delay/DelayTMR1.h"
#include "I2C/I2C.h"
#include "LCD/LCD.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

void fufoInitSystem(void);


unsigned short flag1, flag2, buf_idx, str_idx, i;
unsigned char buff[] = "abc";
unsigned char str[16], temp;

int main(void) {
	 int dataGyroArray[3], dataAccelArray[3];

        fufoInitSystem();
        while(1)
        {

        	fufoReadAccel(dataAccelArray);
        	fufoReadGyro(dataGyroArray);
			fufoCmd4LCD(LCD_CLEAR);
			fufoDelayMs(5000);
//			_LATE8 = 1;
//			fufoDelayMs(1000);
//			_LATE8 = 0;
//			fufoOutputChar(buff);

			fufoOutputInt(dataAccelArray[0]);
			fufoDelayMs(10);
			fufoDat4LCD(',');
			fufoDelayMs(10);
			fufoOutputInt(dataAccelArray[1]);
			fufoDelayMs(10);
			fufoDat4LCD(',');
			fufoDelayMs(10);
			fufoOutputInt(dataAccelArray[2]);
            fufoDelayMs(10);
			fufoDelayMs(10000);
			
			fufoCmd4LCD(LCD_CLEAR);
			fufoDelayMs(5);
			fufoOutputInt(dataGyroArray[0]);
			fufoDelayMs(10);
			fufoDat4LCD(',');
			fufoDelayMs(10);
			fufoOutputInt(dataGyroArray[1]);
			fufoDelayMs(10);
			fufoDat4LCD(',');
			fufoDelayMs(10);
			fufoOutputInt(dataGyroArray[2]);
            fufoDelayMs(10);
			fufoDelayMs(10000);			
        }
}

//-------------- initSystem -----------------------------------
// Initilize the microcontroler, startup of all modules
void fufoInitSystem() {
	unsigned char error = 0;
	_LATE0 = 0;
	_TRISE0 = 0;
	fufoInitI2C();
	fufoDelayMs(5);
	error = fufoInitAccel();
	fufoDelayMs(1000);
	error = fufoInitGyro();
	fufoDelayMs(1000);
	if(error != 0) {
        fufoDelayMs(1000);
		_LATE0 = 1;
	}

	
	
	fufoDelayMs(50);
	fufoInitLCDPorts();
	fufoDelayMs(5);
	fufoInitLCD();
	fufoDelayMs(5);
}
