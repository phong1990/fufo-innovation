//Communication dspic30f4012 with BlueTooth module (HC-06-S) in UART
#define UARTBAUD 38400
#define lineU1() fufoSendIntUART('\r');fufoSendIntUART('\n')

void fufoInitUART(void);
void fufoSendIntUART(int i);
void fufoSendCharUART(unsigned char c);
void fufoSendStringUART(unsigned char *s);
unsigned char fufoReceiveUART(void);
