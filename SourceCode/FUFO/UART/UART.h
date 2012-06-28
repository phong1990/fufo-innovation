//Communication dspic30f4012 with BlueTooth module (HC-06-S) in UART
#define UARTBAUD 38400
#define lineU1() fufoSendIntUART('\r');fufoSendIntUART('\n')

void fufoInitUART(void);
void fufoSendCharUART(unsigned char c);
void fufoSendStringUART(unsigned char *s);
void fufoSendIntUART(int a);
void fufoSendLongUART(long a);
unsigned char fufoReceiveUART(void);
