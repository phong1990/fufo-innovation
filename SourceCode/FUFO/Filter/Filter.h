#include "math.h"
#include "p30f4012.h"
#include "../ADXL345_accel/ADXL345.h"
#include "../L3G4200D_gyro/L3G4200D.h"
#include "../Delay/DelayTMR1.h"
#include "../I2C/I2C.h"
#include "../UART/UART.h"

#define k		0.98
#define convertAccel  0.0039;
#define convertGyro  0.00875;

void fufoGetAngle(void);
void fufoGetRateAngle(void);
void CompFilter(void);