#include "p30f4012.h"

#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM


void initPWMPort(void);
void initPWM(void);
void initPWMHardware(void);
void initPWMSoftware(void);
void setPWM1(unsigned int Thrust1, int PID_Motor1, int motor1);
void setPWM2(unsigned int Thrust2, int PID_Motor2, int motor2);
void setPWM3(unsigned int Thrust3, int PID_Motor3, int motor3);
void setPWM4(unsigned int Thrust4, int PID_Motor4, int motor4);