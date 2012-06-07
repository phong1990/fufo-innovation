#include "p30f4012.h"

#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fpwm		50

void initPWMPort(void);
int initPWM(unsigned int Fcy,unsigned int initDutyCycleValue);
void initPWMHardware(unsigned int initDutyCycleValue);
void initPWMSoftware(void);