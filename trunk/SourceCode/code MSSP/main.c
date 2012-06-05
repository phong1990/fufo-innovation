//Communication dspic30f4012 with ADXL345 in I2C
#include "p30f4012.h"
#include "ADXL345_accel/ADXL345.h"
#include "L3G4200D_gyro/L3G4200D.h"
#include "Delay/DelayTMR1.h"
#include "I2C/I2C.h"
#include "UART/UART.h"
#include "LCD/LCD.h"
#include "Bluetooth/BL.h"
#include "math.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

void fufoInitSystem(void);


unsigned short flag1, flag2, buf_idx, str_idx, i;
unsigned char buff[] = "abc";
unsigned char str[16], temp;

int main(void) {
	    unsigned int dataGyroArray[3], dataAccelArray[3];
		unsigned char error = 0;
		unsigned char noticeError[] = "Errored";
		unsigned char receiOK[25];
		unsigned char cmdBL;
		float xA, yA, zA, xG, yG, zG;
		float convertAccel = 0.0039;
		float convertGyro = 0.00875;
        int xIntA, yIntA, zIntA, xIntG, yIntG, zIntG;
		int idx = 0;
		_RE5 = 0;
		_TRISE5 = 1;
        fufoInitSystem();
		
		//Init BL module
		fufoInitBluetooth(receiOK);
		while(idx < 2) {
			fufoDat4LCD(receiOK[idx++]);
			fufoDelayMs(1);
		}
		while(idx < 9) {
			fufoDat4LCD(receiOK[idx++]);
			fufoDelayMs(1);
		}
		fufoCmd4LCD(LCD_HOMEL2);
		fufoDelayMs(1);
		while(idx < 18) {
			fufoDat4LCD(receiOK[idx++]);
			fufoDelayMs(1);
		}
		while(idx < 26) {
			fufoDat4LCD(receiOK[idx++]);
			fufoDelayMs(1);
		}
		fufoDelayMs(5000);
		fufoCmd4LCD(LCD_CLEAR);
		fufoDelayMs(1);
        while(1)
        {	
//			if(IFS0bits.U1RXIF) {
				cmdBL = fufoReceiveUART();
				IFS0bits.U1RXIF = 0;
				fufoDat4LCD(cmdBL);
				fufoDelayMs(1);
//			}
//			if(_RE5 == 0) {
//				error = fufoReadAccel(dataAccelArray);
//				if(error == 0) {
//		        	if(dataAccelArray[0] < 4096) {
//						xA = dataAccelArray[0] * convertAccel * 1000;	
//					} else {
//						xA = (8192 - dataAccelArray[0]) * convertAccel * 1000;
//					
//					}
//		
//					if(dataAccelArray[1] < 4096) {
//						yA = dataAccelArray[1] * convertAccel * 1000;	
//					} else {
//						yA = (8192 - dataAccelArray[1]) * convertAccel * 1000;
//							
//					}
//		
//					if(dataAccelArray[2] < 4096) {
//						zA = dataAccelArray[2] * convertAccel * 1000;	
//					} else {
//						zA = (8192 - dataAccelArray[2]) * convertAccel * 1000;
//							
//					}
//					xIntA = (int)xA;
//					yIntA = (int)yA;
//		          	zIntA = (int)zA;
//					
//					fufoCmd4LCD(LCD_CLEAR);
//					fufoDelayMs(1);
//					fufoOutputInt(dataAccelArray[0]);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					fufoOutputInt(dataAccelArray[1]);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					fufoOutputInt(dataAccelArray[2]);
//		            fufoDelayMs(1);
//		
//					fufoCmd4LCD(LCD_HOMEL2);
//					fufoDelayMs(1);
//					if(dataAccelArray[0] >= 4096) { 
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}				
//					fufoOutputInt(xIntA);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					if(dataAccelArray[1] >= 4096) {
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}
//					fufoOutputInt(yIntA);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					if(dataAccelArray[2] >= 4096) { 
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}
//					fufoOutputInt(zIntA);
//		            fufoDelayMs(1);
//				} else {fufoOutputChar(noticeError);}
//			} else {
//				error = fufoReadGyro(dataGyroArray);
//				if(error == 0) {
//					if(dataGyroArray[0] < 32768) {
//						xG = dataGyroArray[0] * convertGyro * 1000;
//					} else {
//						xG = (65536 - dataGyroArray[0]) * convertGyro * 1000;
//					}
//	
//					if(dataGyroArray[1] < 32768) {
//						yG = dataGyroArray[1] * convertGyro * 1000;
//					} else {
//						yG = (65536 - dataGyroArray[1]) * convertGyro * 1000;
//					}
//	
//					if(dataGyroArray[2] < 32768) {
//						zG = dataGyroArray[2] * convertGyro * 1000;
//					} else {
//						zG = (65536 - dataGyroArray[2]) * convertGyro * 1000;
//					}
//	
//					xIntG = (int)xG;
//					yIntG = (int)yG;
//					zIntG = (int)zG;
//	
//					fufoOutputInt(dataGyroArray[0]);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					fufoOutputInt(dataGyroArray[1]);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					fufoOutputInt(dataGyroArray[2]);
//	            	fufoDelayMs(1);
//	
//					fufoCmd4LCD(LCD_HOMEL2);
//					fufoDelayMs(1);
//					if(dataGyroArray[0] >= 32768) {
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}
//					fufoOutputInt(xIntG);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					if(dataGyroArray[1] >= 32768) {
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}
//					fufoOutputInt(yIntG);
//					fufoDelayMs(1);
//					fufoDat4LCD(',');
//					fufoDelayMs(1);
//					if(dataGyroArray[2] >= 32768) {
//						fufoDat4LCD('-');
//						fufoDelayMs(1);
//					}
//					fufoOutputInt(zIntG);
//	            		fufoDelayMs(1);
//				} else {fufoOutputChar(noticeError);}
//			}
//			fufoDelayMs(500);
//			error = fufoReadByteI2C(L3G4200D_I2C, 0x0F, dataArr);
//			if(error == 0) {
//				if(dataArr[0] == 0xD3) {
//					fufoDat4LCD('D');
//				} else {fufoDat4LCD('S');}
//			} else {fufoOutputChar(noticeError);}
//			fufoDelayMs(500);			
        }
}

//-------------- initSystem -----------------------------------
// Initilize the microcontroler, startup of all modules
void fufoInitSystem() {
	unsigned char error = 0;
	_LATE0 = 0;
	_TRISE0 = 0;
	fufoInitI2C();
	fufoDelayMs(10);
	error = fufoInitAccel();
	fufoDelayMs(500);
	error = fufoInitGyro();
	fufoDelayMs(500);
	fufoInitUART();
	fufoDelayMs(10);	
	fufoInitLCDPorts();
	fufoDelayMs(10);
	fufoInitLCD();
	fufoDelayMs(10);
}
