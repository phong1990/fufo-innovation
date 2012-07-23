#include "../FUFO.h"

unsigned int Up, Down, Left, Right, R_Left, R_Right, Forward, Backward;
float Yaw_sum, Pitch_sum, Roll_sum;
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
float total_eR = 0;
float total_eP = 0;
float total_eY = 0;
float Angle_sumR;
float Angle_sumP;
float Angle_sumY;
//float KpTheta = 10;
//float KiTheta = 2.09;
//float KdPhi = 1.0163;
//float KpPsi = 9;
unsigned int userInput;
float xuatLCD = 0;
float xuatLCD1 = 0;
float TT = -1.05;


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
	PID = getPIDStatus();
//	if(Up == 1){
//		setSetpoint(0,0,0);
//	} else if (Down == 1){
//		setSetpoint(0,0,0);
//	} else if(Forward == 1){
//		setSetpoint(20,0,0);
//	} else if (Backward == 1){
//		setSetpoint(-20,0,0);
//	} else if(Left == 1){
//		setSetpoint(0,20,0);
//	} else if (Right == 1){
//		setSetpoint(0,-20,0);
//	} else setSetpoint(0,0,0);
	if(Forward == 1){
		setSetpoint(0,-14,-1.05);
	} else if(Backward == 1){
		setSetpoint(0,16,-1.05);
	} else if(Left == 1){
		setSetpoint(-15,1,-1.05);
	} else if(Right == 1){
		setSetpoint(15,1,-1.05);
	} else setSetpoint(0,1,-1.05);
	
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
		Up = 1;
		thrustRate += 1;
		//pidEnable = 1;
		//pidEnable = 0;
		T2CONbits.TON = 1;
		setState(Hovering);
		fufoSendCharUART('y');
		fufoSendCharUART('\r');
		fufoSendCharUART('\n');
	}
}

void getInstruction(void){
	resetInstruction();
	setConnectStatus(Disable);
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		Up = 1;
		thrustRate += 1;
		if(thrustRate > 22){
			//pidEnable = 1;
			//pidEnable = 0;
			//setState(Hovering);
			if(thrustRate > 100) thrustRate = 100;
		}
	} else if(comandfromBluetooth == 'p'){
		Down = 1;
		thrustRate -= 1;
		if (thrustRate < 23){
			T2CONbits.TON = 0;
			setPIDStatus(Disable);
			thrustRate = 22;
			setState(Landing);
		}
	} else if(comandfromBluetooth == 'w'){
//		resetInstruction();
//		Forward = 1;
//		TT += 0.1;
//		KpTheta += 0.1;
//		KdPhi += 0.1;
//		PWM_Motor1 -= 1;
//		PWM_Motor3 += 1;
	} else if(comandfromBluetooth == 's'){
//		resetInstruction();
//		Backward = 1;
//		TT -= 0.1;
//		KpTheta -= 0.1;
//		KdPhi -= 0.1;
//		PWM_Motor1 += 1;
//		PWM_Motor3 -= 1;
	} else if(comandfromBluetooth == 'a'){
//		resetInstruction();
		Left = 1;
//		PWM2 += 1;
//		PWM1 += 1;
//		PWM_Motor2 -= 1;
//		PWM_Motor4 += 1;
	} else if(comandfromBluetooth == 'd'){
//		resetInstruction();
		Right = 1;
//		PWM4 += 1;
//		PWM3 += 1;
//		PWM_Motor2 += 1;
//		PWM_Motor4 -= 1;
	} else if(comandfromBluetooth == 'n'){
		R_Left = 1;
//		TT += 1;
//		KpPsi += 1;
	} else if(comandfromBluetooth == 'k'){
		R_Right = 1;
//		TT -= 1;
//		KpPsi -= 1;
	} else if(comandfromBluetooth == 'f'){
		_RE8 = 1;
		if(PID == Enable){
//			setPIDStatus(Disable);
//			T2CONbits.TON = 0;
			setState(Landing);
		} else 	setPIDStatus(Enable);
	}
	if(comandfromBluetooth == 'f' || comandfromBluetooth == 'y' || Up == 1 || Down == 1 || R_Left == 1 || R_Right == 1 || Left == 1 || Right == 1 || Forward == 1 || Backward == 1){
		userInput = 1;
		setConnectStatus(Enable);
	} else userInput = 0;
	xuatLCD = TT;
//	xuatLCD1 = KdTheta;
}

void setSetpoint(float Phi, float Theta, float Psi){
	
	if (PID == Enable) {
		CompFilter();
		calcAngle_sum(Phi, Theta, Psi);
	}
	PWM_Motor1 = Roll_sum + Yaw_sum;
	PWM_Motor2 = Pitch_sum - Yaw_sum;
	PWM_Motor3 = - Roll_sum + Yaw_sum;
	PWM_Motor4 = - Pitch_sum - Yaw_sum;

	setPWM1(thrustRate, PWM_Motor1, PWM1);
	setPWM2(thrustRate, PWM_Motor2, PWM2);
	setPWM3(thrustRate, PWM_Motor3, PWM3);
	setPWM4(thrustRate, PWM_Motor4, PWM4);
}

void calcAngle_sum(float phiDesire, float thetaDesire, float psiDesire){
	float phiAct, thetaAct, psiAct, GyrosR, GyrosP, GyrosY;
	phiAct = getPhiAngle();
	thetaAct = getThetaAngle();
	psiAct = getPsiAngle();
	GyrosR = getGyrosOutputR();
	GyrosP = getGyrosOutputP();
	GyrosY = getGyrosOutputY();
	if(GyrosY < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)GyrosY);
	fufoSendCharUART('\t');

	if(psiAct < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)psiAct);
	fufoSendCharUART('\t');

//	fufoSendIntUART(PDC1);
//	fufoSendCharUART('\t');
//	fufoSendIntUART(PDC3);
//	fufoSendCharUART('\t');

	if(xuatLCD < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)(xuatLCD*100));
	fufoSendCharUART('\t');

//	fufoSendIntUART(thrustRate);
//	fufoSendCharUART('\t');
	
	Pitch_sum = calcPitchAngle(phiDesire, phiAct, GyrosP, KpPhi, KiPhi, KdPhi);
	Roll_sum = calcRollAngle(thetaDesire, thetaAct, GyrosR, KpTheta, KiTheta, KdTheta);
	//Roll_sum = 0;
	Yaw_sum = calcYawAngle(psiDesire, psiAct, GyrosY, KpPsi, KiPsi, KdPsi);
	//Yaw_sum = 0;
	fufoSendCharUART('\r');
	fufoSendCharUART('\n');
}

float calcRollAngle(float desireR_Angle, float actualR_Angle, float Gyros_OutputR, float KpR, float KiR, float KdR){
	eR = desireR_Angle - actualR_Angle;
	total_eR = total_eR + eR;
	P = KpR*eR;
	I = KiR*total_eR*0.01;
	D = KdR*Gyros_OutputR;
	Angle_sumR = P + I - D;
	return Angle_sumR;
}

float calcPitchAngle(float desireP_Angle, float actualP_Angle, float Gyros_OutputP, float KpP, float KiP, float KdP){
	eP = desireP_Angle - actualP_Angle;
	total_eP = total_eP + eP;
	P = KpP*eP;
	I = KiP*total_eP*0.01;
	D = KdP*Gyros_OutputP;
	Angle_sumP = P + I - D;
	return Angle_sumP;
}

float calcYawAngle(float desireY_Angle, float actualY_Angle, float Gyros_OutputY, float KpY, float KiY, float KdY){
	eY = desireY_Angle - actualY_Angle;
	total_eY = total_eY + eY;
	P = KpY*eY;
	I = KiY*total_eY*0.01;
	D = KdY*Gyros_OutputY;
	Angle_sumY = P + I - D;
	return Angle_sumY;
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