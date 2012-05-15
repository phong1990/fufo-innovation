//Definition ADXL345 accelerometer
#include "ADXL345.h"
#include "../I2C/I2C.h"

//---------------- Constantes ------------------
// ADXL345  Registers
#define ADXL345_DEVID                   0x00    // R     Device ID 
#define ADXL345_THRESH_TAP              0x1D    // R/W   Tap threshold 
#define ADXL345_OFSX                    0x1E    // R/W   X-axis offset 
#define ADXL345_OFSY                    0x1F    // R/W   Y-axis offset 
#define ADXL345_OFSZ                    0x20    // R/W   Z-axis offset 
#define ADXL345_DUR                     0x21    // R/W   Tap duration 
#define ADXL345_LATENT                  0x22    // R/W   Tap latency 
#define ADXL345_WINDOW                  0x23    // R/W   Tap window 
#define ADXL345_THRESH_ACT              0x24    // R/W   Activity threshold 
#define ADXL345_THRESH_INACT    		0x25    // R/W   Inactivity threshold 
#define ADXL345_TIME_INACT              0x26    // R/W   Inactivity time 
#define ADXL345_ACT_INACT_CTL   		0x27    // R/W   Axis enable control for activity and inactivity detection 
#define ADXL345_THRESH_FF               0x28    // R/W   Free-fall threshold 
#define ADXL345_TIME_FF                 0x29    // R/W   Free-fall time 
#define ADXL345_TAP_AXES                0x2A    // R/W   Axis control for single tap/double tap 
#define ADXL345_ACT_TAP_STATUS  		0x2B    // R     Source of single tap/double tap 
#define ADXL345_BW_RATE                 0x2C    // R/W   Data Rate and power mode control 
#define ADXL345_POWER_CTL               0x2D    // R/W   Power-saving features control 
#define ADXL345_INT_ENABLE              0x2E    // R/W   Interrupt enable control 
#define ADXL345_INT_MAP                 0x2F    // R/W   Interrupt mapping control 
#define ADXL345_INT_SOURCE              0x30    // R     Source of interrupts 
#define ADXL345_DATA_FORMAT             0x31    // R/W   Data format control 
#define ADXL345_DATAX0                  0x32    // R     X-Axis Data 0 
#define ADXL345_DATAX1                  0x33    // R     X-Axis Data 1 
#define ADXL345_DATAY0                  0x34    // R     Y-Axis Data 0 
#define ADXL345_DATAY1                  0x35    // R     Y-Axis Data 1 
#define ADXL345_DATAZ0                  0x36    // R     Z-Axis Data 0 
#define ADXL345_DATAZ1                  0x37    // R     Z-Axis Data 1 
#define ADXL345_FIFO_CTL                0x38    // R/W   FIFO control 
#define ADXL345_FIFO_STATUS             0x39    // R     FIFO status
#define ADXL345_OUTPUTS                 0x32

//-------------------------Functions-----------------------
//Initialize Accelerometer
unsigned char fufoInitAccel(void) {
	unsigned char error = 0;
	error += fufoWriteByteI2C(ADXL345_I2C, ADXL345_DATA_FORMAT, 0x0A);
	error += fufoWriteByteI2C(ADXL345_I2C, ADXL345_POWER_CTL, 0x08);
	error += fufoWriteByteI2C(ADXL345_I2C, ADXL345_BW_RATE, 0x0A);
	return error;
}

//Read the values in an array of 3 integers, temp, accel_X, accel_Y, accel_Z.
//Return an error if it can not.
unsigned char fufoReadAccel(int *data) {
	unsigned char error = 0;
	error += fufoReadArrayI2C(ADXL345_I2C, ADXL345_OUTPUTS, (unsigned char*) data, 6);
	return error;
}
