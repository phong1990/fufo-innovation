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
#define L3G4200D_OUTPUTS 0x28

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
	error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG1, 0x1F);
	error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG3, 0x08);
	error += fufoWriteByteI2C(L3G4200D_I2C, L3G4200D_CTRL_REG4, 0x80);
	return error;
}

//Read the values in an array of 3 integers gyro_X, gyro_Y, gyro_Z.
//Return an error if it can not.
unsigned char fufoReadGyro(int *data) {
	unsigned char error = 0;
	error += fufoReadArrayI2C(L3G4200D_I2C, L3G4200D_OUTPUTS, (unsigned char*) data, 6);
	return error;
}
