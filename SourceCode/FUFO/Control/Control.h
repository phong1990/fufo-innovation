#include "p30f4012.h"
#include "../LCD/LCD.h"
#include "../Delay/DelayTMR1.h"
#include "../Bluetooth/Bluetooth.h"
#include "../UART/UART.h"
#include "../PWM/pwmControl.h"

#define KpPhi 		0
#define KdPhi		0
#define KiPhi		0
#define KpTheta		0
#define KdTheta		0
#define KiTheta		0
#define KpPsi		0
#define KdPsi		0
#define KiPsi		0

void controlFUFO(void);
void getInstruction(void);
int getThrustRate(void);
void getValuefromBluetooth(void);
void setSetpoint(unsigned int phi, unsigned int theta, unsigned int psi);
void getValuefromSensor();
void calcAngle_sum(unsigned int phiDesire, unsigned int thetaDesire, unsigned int psiDesire);
int calcAngle(unsigned int desire_Angle, unsigned int actual_Angle, unsigned int Kp, unsigned int Ki, unsigned int Kd);
void resetInstruction(void);
void resetSensor(void);