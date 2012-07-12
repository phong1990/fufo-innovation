
#define KpPhi 		0
#define KdPhi		0
#define KiPhi		0
//#define KpTheta		0.727
#define KdTheta		0
#define KiTheta		0	//0.424
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
float calcRollAngle(float desireR_Angle, float actualR_Angle, float KpR, float KiR, float KdR);
float calcPitchAngle(float desireP_Angle, float actualP_Angle, float KpP, float KiP, float KdP);
void resetInstruction(void);
void resetSensor(void);
void resetPWM(void);