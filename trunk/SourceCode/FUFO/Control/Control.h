#include "p30f4012.h"
#include "../LCD/LCD.h"
#include "../Delay/DelayTMR1.h"
#include "../Bluetooth/Bluetooth.h"
#include "../UART/UART.h"
#include "../PWM/pwmControl.h"

#define KpPhi 		300
#define KdPhi		0
#define KiPhi		0
#define KpTheta		300
#define KdTheta		0
#define KiTheta		0
#define KpPsi		0
#define KdPsi		0
#define KiPsi		0

void controlFUFO(void);
void getInstruction(void);
void getStartInstruction(void);
void getUpInstruction(void);
void checkConnection(void);
void checkBLConnection(void);
int getThrustRate(void);
void setThrustRate(unsigned int Thrust);
int getUserInput(void);
void setSetpoint(float phi, float theta, float psi);
void getValuefromSensor();
void calcAngle_sum(float phiDesire, float thetaDesire, float psiDesire);
float calcAngle(float desire_Angle, float actual_Angle, float Kp, float Ki, float Kd);
void resetInstruction(void);
void resetSensor(void);