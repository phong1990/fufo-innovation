#include "p30f4012.h"
#include "../LCD/LCD.h"
#include "../Delay/DelayTMR1.h"
#include "../Bluetooth/Bluetooth.h"
#include "../UART/UART.h"
#include "../PWM/pwmControl.h"

void ControlFUFO();
void getInstruction(void);
void getValuefromBluetooth(void);
void setSetpoint(unsigned int phi, unsigned int theta, unsigned int psi);
void getValuefromSensor(unsigned int phiDesire, unsigned int thetaDesire, unsigned int psiDesire);
void resetInstruction(void);
void resetAngle(void);