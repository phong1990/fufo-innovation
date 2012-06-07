#include "p30f4012.h"

#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fpwm		50

void initPWMPort(void);
int initPWM(unsigned int Fcy,unsigned int DCValue);
void initPWMHardware(void);
void initPWMSoftware(void);
void setPWM1(unsigned int Thrust1, unsigned int PID_Motor1);
void setPWM2(unsigned int Thrust2, unsigned int PID_Motor2);
void setPWM3(unsigned int Thrust3, unsigned int PID_Motor3);
void setPWM4(unsigned int Thrust4, unsigned int PID_Motor4);