//Definition L3G4200D gyroscope
//---------------- Constantes ------------------
// L3G4200D I2C address (just the first 7 bits)
#define L3G4200D_I2C 0x69

unsigned char fufoInitGyro(void);//Initialize L3D4200D
unsigned char fufoReadGyro(int *data);//Read the values in an array of 3 integers gyro_X, gyro_Y, gyro_Z. Return an error if it can not
