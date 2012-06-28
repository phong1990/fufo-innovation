#include "Filter.h"
#include "../FUFO.h"
#include "../LCD/LCD.h"

unsigned int idx100 = 0;
int R0x, R0y, R0z;
int xIntG, yIntG, zIntG;
int Rxm, Rym, Rzm;
float Rx, Ry, Rz;
float Ax, Ay, Az;
float phiAngle, thetaAngle;
unsigned int dataGyroArray[3], dataAccelArray[3];
unsigned char noticeError[] = "Errored";
float phiComp;
float thetaComp;
float psiComp;


void CompFilter(void){
	fufoGetRateAngle();
	fufoGetAngle();
	phiComp = k*(phiComp + Ry*0.01) + (1 - k)*phiAngle;
	setPhiAngle(phiComp);
	thetaComp = k*(thetaComp + Rx*0.01) + (1 - k)*thetaAngle;\
	setThetaAngle(thetaComp);
	//psiComp = k*(psiComp + Rz*0.01) + (1 - k)*psiAngle;
	//setPsiAngle(psiComp);
	
}

void fufoGetRateAngle(void){
	if(idx100 < 100) {
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
			fufoCmd4LCD(LCD_CLEAR);
			fufoDelayMs(1);
			fufoOutputChar("dc roi");
			setState(Setup);
		} else {
			fufoCmd4LCD(LCD_CLEAR);
			fufoDelayMs(1);
			fufoOutputChar("dc roi");
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
		Rx = (Rxm - R0x) * convertGyro;
		Ry = (Rym - R0y) * convertGyro;
		Rz = (Rzm - R0z) * convertGyro ;
	}
}

void fufoGetAngle(void){
	if(idx100 > 100) {
	fufoReadAccel(dataAccelArray);
	
    if(dataAccelArray[0] < 4096) {
		Ax = dataAccelArray[0]*convertAccel;	
	} else {
		Ax = (8192 - dataAccelArray[0])*convertAccel;
	
	}

	if(dataAccelArray[1] < 4096) {
		Ay = dataAccelArray[1]*convertAccel;	
	} else {
		Ay = (8192 - dataAccelArray[1])*convertAccel;
			
	}

	if(dataAccelArray[2] < 4096) {
		Az = dataAccelArray[2]*convertAccel;	
	} else {
		Az = (8192 - dataAccelArray[2])*convertAccel;
			
	}
	phiAngle = (180 / 3.1415926)*atan2(-Ax, sqrt(pow(Ay, 2) + pow(Az, 2)))*1000;

	thetaAngle = (180 / 3.1415926)*atan2(Ay, sqrt(pow(Az, 2) + 0.01 * pow(Ax, 2)))*1000;
	}
}