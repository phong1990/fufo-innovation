#include "../FUFO.h"

unsigned int Up, Down, Left, Right, R_Left, R_Right, Forward, Backward;
float Yaw_sum, Pitch_sum, Roll_sum;
unsigned int pidEnable = 0;
unsigned int thrustRate = 0;
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
float e = 0;
float total_e = 0;
float Angle_sum;
//float KpTheta = 1;
unsigned int userInput;


int getThrustRate(void){
	return thrustRate;	
}

void setThrustRate(unsigned int Thrust){
	thrustRate = Thrust;
}

int getUserInput(void){
	return userInput;	
}

void controlFUFO(void){
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
		setSetpoint(0,0,0);
	} else if(Backward == 1){
		setSetpoint(0,0,0);
	} else if(Left == 1){
		setSetpoint(0,-20,0);
	} else if(Right == 1){
		setSetpoint(0,20,0);
	} else setSetpoint(0,0,0);
	
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
	} else {
		fufoCmd4LCD(LCD_HOMEL2);
		fufoOutputChar("loi");
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
	}
}

void getInstruction(void){
//	resetInstruction();
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
			pidEnable = 0;
			thrustRate = 22;
			setState(Landing);
		}
	} else if(comandfromBluetooth == 'w'){
		resetInstruction();
		Forward = 1;
//		KpTheta += 0.1;
//		PWM_Motor1 -= 1;
//		PWM_Motor3 += 1;
	} else if(comandfromBluetooth == 's'){
		resetInstruction();
		Backward = 1;
//		KpTheta -= 0.1;
//		PWM_Motor1 += 1;
//		PWM_Motor3 -= 1;
	} else if(comandfromBluetooth == 'a'){
		resetInstruction();
		Left = 1;
//		PWM1 += 1;
//		PWM_Motor2 -= 1;
//		PWM_Motor4 += 1;
	} else if(comandfromBluetooth == 'd'){
		resetInstruction();
		Right = 1;
//		PWM3 += 1;
//		PWM_Motor2 += 1;
//		PWM_Motor4 -= 1;
	} else if(comandfromBluetooth == 'k'){
		R_Right = 1;
		PWM3 -= 1;
	} else if(comandfromBluetooth == 'n'){
		R_Left = 1;
		PWM1 -= 1;
	} else if(comandfromBluetooth == 'f'){
		if(pidEnable == 1){
			pidEnable = 0;
			T2CONbits.TON = 0;
			setState(Landing);
		} else 	pidEnable = 1;
	}
	if(comandfromBluetooth == 'f' || Up == 1 || Down == 1 || R_Left == 1 || R_Right == 1 || Left == 1 || Right == 1 || Forward == 1 || Backward == 1){
		userInput = 1;
	} else userInput = 0;
//	setPID4(KpTheta*10);
}

void setSetpoint(float Phi, float Theta, float Psi){
	
	if (pidEnable == 1) {
		CompFilter();
		calcAngle_sum(Phi, Theta, Psi);
	}
	PWM_Motor1 = Roll_sum + Yaw_sum;
	PWM_Motor2 = Pitch_sum - Yaw_sum;
	PWM_Motor3 = - Roll_sum + Yaw_sum;
	PWM_Motor4 = - Pitch_sum - Yaw_sum;

	setPWM1(thrustRate, PWM_Motor1, PWM1);
	setPWM2(thrustRate, PWM_Motor2, 0);
	setPWM3(thrustRate, PWM_Motor3, PWM3);
	setPWM4(thrustRate, PWM_Motor4, 0);
}

void calcAngle_sum(float phiDesire, float thetaDesire, float psiDesire){
	float phiAct, thetaAct, psiAct, Gyros;
	phiAct = getPhiAngle();
	thetaAct = getThetaAngle();
	Gyros = getGyrosOutput();
	if(thetaAct < 0){
		fufoSendCharUART('-');
	}
	fufoSendIntUART((int)thetaAct);
	fufoSendCharUART('\t');

	fufoSendIntUART(PDC1);
	fufoSendCharUART('\t');
	fufoSendIntUART(PDC3);
	fufoSendCharUART('\t');

//	fufoSendIntUART(KpTheta*10);
//	fufoSendCharUART('\t');
	
	//psiAct = getPsiAngle();
	//Pitch_sum = calcAngle(phiDesire, phiAct, KpPhi, KiPhi, KdPhi);
	Pitch_sum = 0;
	Roll_sum = calcRollAngle(thetaDesire, thetaAct, Gyros, KpTheta, KiTheta, KdTheta);
	//Yaw_sum = calcAngle(psiDesire, psiAct, KpPsi, KiPsi, KdPsi);
	Yaw_sum = 0;
	fufoSendCharUART('\r');
	fufoSendCharUART('\n');
}

float calcRollAngle(float desire_Angle, float actual_Angle, float Gyros_Output, float KpR, float KiR, float KdR){
	e = desire_Angle - actual_Angle;
	total_e = total_e + e;
//	if(total_e < 0){
//		fufoSendCharUART('-');
//	}
//	fufoSendIntUART(total_e);
//	fufoSendCharUART('\t');
	P = KpR*e;
	I = KiR*total_e*0.01;
	D = KdR*Gyros_Output;
	Angle_sum = P + I - D;
	return Angle_sum;
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