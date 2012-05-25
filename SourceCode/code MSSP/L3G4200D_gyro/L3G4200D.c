//Definition L3G4200D gyroscope
#include "L3G4200D.h"
#include "../I2C/I2C.h"
//---------------- Constantes ------------------
// L3G4200D  Registers
#define L3G4200D_WHO_AM_I 0x0F

#define L3G4200D_CTRL_REG1 0x20
#define L3G4200D_CTRL_REG2 0x21
#define L3G4200D_CTRL_REG3 0x22
#define L3G4200D_CTRL_REG4 0x23
#define L3G4200D_CTRL_REG5 0x24
#define L3G4200D_REFERENCE 0x25
#define L3G4200D_OUT_TEMP 0x26
#define L3G4200D_STATUS_REG 0x27

#define L3G4200D_OUT_X_L 0x28
#define L3G4200D_OUT_X_H 0x29
#define L3G4200D_OUT_Y_L 0x2A
#define L3G4200D_OUT_Y_H 0x2B
#define L3G4200D_OUT_Z_L 0x2C
#define L3G4200D_OUT_Z_H 0x2D


#define L3G4200D_FIFO_CTRL_REG 0x2E
#define L3G4200D_FIFO_SRC_REG 0x2F

#define L3G4200D_INT1_CFG 0x30
#define L3G4200D_INT1_SRC 0x31
#define L3G4200D_INT1_THS_XH 0x32
#define L3G4200D_INT1_THS_XL 0x33
#define L3G4200D_INT1_THS_YH 0x34
#define L3G4200D_INT1_THS_YL 0x35
#define L3G4200D_INT1_THS_ZH 0x36
#define L3G4200D_INT1_THS_ZL 0x37
#define L3G4200D_INT1_DURATION 0x38


//-------------------------Functions-----------------------
//Initialize Gyroscope
unsigned char fufoInitGyro(void) {
	unsigned char error = 0;
	error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG1, 0x0F);
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG2, 0x00);
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG3, 0x08);
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG4, 0x00);// scale = 250
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG4, 0x10);// scale = 500
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG4, 0x20);// scale = 2000
	//error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG5, 0x00);
	return error;
}

//Read the values in an array of 3 integers gyro_X, gyro_Y, gyro_Z.
//Return an error if it can not.
unsigned char fufoReadGyro(unsigned int *data) {
	unsigned char error = 0;
	unsigned char datatemp[6];
	error += fufoReadArrayI2C(L3G4200D_I2C, (L3G4200D_OUT_X_L | 0x80), datatemp, 6);
	*data = (datatemp[1] << 8) | datatemp[0]; //X_Axis
	*(data+1) = (datatemp[3] << 8) | datatemp[2]; //Y_Axis
	*(data+2) = (datatemp[5] << 8) | datatemp[4]; //Z_Axis
//	unsigned char datatemp[1];
//	unsigned char datatemp1[1];
//	error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_X_L, datatemp);
//    error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_X_H, datatemp1);
//	*data = (datatemp1[0] << 8) | datatemp[0];
//	error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_Y_L, datatemp);
//    error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_Y_H, datatemp1);
//	*(data + 1) = (datatemp1[0] << 8) | datatemp[0]; 
//	error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_Z_L, datatemp);
//    error += fufoReadByteI2C(L3G4200D_I2C, L3G4200D_OUT_Z_H, datatemp1);
//	*(data + 2) = (datatemp1[0] << 8) | datatemp[0];  
	return error;
}
