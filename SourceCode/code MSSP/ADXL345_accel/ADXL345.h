//Definition ADXL345 accelerometer
//---------------- Constantes ------------------
// ADXL345 I2C address (just the first 7 bits)
#define ADXL345_I2C 0x53

unsigned char fufoInitAccel(void);//Initialize ADXL345
unsigned char fufoReadAccel(unsigned int *data);//Read the values in an array of 3 integers accel_X, accel_Y, accel_Z. Return an error if it can not
