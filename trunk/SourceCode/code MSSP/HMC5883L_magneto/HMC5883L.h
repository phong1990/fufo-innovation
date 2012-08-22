//Definition HMC5883L magnetometer
//---------------- Constantes ------------------
// HMC5883L I2C address (just the first 7 bits)
#define HMC5883L_I2C 0x1E
#define HMC5883L_IDN 0x10

unsigned char fufoInitMagneto(void);//Initialize HMC5883L
unsigned char fufoReadMagneto(unsigned int *data);//Read the values in an array of 3 integers magneto_X, magneto_Y, magneto_Z. Return an error if it can not
void fufoCalcAngleMag();//Calculate Angle from HMC5883L