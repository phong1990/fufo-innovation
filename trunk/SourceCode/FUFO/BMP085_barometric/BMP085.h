//Definition BMP085 Barometric
//---------------- Constantes ------------------
// BMP085 I2C address (just the first 7 bits)
#define BMP085_I2C 0x77

void fufoInitBaro(void);//Initialize BMP085
unsigned char fufoReadBaro(unsigned int *data);//Read the values in an array of 2 integers baro_temp, baro_pressure. Return an error if it can not
void fufoRequestRawPressure();
long readRawPressure();
void requestRawTemperature();
unsigned int readRawTemperature();
void measureBaro();
void measureBaroSum();
void evaluateBaroAltitude();
float  getBaroAltitude();
float  getBaroAltitudeR();
float  fufoGetBaroGAltitude();
void measureGroundBaro();
float filterSmooth(float currentData, float previousData, float smoothFactor);
