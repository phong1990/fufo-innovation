#include "math.h"
#include "p30f4012.h"
#include "../ADXL345_accel/ADXL345.h"
#include "../L3G4200D_gyro/L3G4200D.h"
#include "../Delay/DelayTMR1.h"
#include "../I2C/I2C.h"
#include "../UART/UART.h"

#define k		0.98
#define kAlt	0.98
#define kH		0.02
#define Klpf	0.98
#define k_h_est	-0.008;
#define	k_vz_est - 0.0001;
#define convertAccel  0.0039;
#define convertGyro  0.00875;

void CalcFirstAngle(void);
void fufoGetAngleAccel(void);
void fufoGetAngleGyros(void);
void fufoGetRateAngle(void);
int calcRateAngle(void);
void CompFilter(void);
void HighPassFilter(void);
float getAltitude(float baroAlt);
void calcAltZ(void);