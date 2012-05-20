/*Communication dspic30f4012 with ADXL345 in I2C*/
#include "p30f4012.h"
#include "I2C.h"
	
#define I2CWRITE 0
#define I2CREAD 1
#define FOSC 7372800

//Send start bit
void fufoStartI2C(void ) {
	//Enable a start condition
	I2CCONbits.SEN = 1;
	while(I2CCONbits.SEN);//Wait
}

//Send restart bit
void fufoRestartI2C(void) {
	//Enable a restart condition
	I2CCONbits.RSEN = 1;
	while(I2CCONbits.RSEN);//Wait
}

//Send stop bit
void fufoStopI2C(void) {
	//Enable a stop condition
	I2CCONbits.PEN = 1;
	while(I2CCONbits.PEN);//Wait
}

//Send Acknowledgement
void fufoAckI2C(void) {
	I2CCONbits.ACKDT = 0;//Set for ACK
	I2CCONbits.ACKEN = 1;//Send a ACK
	while(I2CCONbits.ACKEN);//wait for ACK to complete
}

//Send Not Acknowledgement
void fufoNackI2C(void) {
	I2CCONbits.ACKDT = 1;//Set for notACK
	I2CCONbits.ACKEN = 1;//Send a  notACK
	while(I2CCONbits.ACKEN);//wait for notACK to complete
	I2CCONbits.ACKDT = 0;//Set for ACK
}

//Receive Acknowledgement
unsigned char fufoGetAckI2C(void) {
	return (!I2CSTATbits.ACKSTAT);//Return ACK status
}

//Write a byte
void fufoWriteI2C(unsigned char c) {
	I2CTRN = c;
	while(I2CSTATbits.TBF);//check bus collision occurred and transmit is halted
}

//Write a byte, and receice Acknowledgement
unsigned char fufoWriteAckI2C(unsigned char c) {
	I2CTRN = c;
	while(I2CSTATbits.TRSTAT == 1);//Master transmit is in process
	return (!I2CSTATbits.ACKSTAT);
}

//Read a byte
unsigned char fufoReadI2C(void) {
	I2CCONbits.RCEN = 1;//Enable master receive
	while(!I2CSTATbits.RBF);//wait for receive buffer to be full
	return (I2CRCV);//return data in buffer
}

//Initialize I2C modulde	
void fufoInitI2C(void) {
	I2CCON = 0x8200; 
	
	//Baudrate setting
	I2CBRG = ((((FOSC/4)/I2CBAUD) - ((FOSC/4)/1111111))-1);
	
}

//Wait I2C opetation finish
void fufoWaitI2C(void) {
	while(!IFS0bits.MI2CIF);
	IFS0bits.MI2CIF = 0;
}

unsigned char fufoWriteByteI2C(unsigned char i2cADD, unsigned char ADD, unsigned char data) {
	unsigned char error = 0;
	fufoStartI2C();
	error += !fufoWriteAckI2C(i2cADD << 1 | I2CWRITE);
	error += !fufoWriteAckI2C(ADD);
	error += !fufoWriteAckI2C(data);
	fufoStopI2C();
	return error;
}

unsigned char fufoReadByteI2C(unsigned char i2cADD, unsigned char ADD, unsigned char *data) {
	unsigned char error = 0;
	fufoStartI2C();
	error += !fufoWriteAckI2C(i2cADD << 1 | I2CWRITE);
	error += !fufoWriteAckI2C(ADD);
	fufoRestartI2C();
	error += !fufoWriteAckI2C(i2cADD << 1 | I2CREAD);
	
	if(error) {
		fufoStopI2C();
		return error;
	}
	
	*data = fufoReadI2C();
	fufoNackI2C();
	fufoStopI2C();
	return error;
}

unsigned char fufoReadArrayI2C(unsigned char i2cADD, unsigned char ADD, unsigned char *data, unsigned char length) {
	unsigned char error = 0;
	fufoStartI2C();
	error += !fufoWriteAckI2C(i2cADD << 1 | I2CWRITE);
	error += !fufoWriteAckI2C(ADD);
	fufoRestartI2C();
	error += !fufoWriteAckI2C(i2cADD << 1 | I2CREAD);
	
	if(error) {
		fufoStopI2C();
		return error;
	}
	
	while((length--) > 1) {
		*data++ = fufoReadI2C();
		fufoAckI2C();
	}
	
	*data = fufoReadI2C();
	fufoNackI2C();
	fufoStopI2C();
	return error;
}
