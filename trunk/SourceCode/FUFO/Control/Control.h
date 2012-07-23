
#define KpPhi 		8.9		//1.08
#define KdPhi		3.19	//1.0163
#define KiPhi		2.19	//1.3481
#define KpTheta		8.9		//1.08		//9
#define KdTheta		3.19	//1.0163	//3.29
#define KiTheta		2.19	//1.3481 	//6.155
#define KpPsi		8.9
#define KdPsi		3.19
#define KiPsi		2.19

void controlFUFO(void);
void getInstruction(void);
void getStartInstruction(void);
void getUpInstruction(void);
void checkConnection(void);
void checkBLConnection(void);
int getThrustRate(void);
void setThrustRate(int Thrust);
int getUserInput(void);
void setSetpoint(float phi, float theta, float psi);
void getValuefromSensor();
void calcAngle_sum(float phiDesire, float thetaDesire, float psiDesire);
float calcRollAngle(float desireR_Angle, float actualR_Angle, float Gyros_OutputR, float KpR, float KiR, float KdR);
float calcPitchAngle(float desireP_Angle, float actualP_Angle, float Gyros_OutputP, float KpP, float KiP, float KdP);
float calcYawAngle(float desireY_Angle, float actualY_Angle, float Gyros_OutputY, float KpY, float KiY, float KdY);
void resetInstruction(void);
void resetSensor(void);
void resetPWM(void);