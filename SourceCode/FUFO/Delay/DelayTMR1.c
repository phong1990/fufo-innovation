/*Communication dspic30f4012 with ADXL345 in I2C*/
#include "../FUFO.h"

//Delay ms
void fufoDelayMs(unsigned int n) {
	T1CONbits.TON = 1;//Use clock by Fcy, and prescale 1:1
	while(n--) {
		TMR1 = 0;
		while(TMR1 < COUNTMS);
	}
	T1CONbits.TON = 0;
	TMR1 = 0;
}

//Delay us
void fufoDelayUs (unsigned int n) {
	T1CONbits.TON = 1;//Use clock by Fcy, and prescale 1:1
	while(n--) {
		TMR1 = 0;
		while(TMR1 < COUNTUS);
	}
	T1CONbits.TON = 0;
	TMR1 = 0;
}
