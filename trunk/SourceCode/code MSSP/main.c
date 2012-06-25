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
void fufoInitTimer2();
void fufoGetRateAngle();
void fufoGetAngle();
unsigned short flag1, flag2, buf_idx, str_idx, i;
unsigned int idx100 = 0;
unsigned int setupFlag = 1;
unsigned int readTimes = 1;
unsigned int h  = 0;
int R0x, R0y, R0z;
int xIntA, yIntA, zIntA, xIntG, yIntG, zIntG;
int Rxm, Rym, Rzm;
int Rx, Ry, Rz;
float Ax, Ay, Az;
int phiAngle, thetaAngle;
float convertAccel = 0.0039;
float convertGyro = 0.00875;
unsigned int dataGyroArray[3], dataAccelArray[3];
unsigned char noticeError[] = "Errored";
int main(void) {
	    
		unsigned char error = 0;
		unsigned char receiOK[25];
		unsigned char dataArr[1];
		//unsigned char cmdBL;
		float xA, yA, zA, xG, yG, zG;
		
		int idx = 0;
		fufoDelayMs(5000);
        fufoInitSystem();
		//Init BL module
//		fufoInitBluetooth(receiOK);
//		while(idx < 2) {
//			fufoDat4LCD(receiOK[idx++]);
//			fufoDelayMs(1);
//		}
//		while(idx < 9) {
//			fufoDat4LCD(receiOK[idx++]);
//			fufoDelayMs(1);
//		}
//		fufoCmd4LCD(LCD_HOMEL2);
//		fufoDelayMs(1);
//		while(idx < 18) {
//			fufoDat4LCD(receiOK[idx++]);
//			fufoDelayMs(1);
//		}
//		while(idx < 26) {
//			fufoDat4LCD(receiOK[idx++]);
//			fufoDelayMs(1);
//		}
//		fufoDelayMs(5000);
//		fufoCmd4LCD(LCD_CLEAR);
//		fufoDelayMs(1);		
      while(1) {
//			fufoDelayMs(500);
//			fufoCmd4LCD(LCD_CLEAR);
//			fufoDelayMs(1);	
//			error = fufoReadByteI2C(L3G4200D_I2C, 0x0F, dataArr);
//			if(error == 0) {
//				if(dataArr[0] == 0xD3) {
//					fufoDat4LCD('D');
//				} else {fufoDat4LCD('S');}
//			} else {fufoOutputChar(noticeError);}
//			fufoDelayMs(500);
			T4CONbits.TON = 1;
			if (h == 1) {
				fufoGetRateAngle();
				fufoGetAngle();
				h = 0;
				T2CONbits.TON = 0;
			}
			T4CONbits.TON = 0;
			fufoOutputInt(TMR4);
			fufoDelayMs(2000);
			fufoCmd4LCD(LCD_CLEAR);
			TMR4 = 0;
        }
}

//-------------- initSystem -----------------------------------
// Initilize the microcontroler, startup of all modules
void fufoInitSystem() {
	fufoInitI2C();
	fufoDelayMs(5);
	fufoInitAccel();
	fufoDelayMs(5);
	fufoInitGyro();
	fufoDelayMs(5);
	fufoInitUART();
	fufoDelayMs(5);	
	fufoInitLCDPorts();
	fufoDelayMs(5);
	fufoInitLCD();
	fufoDelayMs(5);
	fufoInitTimer2();

}
void fufoInitTimer2() {
	IPC1bits.T2IP = 6;  	//highest priority interrupt
	T2CONbits.TCKPS = 2;	// timer 2 prescale = 1:64
	TMR2 = 0;
	PR2 = 288;			// 10 ms	for downtime
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 1;		//timer 2 on
}

void fufoInitTimer4() {
	T4CONbits.TCKPS = 2;	// timer 4 prescale = 1:64
	TMR4 = 0;
	PR4 = 28800;			// 1000 ms	for downtime
}

void fufoGetRateAngle() {
	if(setupFlag == 1 && idx100 < 100) {
		fufoReadGyro(dataGyroArray);
		if(dataGyroArray[0] < 32768) {
			xIntG += dataGyroArray[0];
		} else {
			xIntG += (dataGyroArray[0] - 65536 );
		}
		
		if(dataGyroArray[1] < 32768) {
			yIntG += dataGyroArray[1];
		} else {
			yIntG += (dataGyroArray[1] - 65536);
		}
		
		if(dataGyroArray[2] < 32768) {
			zIntG += dataGyroArray[2];
		} else {
			zIntG += (dataGyroArray[2] - 65536);
		}
		idx100++;
		if(idx100 == 100) {	
			R0x = xIntG/idx100;
			R0y = yIntG/idx100;
			R0z = zIntG/idx100;	
		}
	} else {
		fufoReadGyro(dataGyroArray);
		if(dataGyroArray[0] < 32768) {
			Rxm = dataGyroArray[0];
		} else {
			Rxm = (dataGyroArray[0] - 65536 );
		}
		
		if(dataGyroArray[1] < 32768) {
			Rym = dataGyroArray[1];
		} else {
			Rym = (dataGyroArray[1] - 65536);
		}
		
		if(dataGyroArray[2] < 32768) {
			Rzm = dataGyroArray[2];
		} else {
			Rzm = (dataGyroArray[2] - 65536);
		}
	}
	if(idx100 >= 100) {	
		Rx = (int)(convertGyro*(Rxm - R0x) * 1000);
		Ry = convertGyro*(Rym - R0y) * 1000;
		Rz = convertGyro*(Rzm - R0z) * 1000;
		
//		if(Ry < 0) {
//			fufoSendCharUART('-');
//		}
		if(Rx < 0) {
			fufoSendCharUART('-');
		}	

		fufoSendIntUART(Rx);
		fufoSendCharUART(',');
		//fufoSendIntUART(Ry);
		//fufoSendCharUART(',');		
	}
}

void fufoGetAngle() {
	fufoReadAccel(dataAccelArray);
	
        if(dataAccelArray[0] < 4096) {
		Ax = dataAccelArray[0] * convertAccel;	
	} else {
		Ax = (8192 - dataAccelArray[0]) * convertAccel;
	
	}

	if(dataAccelArray[1] < 4096) {
		Ay = dataAccelArray[1] * convertAccel;	
	} else {
		Ay = (8192 - dataAccelArray[1]) * convertAccel;
			
	}

	if(dataAccelArray[2] < 4096) {
		Az = dataAccelArray[2] * convertAccel;	
	} else {
		Az = (8192 - dataAccelArray[2]) * convertAccel;
			
	}
	phiAngle = (int)((180 / 3.1415926) * atan2(-Ax, sqrt(pow(Ay, 2) + pow(Az, 2))) * 1000);

	thetaAngle = (int)((180 / 3.1415926) * atan2(Ay, sqrt(pow(Az, 2) + 0.01 * pow(Ax, 2))) * 1000);
	
//	if(phiAngle < 0) {
//		fufoSendCharUART('-');
//	}
//	fufoSendIntUART(phiAngle);
	if(thetaAngle < 0) {
		fufoSendCharUART('-');
	}
	fufoSendIntUART(thetaAngle);
	fufoSendCharUART('\r');
	fufoSendCharUART('\n');
	
}
void _ISR _U1RXInterrupt(void) {
	unsigned char cmdBL;
	IFS0bits.U1RXIF = 0;
//	fufoSendCharUART('2');
//	fufoSendCharUART('3');
//	fufoSendCharUART('4');
//	fufoSendCharUART('5');
//	fufoSendCharUART('6');
//	fufoSendCharUART('7');	
	cmdBL = fufoReceiveUART();
	//fufoSendCharUART(cmdBL);
//	fufoSendCharUART('a');
//	fufoSendCharUART('1');
//	fufoSendCharUART('2');
//	fufoSendCharUART('3');
//	fufoSendCharUART('4');
//	fufoSendCharUART('5');
//	fufoSendCharUART('6');
//	fufoSendCharUART('7');
	//fufoDat4LCD(cmdBL);
	//fufoDelayMs(1);
	//fufoDat4LCD(cmdBL);
}

void _ISR _T2Interrupt(void) {
		IFS0bits.T2IF = 0;
		h = 1;
		readTimes++;	
}
