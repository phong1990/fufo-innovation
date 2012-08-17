#include "FUFO.h"

unsigned int mainState = 0;
float phiActual = 0; 
float thetaActual = 0;
float psiActual = 0;
float GyrosOutputR = 0;
float GyrosOutputP = 0;
float GyrosOutputY = 0;
float AccelAltitude = 0;
int pid1 = 0;
int pid2 = 0;
int pid3 = 0;
int pid4 = 0;
int PIDStatus = 0;
int PIDAltitude = 0;
int Conn;

int getConnectStatus(void){
	return Conn;
}
void setConnectStatus(int Connect){
	Conn = Connect;
}

int getPIDStatus(void){
	return PIDStatus;
}
void setPIDStatus(int status){
	PIDStatus = status;
}

void setPIDAltitude(int sta){
	PIDAltitude = sta;
}
int getPIDAltitude(void){
	return PIDAltitude;
}

void setPID1(int p1){
	pid1 = p1;
}

int getPID1(void){
	return pid1;
}
void setPID2(int p2){
	pid2 = p2;
}

int getPID2(void){
	return pid2;
}
void setPID3(int p3){
	pid3 = p3;
}

int getPID3(void){
	return pid3;
}
void setPID4(int p4){
	pid4 = p4;
}

int getPID4(void){
	return pid4;
}

int getState(){
	return mainState;
}

void setState(unsigned int State){
	mainState = State;
}

int calcTimeMS(unsigned int time){
	return (time*Fcy/1000);
}

void setPhiAngle(float Phi){
	phiActual = Phi;
}

float getPhiAngle(void){
	return phiActual;
}

void setThetaAngle(float Theta){
	thetaActual = Theta;
}

float getThetaAngle(void){
	return thetaActual;
}

void setPsiAngle(float Psi){
	psiActual = Psi;
}

float getPsiAngle(void){
	return psiActual;
}

void setGyrosOutputR(float GyrosR){
	GyrosOutputR = GyrosR;
}

float getGyrosOutputR(void){
	return GyrosOutputR;
}

void setGyrosOutputP(float GyrosP){
	GyrosOutputP = GyrosP;
}

float getGyrosOutputP(void){
	return GyrosOutputP;
}

void setGyrosOutputY(float GyrosY){
	GyrosOutputY = GyrosY;
}

float getGyrosOutputY(void){
	return GyrosOutputY;
}

void setAccelAlt(float Alt){
	AccelAltitude = Alt;
}

float getAccelAlt(void){
	return AccelAltitude;
}

float constrain(float valueConstrain, float min, float max) {
	if(valueConstrain > max) {
		valueConstrain = max;
	}
	if(valueConstrain < min) {
		valueConstrain = min;
	}
	return valueConstrain;
}
