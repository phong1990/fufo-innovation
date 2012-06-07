#include "Control.h"

unsigned int Up, Down, Left, Right, Forward, Backward;
unsigned int Yaw_sum, Pitch_sum, Roll_sum;
unsigned int pidEnable = 0;
unsigned int thrustRate = 20;
unsigned int PWM_Motor1, PWM_Motor2, PWM_Motor3, PWM_Motor4;
unsigned char comandfromBluetooth;

void ControlFUFO(){
	getInstruction();
}

void getInstruction(void){
	getValuefromBluetooth();
	if(Up == 1 || Down == 1){
		setSetpoint(0,0,0);
	} else if(Forward == 1 || Backward == 1){
		setSetpoint(20,0,0);
	} else if(Left == 1 || Right == 1){
		setSetpoint(0,20,0);
	}
}

void getValuefromBluetooth(void){
	resetInstruction();
	comandfromBluetooth = fufoReceiveUART();
	IFS0bits.U1RXIF = 0;
	if(comandfromBluetooth == 'o'){
		Up = 1;
		thrustRate += 1;
	} else if(comandfromBluetooth == 'p'){
		Down = 1;
		thrustRate -= 1;
	} else if(comandfromBluetooth == 'w'){
		Forward = 1;
	} else if(comandfromBluetooth == 's'){
		Backward = 1;
	} else if(comandfromBluetooth == 'a'){
		Left = 1;
	} else if(comandfromBluetooth == 'd'){
		Right = 1;
	}
	if(thrustRate > 21){
		pidEnable = 0;
	} else {
		pidEnable = 0;
		resetAngle();
	}
}

void setSetpoint(unsigned int Phi, unsigned int Theta, unsigned int Psi){
	if (pidEnable == 1) {
		getValuefromSensor(Phi, Theta, Psi);
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

void getValuefromSensor(unsigned int phiDesire, unsigned int thetaDesire, unsigned int psiDesire){
	
}

void resetInstruction(void){
	Up = 0;
	Down = 0;
	Left = 0;
	Right = 0;
	Forward = 0;
	Backward = 0;
}

void resetAngle(void){
	Yaw_sum= 0;
	Pitch_sum = 0;
	Roll_sum = 0;
}
