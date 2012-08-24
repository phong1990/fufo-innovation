//Definition BMP085 Barometric
#include "../FUFO.h"

//---------------- Constantes ------------------
// BMP085  Registers
#define TEMPERATURE 0
#define PRESSURE 1
#define OVER_SAMPLING_SETTING 3
#define AC1MSB 0xAA
float baroAltitude      = 0.0; 
float baroRawAltitude   = 0.0;
float baroGroundAltitude = 0.0;
float baroSmoothFactor   = 0.98;
long T = 0;
int overSamplingSetting = OVER_SAMPLING_SETTING;
int ac1 = 0, ac2 = 0, ac3 = 0;
unsigned int ac4 = 0, ac5 = 0, ac6 = 0;
int b1 = 0, b2 = 0, mb = 0, mc = 0, md = 0;
long pressure = 0;
long rawPressure = 0, rawTemperature = 0;
int pressureCount = 0;
float pressureFactor = 1/5.255;
int isReadPressure = 0;
float rawPressureSum = 0;
int rawPressureSumCount = 0;
//-------------------------Functions-----------------------

//Initialize BMP085
void initBaro(void) {
//   oversampling setting
//   0 = ultra low power
//   1 = standard
//   2 = high
//   3 = ultra high resolution
  overSamplingSetting = OVER_SAMPLING_SETTING;
  pressure = 0;
  baroGroundAltitude = 0;
  pressureFactor = 1/5.255;
  
  unsigned char datatemp[22];
  fufoReadArrayI2C(BMP085_I2C, AC1MSB, datatemp, 22);
  ac1 = datatemp[0] << 8 | datatemp[1];
  ac2 = datatemp[2] << 8 | datatemp[3];
  ac3 = datatemp[4] << 8 | datatemp[5];
  ac4 = datatemp[6] << 8 | datatemp[7];
  ac5 = datatemp[8] << 8 | datatemp[9];
  ac6 = datatemp[10] << 8 | datatemp[11];
  b1 = datatemp[12] << 8 | datatemp[13];
  b2 = datatemp[14] << 8 | datatemp[15];
  mb = datatemp[16] << 8 | datatemp[17];
  mc = datatemp[18] << 8 | datatemp[19];
  md = datatemp[20] << 8 | datatemp[21];
  //test constants values
//  fufoOutputUint(ac6);
//  fufoDat4LCD(',');
//  fufoOutputUint(ac5);
//  fufoCmd4LCD(LCD_HOMEL2);
//  fufoDelayMs(2);
//  fufoOutputInt(mc);
//  fufoDat4LCD(',');
//  fufoOutputInt(md);
  //end test constants values
  requestRawTemperature();
  fufoDelayMs(5);
  isReadPressure = 0;
  pressureCount = 0;
  measureBaro();
  fufoDelayMs(26);
  //fufoDelayMs(5); // delay for temperature

  measureBaro();
	fufoDelayMs(26);
  //fufoDelayMs(10); // delay for pressure
  
  measureGroundBaro();
  // check if measured ground altitude is valid
  while (abs(baroRawAltitude - baroGroundAltitude) > 10) {
    fufoDelayMs(26);
    measureGroundBaro();
  }
  baroAltitude = baroGroundAltitude;
}

//Read the values in an array of 2 integers baro_temp, baro_pressure. Return an error if it can not
unsigned char fufoReadBaro(unsigned int *data);

void fufoRequestRawPressure() {
  fufoWriteByteI2C(BMP085_I2C, 0xF4, 0x34 + (overSamplingSetting<<6));
}

long readRawPressure() {
  unsigned char dataRawPressure[3];
  fufoReadArrayI2C(BMP085_I2C, 0xF6, dataRawPressure, 3);
  return (((long)dataRawPressure[0] << 16) | ((long)dataRawPressure[1] << 8) | ((long)dataRawPressure[2])) >> (8 - overSamplingSetting);
}

void requestRawTemperature() {
  fufoWriteByteI2C(BMP085_I2C, 0xF4, 0x2E);
}

unsigned int readRawTemperature() {
  //unsigned char dataRawTemperature[2];
  //fufoReadArrayI2C(BMP085_I2C, 0xF6, dataRawTemperature, 2);
  unsigned char dataRawTemperatureM[1];
  unsigned char dataRawTemperatureL[1];
  fufoReadByteI2C(BMP085_I2C, 0xF6, dataRawTemperatureM);
  fufoReadByteI2C(BMP085_I2C, 0xF7, dataRawTemperatureL);
  return ((long)dataRawTemperatureM[0] << 8) | ((long)dataRawTemperatureL[0]);
}

void measureBaro() {
  measureBaroSum();
  evaluateBaroAltitude();
}

void measureBaroSum() {
  // switch between pressure and tempature measurements
  // each loop, since it's slow to measure pressure
  if (isReadPressure) {
    rawPressureSum += readRawPressure();
	//rawPressureSum = readRawPressure();
	//fufoCmd4LCD(LCD_HOMEL2);
	//fufoDelayMs(5);
	//fufoOutputLong(rawPressureSum);
	rawPressureSumCount++;
    if (pressureCount == 4) {
      requestRawTemperature();
      pressureCount = 0;
      isReadPressure = 0;
    }
    else {
      fufoRequestRawPressure();
	  pressureCount++;
	}
    
  }
  else { // select must equal TEMPERATURE
    rawTemperature = (long)readRawTemperature();
    //fufoOutputLong(rawTemperature);
    fufoRequestRawPressure();
    isReadPressure = 1;
  }
}

void evaluateBaroAltitude(){ 
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;
  long tmp;

  //calculate true temperature
  x1 = ((long)rawTemperature - ac6) * ac5 >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
  b5 = x1 + x2;
  
  //test temperature
  T = (b5 + 8) >> 4;
  //fufoOutputLong(T);
  //end test temperature

  if (rawPressureSumCount == 0) { // may occure at init time that no pressure have been read yet!
    return;
  }
  rawPressure = rawPressureSum / rawPressureSumCount;
  //rawPressure = rawPressureSum;
  rawPressureSum = 0.0;
  rawPressureSumCount = 0;
  
  //calculate true pressure
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11; 
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
 
  // Real Bosch formula - b3 = ((((int32_t)ac1 * 4 + x3) << overSamplingSetting) + 2) >> 2;
  // The version below is the same, but takes less program space
  tmp = ac1;
  tmp = (tmp * 4 + x3) << overSamplingSetting;
  b3 = (tmp + 2) >> 2;
 
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
  b7 = ((unsigned long) rawPressure - b3) * (50000 >> overSamplingSetting);
  p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;
    
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  pressure = (p + ((x1 + x2 + 3791) >> 4));
  //test calc first pressure
  
//  fufoOutputLong(pressure);
  //end test calc first pressure  
  baroRawAltitude = 44330 * (1 - pow(pressure/101325.0, pressureFactor)); // returns absolute baroAltitude in meters
  baroAltitude = filterSmooth(baroRawAltitude, baroAltitude, baroSmoothFactor);
}

float getBaroAltitude() {
  return baroAltitude - baroGroundAltitude;
}

float  getBaroAltitudeR() {
 return baroAltitude;
}
float  fufoGetBaroGAltitude() {
 return baroGroundAltitude;
}

void measureGroundBaro() {
  // measure initial ground pressure (multiple samples)
  float altSum = 0.0;
  int i;
  for (i=0; i < 25; i++) {
    measureBaro();
	altSum += baroRawAltitude;
    fufoDelayMs(26);
  }
  baroGroundAltitude = altSum / 25;
}

float filterSmooth(float currentData, float previousData, float smoothFactor) {
  if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
  {
    return (currentData * (1.0 - smoothFactor) + (previousData * smoothFactor)); 
  }
  return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
}
