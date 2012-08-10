
#define KpPhi 		19		//8.9		//1.08
#define KdPhi		5.8		//3.19	//1.0163
#define KiPhi		18		//2.19	//1.3481
#define KpTheta		19		//1.08		//9
#define KdTheta		5.8		//1.0163	//3.29
#define KiTheta		18	//1.3481 	//6.155
#define KpPsi		0
#define KdPsi		18.8
#define KiPsi		0
#define KpAlt			100
#define KdAlt			400
//#define KiAlt			0

void controlFUFO(void);
void getInstruction(void);
void getStartInstruction(void);
void getUpInstruction(void);
void checkConnection(void);
void checkBLConnection(void);
int getThrustRate(void);
void setThrustRate(int Thrust);
int getUserInput(void);
void setSetpoint(float phi, float theta, float psi, float high);
void getValuefromSensor();
void calcPID(float phiDesire, float thetaDesire, float psiDesire, float altitudeDesire);
float calcRollAngle(float desireR_Angle, float actualR_Angle, float Gyros_OutputR, float KpR, float KiR, float KdR);
float calcPitchAngle(float desireP_Angle, float actualP_Angle, float Gyros_OutputP, float KpP, float KiP, float KdP);
float calcYawAngle(float desireY_Angle, float actualY_Angle, float Gyros_OutputY, float KpY, float KiY, float KdY);
float calcAltitude(float desireAltitude, float actualAltitude, float KpA, float KiA, float KdA);
void resetInstruction(void);
void resetSensor(void);
void resetPWM(void);