
#define KpPhi 		13.5		//19		//7.3		//19		//8.9		//1.08
#define KdPhi		4.1			//5.8		//3.19	//1.0163
#define KiPhi		15			//18		//2.19	//1.3481
#define KpTheta		13.5		//19		//7.3		//19		//1.08		//9
#define KdTheta		4.1			//5.8		//1.0163	//3.29
#define KiTheta		15			//18		//3		//18	//1.3481 	//6.155
#define KpPsi		0
//#define KdPsi		15
#define KiPsi		0
#define KpAlt			100
#define KdAlt			400
#define KiAlt			50

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
float calcRollAngle(float desireRoll_Angle, float actualRoll_Angle, float Gyros_OutputRoll, float KpRoll, float KiRoll, float KdRoll);
float calcPitchAngle(float desirePitch_Angle, float actualPitch_Angle, float Gyros_OutputPitch, float KpPitch, float KiPitch, float KdPitch);
float calcYawAngle(float desireYaw_Angle, float actualYaw_Angle, float Gyros_OutputYaw, float KpYaw, float KiYaw, float KdYaw);
float calcAltitude(float desireAltitude, float actualAltitude, float KpA, float KiA, float KdA);
void resetInstruction(void);
void resetSensor(void);
void resetPWM(void);
float setHigh_sum(float h_sum);
