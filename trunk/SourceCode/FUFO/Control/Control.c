#include "Control.h"
#include "../FUFO.h"

unsigned int Up, Down, Left, Right, Forward, Backward;
int Yaw_sum, Pitch_sum, Roll_sum;
unsigned int pidEnable = 0;
unsigned int thrustRate = 0;
int PWM_Motor1 = 0; 
int PWM_Motor2 = 0;
int PWM_Motor3 = 0;
int PWM_Motor4 = 0;
int phiActual, thetaActual, psiActual;
int gyro_output;
unsigned char comandfromBluetooth;
int P = 0;
int I = 0;
int D = 0;
int e = 0;
int total_e = 0;
int Angle_sum;
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
	if(Up == 1){
		setSetpoint(0,0,0);
	} else if (Down == 1){
		setSetpoint(0,0,0);
	} else if(Forward == 1){
		setSetpoint(20,0,0);
	} else if (Backward == 1){
		setSetpoint(-20,0,0);
	} else if(Left == 1){
		setSetpoint(0,20,0);
	} else if (Right == 1){
		setSetpoint(0,-20,0);
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
	} else {
		fufoCmd4LCD(LCD_CLEAR);
		fufoDat4LCD(comandfromBluetooth);
		fufoDelayMs(2000);
	}
}

void getStartInstruction(void){
	fufoCmd4LCD(LCD_HOMEL2);
	fufoOutputChar("vao  ");
	comandfromBluetooth = fufoReceiveUART();
	fufoOutputChar("qua  ");
	if(comandfromBluetooth == 'f'){ // ky tu f bao Start
		setState(Setup);
		fufoOutputChar("dc  ");
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
		if(thrustRate > 21){
			//pidEnable = 1;
			pidEnable = 0;
			setState(Hovering);
			if(thrustRate > 97) thrustRate = 97;
		}
	}
}

void getInstruction(void){
	resetInstruction();
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		Up = 1;
		thrustRate += 1;
		if(thrustRate > 22){
			//pidEnable = 1;
			pidEnable = 0;
			//setState(Hovering);
			if(thrustRate > 97) thrustRate = 97;
		}
	} else if(comandfromBluetooth == 'p'){
		Down = 1;
		thrustRate -= 1;
		if (thrustRate < 22){
			setState(Landing);
			pidEnable = 0;
			thrustRate = 21;
			resetSensor();
		}
	} else if(comandfromBluetooth == 'w'){
		Forward = 1;
//		PWM_Motor1 -= 1;
//		PWM_Motor3 += 1;
	} else if(comandfromBluetooth == 's'){
		Backward = 1;
//		PWM_Motor1 += 1;
//		PWM_Motor3 -= 1;
	} else if(comandfromBluetooth == 'a'){
		Left = 1;
//		PWM_Motor2 -= 1;
//		PWM_Motor4 += 1;
	} else if(comandfromBluetooth == 'd'){
		Right = 1;
//		PWM_Motor2 += 1;
//		PWM_Motor4 -= 1;
	}
	if(Up == 1 || Down == 1 || Left == 1 || Right == 1 || Forward == 1 || Backward == 1){
		userInput = 1;
	} else userInput = 0;
}

void setSetpoint(unsigned int Phi, unsigned int Theta, unsigned int Psi){
	if (pidEnable == 1) {
		getValuefromSensor();
		calcAngle_sum(Phi, Theta, Psi);
	} else {
		PWM_Motor1 = - Roll_sum + Yaw_sum;
		PWM_Motor2 = Pitch_sum - Yaw_sum;
		PWM_Motor3 = Roll_sum + Yaw_sum;
		PWM_Motor4 = - Pitch_sum - Yaw_sum;
	}
	setPWM1(thrustRate, PWM_Motor1);
	setPWM2(thrustRate, PWM_Motor2);
	setPWM3(thrustRate, PWM_Motor3);
	setPWM4(thrustRate, PWM_Motor4);
}

void getValuefromSensor(){
//	phiActual = getPhiActual();
//	thetaActual = getThetaActual();
//	psiActual = getPsiActual();
//	gyro_output = getGyro_output();
}

void calcAngle_sum(unsigned int phiDesire, unsigned int thetaDesire, unsigned int psiDesire){
	Pitch_sum = calcAngle(phiDesire, phiActual, KpPhi, KiPhi, KdPhi);
	Roll_sum = calcAngle(thetaDesire, thetaActual, KpTheta, KiTheta, KdTheta);
	Yaw_sum = calcAngle(psiDesire, psiActual, KpPsi, KiPsi, KdPsi);
}

int calcAngle(unsigned int desire_Angle, unsigned int actual_Angle, unsigned int Kp, unsigned int Ki, unsigned int Kd){
	e = desire_Angle - actual_Angle;
	total_e = total_e + e;
	P = Kp*e;
	I = Ki*total_e;
	D = Kd*gyro_output;
	Angle_sum = P + I + D;
	return Angle_sum;
}

void resetInstruction(void){
	Up = 0;
	Down = 0;
	Left = 0;
	Right = 0;
	Forward = 0;
	Backward = 0;
}

void resetSensor(void){
	Yaw_sum= 0;
	Pitch_sum = 0;
	Roll_sum = 0;
	gyro_output = 0;
}

