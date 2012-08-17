/*Communication dspic30f4012 with ADXL345 in I2C*/
#define I2CBAUD 100000
#define NACK 1
#define ACK 0

void fufoStartI2C(void );							//Send start bit
void fufoRestartI2C(void);							//Send restart bit
void fufoStopI2C(void);								//Send stop bit
void fufoAckI2C(void);								//Send Acknowledgement
void fufoNackI2C(void);								//Send Not Acknowledgement
unsigned char fufoGetAckI2C(void);					//Receive Acknowledgement
void fufoWriteI2C(unsigned char c);					//Write a byte
unsigned char fufoWriteAckI2C(unsigned char c); 	//Write a byte, and receice Acknowledgement
unsigned char fufoReadI2C(void);					//Read a byte			
void fufoInitI2C(void);								//Initialize I2C modulde
void fufoWaitI2C(void);								//Wait I2C opetation finish
unsigned char fufoWriteByteI2C(unsigned char i2cADD, unsigned char ADD, unsigned char data);
unsigned char fufoReadByteI2C(unsigned char i2cADD, unsigned char ADD, unsigned char *data);
unsigned char fufoReadArrayI2C(unsigned char i2sADD, unsigned char ADD, unsigned char *data, unsigned char length);
