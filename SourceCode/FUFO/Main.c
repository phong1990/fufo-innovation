#include "FUFO.h"


	_FOSC(CSW_FSCM_OFF & XT_PLL8);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)


//Cac prototype cho cac chuong trinh con
void initFUFO(void);

//Cac bien toan cuc
unsigned char receiOK[25];
unsigned int index = 0;
int FUFO_thrust = 0;
unsigned int userInputFlag = 0;
unsigned int FUFO_State;
int Connection = 1;
int i = 0;
unsigned char command;
unsigned int PIDControl = 0;
int motor1, motor2, motor3, motor4;
int value = 0;
//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	//T2CONbits.TON = 1;		//timer 2 on
	while(1){
		FUFO_State = getState();
		switch(FUFO_State){
			case Start: // trang thai Start
					initFUFO();					
					break;

			case Waiting_for_connection: // Trang thai Waiting for connection
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Welcome to FUFO");
					fufoDelayMs(10);
					fufoCmd4LCD(LCD_HOMEL2);
					fufoOutputChar("Wait for connect");
					checkBLConnection();
					setConnectStatus(1);
					break;

			case Verify: // Trang thai Verify
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Choose connect!");
					checkConnection();
					break;

			case Pending: // Trang thai Pending 
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Press Start  ");
					getStartInstruction();
					break;

			case Setup: // Trang thai Setup
					fufoGetRateAngle(); // calc R0
					FUFO_thrust = getThrustRate();
					FUFO_thrust++;
					if(FUFO_thrust >= 44) {
						FUFO_thrust = 44;
						//setState(Ready);
						//T2CONbits.TON = 1;
					}
					setThrustRate(FUFO_thrust);
					controlFUFO();
					break;

			case Ready: // Trang thai Ready
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Press Up!");
					getUpInstruction();
					break;

			case Hovering: // Trang thai Hovering
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Thrust :");
					//fufoOutputInt(Fcy/Fpwm - 1);
					fufoCmd4LCD(LCD_HOMEL2);
					fufoOutputInt(getThrustRate());
//					fufoOutputChar("Kp Theta: ");
//					fufoOutputInt(getPID4());
//					fufoOutputChar(" ");
					if (userInputFlag == 0){
						getInstruction();
						userInputFlag = getUserInput();
					}
					break;
			
			case Landing: // Trang thai Landing
					// Auto landing
					motor1 = 1;
					motor2 = 1;
					motor3 = 1;
					motor4 = 1;
					if(PDC1 >= 3000){
						motor1 = 0;
						PDC1 -= 80;
//						fufoCmd4LCD(LCD_CLEAR);
//						fufoOutputChar("motor1");
//						fufoDelayMs(100);
					}
					if(PDC2 >= 3000){
						motor2 = 0;
						PDC2 -= 80;
//						fufoCmd4LCD(LCD_CLEAR);
//						fufoOutputChar("motor2");
//					//	fufoDelayMs(100);
					}
					if(PDC3 >= 3000){
						motor3 = 0;
						PDC3 -= 80;
//						fufoCmd4LCD(LCD_CLEAR);
//						fufoOutputChar("motor3");
//					//	fufoDelayMs(100);
					}
					if(getPR4() >= 800){
						motor4 = 0;
						value -= 20;
						setPR4(value);
//						fufoCmd4LCD(LCD_CLEAR);
//						fufoOutputChar("motor4");
//					//	fufoDelayMs(100);
					}
					if(motor1 == 1 && motor2 == 1 && motor3 == 1 && motor4 == 1) {
						//FUFO_thrust = 0;
						setPIDStatus(Disable);
						T2CONbits.TON = 0;
						fufoCmd4LCD(LCD_CLEAR);
						fufoOutputChar("xong");
						fufoDelayMs(1000);
						setState(Pending);	
					}
					break;

			case End: 
					break;
		}


//		fufoCmd4LCD(LCD_CLEAR);
//		fufoDelayMs(5);
//		fufoOutputChar("Thrust: ");
//		fufoOutputInt(getThrustRate());
//		fufoCmd4LCD(LCD_HOMEL2);
//		fufoOutputInt(PDC2);
//		if (userInputFlag == 0){
//			getInstruction();
//			userInputFlag = getUserInput();
//		}
	}
}

//Ham khoi tao cac chuong trinh cua FUFO
void initFUFO(void){
	fufoInitLCDPorts();
	fufoDelayMs(10);
	fufoInitLCD();
	fufoDelayMs(10);
	fufoOutputChar("Please wait");
	fufoCmd4LCD(LCD_HOMEL2);
	initPWM();		// khoi tao PWM voi tan so thuc thi lenh Fcy;
							// do rong xung ban dau 1ms (1843).
	fufoDelayMs(200);
	fufoOutputChar("...");
	fufoDelayMs(500);
	fufoOutputChar("....");
	fufoInitUART();
	fufoDelayMs(200);
	fufoOutputChar("...");
	fufoInitI2C();
	fufoDelayMs(200);
	fufoOutputChar("..");
	fufoInitAccel();
	fufoDelayMs(200);
	fufoOutputChar("..");
	fufoInitGyro();
	fufoDelayMs(200);
	fufoOutputChar("...");
	initTMR2();
//	initTMR3();
//	fufoInitBluetooth(receiOK);
//	fufoDelayMs(200);
	setState(Waiting_for_connection);
}

void initTMR2(void){
	IPC1bits.T2IP = 6;  	//highest priority interrupt
	T2CONbits.TCKPS = 0b01;	// timer 2 prescale = 8
	TMR2 = 0;
	PR2 = 20000;		
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 0;		//timer 2 on
}

void initTMR3(void){
	T3CONbits.TCKPS = 0b01;	// timer 2 prescale = 8
	TMR3 = 0;		
	T3CONbits.TON = 1;		//timer 2 on
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{	
	IFS0bits.T2IF = 0;	// clear interrupt flag manually
	TMR2 = 0;
//	TMR3 = 0;
	controlFUFO();
	if(userInputFlag == 1){
		_RE8 = 1;
		index++;
		if(index == 50){
			index = 0;
			userInputFlag = 0;
			if (_RE8 == 1){
				_RE8 = 0;
			} else _RE8 = 1;
		}
	}

	if(getConnectStatus() == Disable){
		i++;
		if(i == 200){
			i = 0;
//			setPIDStatus(Disable);
//			T2CONbits.TON = 0;
			setState(Landing);
		}
	} else i = 0;
//	fufoSendCharUART('k');
//	fufoSendIntUART(TMR3);
//	fufoSendCharUART('k');
}