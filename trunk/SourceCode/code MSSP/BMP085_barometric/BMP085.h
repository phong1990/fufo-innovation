//Definition BMP085 Barometric
//---------------- Constantes ------------------
// BMP085 I2C address (just the first 7 bits)
#define BMP085_I2C 0x77

void fufoInitBaro(void);//Initialize BMP085
unsigned char fufoReadBaro(unsigned int *data);//Read the values in an array of 2 integers baro_temp, baro_pressure. Return an error if it can not
void fufoRequestRawPressure();
long fufoReadRawPressure();
void fufoRequestRawTemperature();
unsigned int fufoReadRawTemperature();
void fufoMeasureBaro();
void fufoMeasureBaroSum();
void fufoEvaluateBaroAltitude();
float  fufoGetBaroAltitude();
float  fufoGetBaroAltitudeR();
float  fufoGetBaroGAltitude();
void fufoMeasureGroundBaro();
float fufoFilterSmooth(float currentData, float previousData, float smoothFactor);
