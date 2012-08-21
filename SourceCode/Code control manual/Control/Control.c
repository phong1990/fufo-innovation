#include "../FUFO.h"

unsigned int Up, Down, Left, Right, R_Left, R_Right, Forward, Backward;
float Yaw_sum, Pitch_sum, Roll_sum, High_sum;
int PID = 0;
int thrustRate = 0;
int PWM_Motor1 = 0; 
int PWM_Motor2 = 0;
int PWM_Motor3 = 0;
int PWM_Motor4 = 0;
unsigned char comandfromBluetooth;
float P = 0;
float I = 0;
float D = 0;
float e_Roll = 0;
float e_Pitch = 0; 
float e_Yaw = 0;
float eAlt = 0;
float total_e_Roll = 0;
float total_e_Pitch = 0;
float total_e_Yaw = 0;
float total_eAlt = 0;
float Angle_sumRoll;
float Angle_sumPitch;
float Angle_sumYaw;
float Altitude;
float actualAltitudeNew = 0;
float actualAltitudeOld = 0;
float PID_sum = 0;
//float KdAlt = 300;
unsigned int userInput;
float xuatPhong = 0;
float xuatThang = 0;
float xuatPhi = 0;
float xuatTheta = 0;
float phong = -3.01;
float thang = -2.77;		//-6.58;
int PID_Yaw = 0;
float altitude, altitudeR, altitudeG;
float altitudeLCD, altitudeLCD1, altitudeLCD2; 
float docao = 1;
float xuatdocao;
float KdAlt = 300;
float KpAlt = 100;
float KiAlt = 20;
//float KdTheta = 5.1;

int getThrustRate(void){
	return thrustRate;	
}

void setThrustRate(int Thrust){
	thrustRate = Thrust;
}

int getUserInput(void){
	return userInput;	
}

void setHigh_sum(float h_sum){
	High_sum = h_sum;
}

float getHigh_sum(void){
	return High_sum;
}

void controlFUFO(void){
	if(Forward == 1){
		setSetpoint(-3.01,-9.77,-1,docao);
	} else if(Backward == 1){
		setSetpoint(-3.01,7.23,-1,docao);
	} else if(Left == 1){
		setSetpoint(-10.01,-2.77,-1,docao);
	} else if(Right == 1){
		setSetpoint(3.99,-2.77,-1,docao);
	} else setSetpoint(-3.01,-2.77,-1,docao);
}

void checkConnection(void){
	comandfromBluetooth = fufoReceiveUART();
	if(comandfromBluetooth == 'n'){ // ky tu n bao da ket noi voi Phone
		setState(Pending);
//		fufoCmd4LCD(LCD_CLEAR);
//		fufoOutputChar("Phone connected!");
//		fufoDelayMs(500);
	} else if(comandfromBluetooth == 'c'){ // ky tu c bao da ket noi voi PC
		setState(Pending);
//		fufoCmd4LCD(LCD_CLEAR);
//		fufoOutputChar("PC connected!");
//		fufoDelayMs(500);
	}
}

void checkBLConnection(void){
	comandfromBluetooth = fufoReceiveUART();
	if(comandfromBluetooth == 'h'){ // ky tu n bao da ket noi Bluetooth
		setState(Verify);
//		fufoCmd4LCD(LCD_CLEAR);
//		fufoOutputChar("Bluetooth connected!");
		fufoDelayMs(200);
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
	}	
}

void getUpInstruction(void){
	resetInstruction();
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		_RE8 = 1;
//		Up = 1;
		thrustRate = 49;
		PID_Yaw = 0;
		setPIDStatus(Enable);
		setPIDAltitude(Enable);
		T2CONbits.TON = 1;
		setState(Hovering);
		fufoSendCharUART('y');
		fufoSendCharUART('\r');
		fufoSendCharUART('\n');
		_RE8 = 0;
	}
}

void getInstruction(void){
//	resetInstruction();
	setConnectStatus(Disable);
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		resetInstruction();
		Up = 1;
//		docao += 0.25;
//		thrustRate = 54;
		thrustRate += 1;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'p'){
		resetInstruction();
		Down = 1;
//		docao -= 0.25;
		thrustRate -= 1;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'w'){
		resetInstruction();
		Forward = 1;
//		thang += 0.2;
//		KdAlt += 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 's'){
		resetInstruction();
		Backward = 1;
//		thang -= 0.2;
//		KdAlt -= 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'a'){
		resetInstruction();
		Left = 1;
//		phong += 0.2;
//		KpAlt += 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'd'){
		resetInstruction();
		Right = 1;
//		phong -= 0.2;
//		KpAlt -= 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'n'){
		resetInstruction();
		R_Left = 1;
//		KiAlt += 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'k'){
		resetInstruction();
		R_Right = 1;
//		KiAlt -= 10;
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'r'){
//		if(Up == 1){
//			thrustRate = 50;
//		}	
		resetInstruction();
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'f'){
		resetInstruction();
		_RE8 = 1;
		setPIDAltitude(Disable);
		setHigh_sum(0);
		setState(Landing);
		fufoSendCharUART('S');
		fufoSendCharUART('S');
		userInput = On;
		setConnectStatus(Enable);
	} else if(comandfromBluetooth == 'y'){
		userInput = On;
		setConnectStatus(Enable);
	} else userInput = Off;
	xuatPhong = phong;
	xuatThang = thang;
	xuatdocao = thrustRate;
}

void setSetpoint(float Phi, float Theta, float Psi, float high){
	
	if (getPIDStatus() == Enable) {
		CompFilter();
		calcAltZ();
		calcPID(Phi, Theta, Psi, high); 
	}
	PWM_Motor1 = Roll_sum + Yaw_sum;
	PWM_Motor2 = Pitch_sum - Yaw_sum;
	PWM_Motor3 = - Roll_sum + Yaw_sum;
	PWM_Motor4 = - Pitch_sum - Yaw_sum;
	
	if(High_sum >= 1000){				// gioi han PID altitude o muc 65% nang luong 
		High_sum = 1000;					// do khoi dong ton 40% nang luong nen altitude chi dc dung toi da 25% nang luong con lai
	}
	if(High_sum <= 0){
		High_sum = 0;
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
	psiAct = getPsiAngle();
	GyrosR = getGyrosOutputR();
	GyrosP = getGyrosOutputP();
	GyrosY = getGyrosOutputY();
	altitudeBaroAct = getBaroAltitude();
	
	xuatTheta = thetaAct;
	xuatPhi = psiAct;
	if (thetaAct <= -40 || thetaAct >= 40 || phiAct <= -40 || phiAct >= 40){
		T4CONbits.TON = 0;
		_PTEN = 0;
		fufoSendCharUART('G');
		fufoSendCharUART('G');
		setPIDStatus(Disable);
		T2CONbits.TON = 0;
		setState(Pending);	
	}

	Pitch_sum = calcPitchAngle(phiDesire, phiAct, GyrosP, KpPhi, KiPhi, KdPhi);
	Roll_sum = calcRollAngle(thetaDesire, thetaAct, GyrosR, KpTheta, KiTheta, KdTheta);
	Yaw_sum = calcYawAngle(psiDesire, psiAct, GyrosY, KpPsi, KiPsi, KdPsi);	
//	Pitch_sum = 0;
//	Roll_sum = 0;
//	Yaw_sum = 0;
	High_sum = 0;
	if(getPIDAltitude() == Enable){
//		altitudeAcc_Baro = getAltitude(altitudeBaroAct);
		altitudeLCD = altitudeBaroAct;
//		High_sum = calcAltitude(altitudeDesire, altitudeBaroAct, KpAlt, KiAlt, KdAlt);
		setPIDAltitude(Disable);
	}

	if(altitudeLCD < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(altitudeLCD*1000));
	fufoSendCharUART('\t');

	if(xuatPhong < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(xuatPhong*100));
	fufoSendCharUART('\t');

	if(xuatThang < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(xuatThang*100));
	fufoSendCharUART('\t');

	if(xuatTheta < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(xuatTheta*1000));
	fufoSendCharUART('\t');

	if(xuatdocao < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(xuatdocao));
	fufoSendCharUART('\t');

	fufoSendCharUART('\r');
	fufoSendCharUART('\n');
}

float calcRollAngle(float desireRoll_Angle, float actualRoll_Angle, float Gyros_OutputRoll, float KpRoll, float KiRoll, float KdRoll){
	e_Roll = desireRoll_Angle - actualRoll_Angle;
	total_e_Roll = total_e_Roll + e_Roll;
	P = KpRoll*e_Roll;
	I = KiRoll*total_e_Roll*0.01;
	D = KdRoll*Gyros_OutputRoll*(-1);
	Angle_sumRoll = P + I + D;
	return Angle_sumRoll;
}

float calcPitchAngle(float desirePitch_Angle, float actualPitch_Angle, float Gyros_OutputPitch, float KpPitch, float KiPitch, float KdPitch){
	e_Pitch = desirePitch_Angle - actualPitch_Angle;
	total_e_Pitch = total_e_Pitch + e_Pitch;
	P = KpPitch*e_Pitch;
	I = KiPitch*total_e_Pitch*0.01;
	D = KdPitch*Gyros_OutputPitch*(-1);
	Angle_sumPitch = P + I + D;
	return Angle_sumPitch;
}

float calcYawAngle(float desireYaw_Angle, float actualYaw_Angle, float Gyros_OutputYaw, float KpYaw, float KiYaw, float KdYaw){
	e_Yaw = desireYaw_Angle - actualYaw_Angle;
	total_e_Yaw = total_e_Yaw + e_Yaw;
	P = KpYaw*e_Yaw;
	I = KiYaw*total_e_Yaw*0.01;
	D = KdYaw*Gyros_OutputYaw*(-1);
	Angle_sumYaw = P + I + D;
	return Angle_sumYaw;
}

float calcAltitude(float desireAltitude, float actualAltitude, float KpA, float KiA, float KdA){
	eAlt = desireAltitude - actualAltitude;
	actualAltitudeNew = actualAltitude ;
	total_eAlt = total_eAlt + eAlt;
	P = KpA*eAlt;
	I = KiA*total_eAlt*0.04;
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
}
