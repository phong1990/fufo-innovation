#include "../FUFO.h"

unsigned int Up, Down, Left, Right, R_Left, R_Right, Forward, Backward;
float Yaw_sum, Pitch_sum, Roll_sum, High_sum;
int PID = 0;
int thrustRate = 0;
int PWM_Motor1 = 0; 
int PWM_Motor2 = 0;
int PWM_Motor3 = 0;
int PWM_Motor4 = 0;
int PWM1 = 0;
int PWM2 = 0;
int PWM3 = 0;
int PWM4 = 0;
unsigned char comandfromBluetooth;
float P = 0;
float I = 0;
float D = 0;
float eR = 0;
float eP = 0; 
float eY = 0;
float eA = 0;
float total_eR = 0;
float total_eP = 0;
float total_eY = 0;
float total_eA = 0;
float Angle_sumR;
float Angle_sumP;
float Angle_sumY;
float Altitude;
float actualAltitudeNew = 0;
float actualAltitudeOld = 0;
float PID_sum = 0;
//float KiTheta = 0;
//float KdTheta = 6;
//float KdPhi = 1.0163;
//float KpPsi = 9;
float KiAlt = 50;
//float KdAlt = 300;
unsigned int userInput;
float xuatPhi = 0;
float xuatTheta = 0;
float phong = 0.12;	//-0.8;
float thang = -2.47;		//-6.58;
int PID_Yaw = 0;
float altitude, altitudeR, altitudeG;
float altitudeLCD, altitudeLCD1, altitudeLCD2, xuatTheta; 
float docao = 1;
float xuatdocao;

int getThrustRate(void){
	return thrustRate;	
}

void setThrustRate(int Thrust){
	thrustRate = Thrust;
}

int getUserInput(void){
	return userInput;	
}

void controlFUFO(void){
//	if(Forward == 1){
//		setSetpoint(-2.59,-23.07,-1,1);
//	} else if(Backward == 1){
//		setSetpoint(-2.59,6.93,-1,1);
//	} else if(Left == 1){
//		setSetpoint(-17.59,-8.07,-1,1);
//	} else if(Right == 1){
//		setSetpoint(12.41,-8.07,-1,1);
//	} else 
	setSetpoint(phong,thang,-1,docao);
}

void checkConnection(void){
	comandfromBluetooth = fufoReceiveUART();
	if(comandfromBluetooth == 'n'){ // ky tu n bao da ket noi voi Phone
		setState(Pending);
		fufoCmd4LCD(LCD_CLEAR);
		fufoOutputChar("Phone connected!");
		fufoDelayMs(500);
	} else if(comandfromBluetooth == 'c'){ // ky tu c bao da ket noi voi PC
		setState(Pending);
		fufoCmd4LCD(LCD_CLEAR);
		fufoOutputChar("PC connected!");
		fufoDelayMs(500);
	}
}

void checkBLConnection(void){
	comandfromBluetooth = fufoReceiveUART();
	if(comandfromBluetooth == 'h'){ // ky tu n bao da ket noi Bluetooth
		setState(Verify);
		fufoCmd4LCD(LCD_CLEAR);
		fufoOutputChar("Bluetooth connected!");
		fufoDelayMs(500);
	}
}

void getStartInstruction(void){
	comandfromBluetooth = fufoReceiveUART();
	if(comandfromBluetooth == 'f'){ // ky tu f bao Start
		resetSensor();
		resetPWM();
		resetInstruction();
		setState(Setup);
		_RE8 = 1;
	} else {
		fufoCmd4LCD(LCD_HOMEL2);
		fufoOutputChar("loi");
		userInput = 0;
	}	
}

void getUpInstruction(void){
	resetInstruction();
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		_RE8 = 1;
		Up = 1;
//		thrustRate += 1;
		PID_Yaw = 0;
		//setPIDStatus(Enable);
		T2CONbits.TON = 1;
		setState(Hovering);
		fufoSendCharUART('y');
		fufoSendCharUART('\r');
		fufoSendCharUART('\n');
		_RE8 = 0;
	}
}

void getInstruction(void){
	resetInstruction();
	setConnectStatus(Disable);
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		Up = 1;
		docao += 0.5;
	} else if(comandfromBluetooth == 'p'){
		Down = 1;
		docao -= 0.5;
	} else if(comandfromBluetooth == 'w'){
//		resetInstruction();
		Forward = 1;
		thang += 0.1;
//		KpTheta += 0.1;
//		KpTheta += 0.1;
//		TT += 0.1;
//		PWM_Motor1 -= 1;
//		PWM_Motor3 += 1;
	} else if(comandfromBluetooth == 's'){
//		resetInstruction();
		Backward = 1;
		thang -= 0.1;
//		KpTheta -= 0.1;
//		KdPhi -= 0.1;
//		PWM_Motor1 += 1;
//		PWM_Motor3 -= 1;
	} else if(comandfromBluetooth == 'a'){
//		resetInstruction();
		Left = 1;
		phong += 0.1;
//		PWM2 += 1;
//		PWM1 += 1;
//		PWM_Motor2 -= 1;
//		PWM_Motor4 += 1;
	} else if(comandfromBluetooth == 'd'){
//		resetInstruction();
		Right = 1;
		phong -= 0.1;
//		PWM4 += 1;
//		PWM3 += 1;
//		PWM_Motor2 += 1;
//		PWM_Motor4 -= 1;
	} else if(comandfromBluetooth == 'n'){
//		resetInstruction();
		R_Left = 1;
		KiAlt += 5;
//		PID_Yaw = 1;
//		TT += 1;
//		KpPsi += 1;
	} else if(comandfromBluetooth == 'k'){
//		resetInstruction();
		R_Right = 1;
		KiAlt -= 5;
//		PID_Yaw = 1;
//		TT -= 1;
//		KpPsi -= 1;
	} else if(comandfromBluetooth == 'f'){
		_RE8 = 1;
		if(getPIDStatus() == Enable){
			setPIDAltitude(Disable);
			setState(Landing);
			fufoSendCharUART('S');
			fufoSendCharUART('S');
		} else {
			setPIDStatus(Enable);
			setPIDAltitude(Enable);
		}
	}
	if(comandfromBluetooth == 'f' || comandfromBluetooth == 'y' || Up == 1 || Down == 1 || R_Left == 1 || R_Right == 1 || Left == 1 || Right == 1 || Forward == 1 || Backward == 1){
		userInput = 1;
		setConnectStatus(Enable);
	} else userInput = 0;
	xuatPhi = phong;
	xuatTheta = thang;
	xuatdocao = docao;
}

void setSetpoint(float Phi, float Theta, float Psi, float high){
	
	if (getPIDStatus() == Enable) {
		CompFilter();
		fufogetAltitude();
		calcPID(Phi, Theta, Psi, high);
	}
	PWM_Motor1 = Roll_sum + Yaw_sum;
	PWM_Motor2 = Pitch_sum - Yaw_sum;
	PWM_Motor3 = - Roll_sum + Yaw_sum;
	PWM_Motor4 = - Pitch_sum - Yaw_sum;
	
	if(High_sum >= 1000){				// gioi han PID altitude o muc 65% nang luong 
		High_sum = 1000;					// do khoi dong ton 40% nang luong nen altitude chi dc dung toi da 25% nang luong con lai
	}

	setPWM1(thrustRate, PWM_Motor1, High_sum);
	setPWM2(thrustRate, PWM_Motor2, High_sum);
	setPWM3(thrustRate, PWM_Motor3, High_sum);
	setPWM4(thrustRate, PWM_Motor4, High_sum);
}

void calcPID(float phiDesire, float thetaDesire, float psiDesire, float altitudeDesire){
	float phiAct, thetaAct, psiAct, GyrosR, GyrosP, GyrosY, altitudeBaroAct, altitudeAcc_Baro;
	phiAct = getPhiAngle();
	thetaAct = getThetaAngle();
	xuatTheta = thetaAct;
	psiAct = getPsiAngle();
	GyrosR = getGyrosOutputR();
	GyrosP = getGyrosOutputP();
	GyrosY = getGyrosOutputY();
	altitudeBaroAct = fufoGetBaroAltitude();
	altitudeLCD = altitudeBaroAct;
//	
//	if (thetaAct <= -40 || thetaAct >= 40 || phiAct <= -40 || phiAct >= 40){
//		T4CONbits.TON = 0;
//		_PTEN = 0;
//		fufoSendCharUART('G');
//		fufoSendCharUART('G');
//		setPIDStatus(Disable);
//		T2CONbits.TON = 0;
//		setState(Pending);	
//	}

//	Pitch_sum = calcPitchAngle(phiDesire, phiAct, GyrosP, KpPhi, KiPhi, KdPhi);
//	Roll_sum = calcRollAngle(thetaDesire, thetaAct, GyrosR, KpTheta, KiTheta, KdTheta);
//	Yaw_sum = calcYawAngle(psiDesire, psiAct, GyrosY, KpPsi, KiPsi, KdPsi);	
	Pitch_sum = 0;
	Roll_sum = 0;
	Yaw_sum = 0;
	if(getPIDAltitude() == Enable){
		altitudeAcc_Baro = altitudeFilter(altitudeBaroAct, getAccelAlt());
		altitudeLCD1 = getAccelAlt();
		altitudeLCD2 = altitudeAcc_Baro;
//		High_sum = calcAltitude(altitudeDesire, altitudeAct, KpAlt, KiAlt, KdAlt);
		setPIDAltitude(Disable);
	}
	High_sum = 0;

//	if(xuatTheta < 0){
//		fufoSendCharUART('-');
//	}
//	fufoSendIntUART((int)(xuatTheta*100));
//	fufoSendCharUART(',');
//
//	if(xuatPhi < 0){
//		fufoSendCharUART('-');
//	}
//	fufoSendIntUART((int)(xuatPhi*100));
//	fufoSendCharUART(',');
//
	if(altitudeLCD < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(altitudeLCD*1000));
	fufoSendCharUART('\t');

	if(altitudeLCD1 < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(altitudeLCD1*1000));
	fufoSendCharUART('\t');

	if(altitudeLCD2 < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(altitudeLCD2*1000));
	fufoSendCharUART('\t');

	fufoSendCharUART('\r');
	fufoSendCharUART('\n');
}

float calcRollAngle(float desireR_Angle, float actualR_Angle, float Gyros_OutputR, float KpR, float KiR, float KdR){
	eR = desireR_Angle - actualR_Angle;
	total_eR = total_eR + eR;
	P = KpR*eR;
	I = KiR*total_eR*0.01;
	D = KdR*Gyros_OutputR*(-1);
	Angle_sumR = P + I + D;
	return Angle_sumR;
}

float calcPitchAngle(float desireP_Angle, float actualP_Angle, float Gyros_OutputP, float KpP, float KiP, float KdP){
	eP = desireP_Angle - actualP_Angle;
	total_eP = total_eP + eP;
	P = KpP*eP;
	I = KiP*total_eP*0.01;
	D = KdP*Gyros_OutputP*(-1);
	Angle_sumP = P + I + D;
	return Angle_sumP;
}

float calcYawAngle(float desireY_Angle, float actualY_Angle, float Gyros_OutputY, float KpY, float KiY, float KdY){
	eY = desireY_Angle - actualY_Angle;
	total_eY = total_eY + eY;
	P = KpY*eY;
	I = KiY*total_eY*0.01;
	D = KdY*Gyros_OutputY*(-1);
	Angle_sumY = P + I + D;
	return Angle_sumY;
}

float calcAltitude(float desireAltitude, float actualAltitude, float KpA, float KiA, float KdA){
	float lcd;
	eA = desireAltitude - actualAltitude;
	actualAltitudeNew = actualAltitude ;
	total_eA = total_eA + eA;
	P = KpA*eA;
	I = KiA*total_eA*0.04;
	D = (float)(KdA*(actualAltitudeOld - actualAltitudeNew)*25); // chia 0.04
	actualAltitudeOld = actualAltitudeNew;
	PID_sum = P + I + D;
	return PID_sum;
}

void resetInstruction(void){
	Up = 0;
	Down = 0;
	Left = 0;
	R_Left = 0;
	Right = 0;
	R_Right = 0;
	Forward = 0;
	Backward = 0;
}

void resetSensor(void){
	Yaw_sum= 0;
	Pitch_sum = 0;
	Roll_sum = 0;
	High_sum = 0;
}

void resetPWM(void){
	PWM_Motor1 = 0; 
	PWM_Motor2 = 0;
	PWM_Motor3 = 0;
	PWM_Motor4 = 0;
	PWM1 = 0;
	PWM2 = 0;
	PWM3 = 0;
	PWM4 = 0;
}