//Communication dspic30f4012 with ADXL345 in I2C
#include "p30f4012.h"
#include "ADXL345_accel/ADXL345.h"
#include "L3G4200D_gyro/L3G4200D.h"
#include "Delay/DelayTMR1.h"
#include "LCD/LCD.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

void fufoInitSystem(void);


unsigned short flag1, flag2, buf_idx, str_idx, i;
unsigned char buff[] = {};
unsigned char str[16], temp;

int main(void) {
	 int dataGyroArray[3], dataAccelArray[3];

        initSystem();

        while(1)
        {

        	fufoReadAccel(dataAccelArray);
        	fufoReadGyro(dataGyroArray);
			
			//Initialize LCD
			fufoInitLCDPorts();
			fufoInitLCD();
            fufoDelayMs(10);

			fufoOutputInt(dataAccelArray[0]);
			fufoOutputChar(",");
			fufoOutputInt(dataAccelArray[1]);
			fufoOutputChar(",");
			fufoOutputInt(dataAccelArray[2]);
            fufoDelayMs(10);
        }
}

//-------------- initSystem -----------------------------------
// Initilize the microcontroler, startup of all modules
void fufoInitSystem() {
	fufoInitI2C();
	fufoInitAccel();
	fufoInitGyro();
	fufoDelayMs(5);
}