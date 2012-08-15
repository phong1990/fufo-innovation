#include "../FUFO.h"


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
float psiHigh;
float accVelo, accAlt, altFinal;
float accAltOld = 0;
float altHigh;
float accAltOld, altHighOld;

void CalcFirstAngle(void){
	fufoGetAngleAccel();
	fufoGetAngleGyros();
	phiComp = k*(phiAngle + Ry*0.01) + (1 - k)*phiAngle; 			// this line of code is to make the angle which is calculated by gyroscope 
																				// become pessistant with the Zero point of the inertial frame, according to 
																				// the Accelerometer.
	thetaComp = k*(thetaAngle + Rx*0.01) + (1 - k)*thetaAngle;
}

void CompFilter(void){
	fufoGetAngleAccel();
	fufoGetAngleGyros();
	phiComp = k*(phiComp + Ry*0.01) + (1 - k)*phiAngle;
	thetaComp = k*(thetaComp + Rx*0.01) + (1 - k)*thetaAngle;
	psiHigh = k*(psiHigh + Rz*0.01);
	setGyrosOutputR(Rx);
	setGyrosOutputP(Ry);
	setGyrosOutputY(Rz);
	setPhiAngle(phiComp);
	setThetaAngle(thetaComp);
	setPsiAngle(psiHigh);	
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
		if (idx100%10 == 0){
			fufoOutputChar("..");
		}
		if(idx100 == 100) {	
			R0x = (int)(xIntG/idx100);
			R0y = (int)(yIntG/idx100);
			R0z = (int)(zIntG/idx100);	
			idx100 = 0;
			CalcFirstAngle();
			_RE8 = 0;
			setState(Ready);	
		}		
	}
}

void fufoGetAngleGyros(void){
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
	Rx = (float)(Rxm - R0x) * convertGyro;
	Ry = (float)(Rym - R0y) * convertGyro;
	Rz = (float)(Rzm - R0z) * convertGyro ;
}

void fufoGetAngleAccel(void){
	readAccel(dataAccelArray);
	
    if(dataAccelArray[0] < 4096) {
		Ax = (float)dataAccelArray[0]*convertAccel;	
	} else {
		Ax = ((float)dataAccelArray[0] - 8192)*convertAccel;
	}

	if(dataAccelArray[1] < 4096) {
		Ay = (float)dataAccelArray[1]*convertAccel;	
	} else {
		Ay = ((float)dataAccelArray[1] - 8192)*convertAccel;
	}

	if(dataAccelArray[2] < 4096) {
		Az = (float)dataAccelArray[2]*convertAccel;	
	} else {
		Az = ((float)dataAccelArray[2] - 8192)*convertAccel;
			
	}
	phiAngle = (180 / 3.1415926)*atan2(-Ax, sqrt(pow(Ay, 2) + pow(Az, 2)));

	thetaAngle = (180 / 3.1415926)*atan2(Ay, sqrt(pow(Az, 2) + 0.01 * pow(Ax, 2)));
}

void fufogetAltitude(void){
	float accZ = 0;
	accZ =  (sqrt(pow(Ax, 2) + pow(Ay, 2) + pow(Az, 2)) - 1)*9.8;
	accAlt = accAlt + (accVelo*0.01) + ((accZ*0.01)*0.01)/2;
	accVelo = accVelo + accZ*0.01;
	setAccelAlt(accAlt);
}

float altitudeFilter(float baroAlt, float accelAlt){	
	altHigh = kH*(altHigh + accelAlt - accAltOld);
	altFinal = kAlt*(altFinal + altHigh - altHighOld) + (1-kAlt)*baroAlt;
	altHighOld = altHigh;
	accAltOld = accelAlt;
	return altFinal;
}
