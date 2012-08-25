//Definition HMC5883L accelerometer
#include "../FUFO.h"

//---------------- Constantes ------------------
//#define SENSOR_GAIN 0x00  // +/- 0.7 Ga
//#define SENSOR_GAIN 0x20  // +/- 1.0 Ga (default)
//#define SENSOR_GAIN 0x40  // +/- 1.5 Ga
//#define SENSOR_GAIN 0x60  // +/- 2.0 Ga
//#define SENSOR_GAIN 0x80  // +/- 3.2 Ga
#define SENSOR_GAIN 0xA0  // +/- 3.8 Ga
//#define SENSOR_GAIN 0xC0  // +/- 4.5 Ga
//#define SENSOR_GAIN 0xE0  // +/- 6.5 Ga (not recommended)

#define HMC5883L_A_REGISTER 0x00
#define HMC5883L_B_REGISTER 0x01
#define HMC5883L_MODE_REGISTER 0x02
#define HMC5883L_DATAX0 0x03
#define HMC5883L_DATAX1 0x04
#define HMC5883L_DATAY0 0x07
#define HMC5883L_DATAY1 0x08
#define HMC5883L_DATAZ0 0x05
#define HMC5883L_DATAZ1 0x06
#define HMC5883L_STATUS_REGISTER 0x09
#define HMC5883L_A_IDN 0x10
#define HMC5883L_B_IDN 0x11
#define HMC5883L_C_IDN 0x12
//-------------------------Functions-----------------------
//Initialize HMC5883L
void fufoInitMagneto(void) {
	unsigned char error = 0;
	error += fufoWriteByteI2C(HMC5883L_I2C, HMC5883L_A_REGISTER, 0x18);
	error += fufoWriteByteI2C(HMC5883L_I2C, HMC5883L_B_REGISTER, SENSOR_GAIN);
	error += fufoWriteByteI2C(HMC5883L_I2C, HMC5883L_MODE_REGISTER, 0x00);
}

//Read the values in an array of 3 integers magneto_X, magneto_Y, magneto_Z
//Return an error if it can not.
unsigned char fufoReadMagneto(unsigned int *data) {
	unsigned char error = 0;
//	unsigned char datatemp[6];
//	error += fufoReadArrayI2C(HMC5883L_I2C, HMC5883L_DATAX0, datatemp, 6);
//	*data = ((datatemp[1] << 8)  | datatemp[0]) & (0x0FFF); //X_Axis
//	*(data+1) = ((datatemp[3] << 8) | datatemp[2]) & (0x0FFF); //Y_Axis
//	*(data+2) = ((datatemp[5] << 8) | datatemp[4])  & (0x0FFF); //Z_Axis
	unsigned char datatemp[1];
	unsigned char datatemp1[1];
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAX0, datatemp);
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAX1, datatemp1);
	*data = ((datatemp[0] << 8)) | (datatemp1[0]) ;
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAY0, datatemp);
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAY1, datatemp1);
	*(data + 1) = ((datatemp[0] << 8)) | (datatemp1[0]);
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAZ0, datatemp);
	error += fufoReadByteI2C(HMC5883L_I2C, HMC5883L_DATAZ1, datatemp1);
	*(data + 2) = ((datatemp[0] << 8)) | (datatemp1[0]);
	return error;
}


