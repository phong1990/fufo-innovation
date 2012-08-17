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
int Hung = 0;
int temp = 0;
int tempHigh = 0;
int FUFO_thrust_step = 0;
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
					if(calcRateAngle() == True){
						FUFO_thrust = getThrustRate();
						FUFO_thrust++;
						if(FUFO_thrust >= 41) {
							FUFO_thrust = 41;
							setState(Ready);
							_RE8 = 0;
						}
						setThrustRate(FUFO_thrust);
						controlFUFO();
					} else {
						fufoGetRateAngle(); // calc R0
					}
					break;

			case Ready: // Trang thai Ready
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Press Up!");
					getUpInstruction();
					break;

			case Hovering: // Trang thai Hovering
					if(value >= 3){
						setPIDAltitude(Enable);
    					measureBaro();
						value = 0;
					}
//					fufoCmd4LCD(LCD_CLEAR);
//					fufoOutputChar("Thrust :");
//					//fufoOutputInt(Fcy/Fpwm - 1);
//					fufoCmd4LCD(LCD_HOMEL2);
//					fufoOutputInt(getThrustRate());
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
					if(Hung >= 100){
						Hung = 0;
						if(FUFO_thrust > 42) 
						{
							FUFO_thrust = getThrustRate();
							FUFO_thrust_step = (FUFO_thrust - 42)/5 ;
							FUFO_thrust = FUFO_thrust-FUFO_thrust_step;
							setThrustRate(FUFO_thrust);
						}
						if(FUFO_thrust <= 42) 
						{
							FUFO_thrust = 42;
							setPIDStatus(Disable);
							T4CONbits.TON = 0;
							T2CONbits.TON = 0;
							_PTEN = 0;
							setState(Pending);
						}	
					}
//					T4CONbits.TON = 0;
//					_PTEN = 0;
//					T2CONbits.TON = 0;
//					setState(Pending);
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
	initPWM();		// khoi tao PWM voi tan so thuc thi lenh Fcy;
							// do rong xung ban dau 1ms (1843).
	fufoDelayMs(200);
	fufoInitUART();
	fufoDelayMs(200);
	fufoInitI2C();
	fufoDelayMs(200);
	initAccel();
	fufoDelayMs(200);
	fufoInitGyro();
	fufoDelayMs(200);
	initBaro();
	fufoDelayMs(200);
	initTMR2();
	initTMR3();
	
//	initBluetooth(receiOK);
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
	value++;
	Hung++;
	TMR2 = 0;
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
			tempHigh = getHigh_sum();
			temp = (tempHigh/40);
			FUFO_thrust = getThrustRate();
			FUFO_thrust = FUFO_thrust + temp;
			setThrustRate(FUFO_thrust);
			setHigh_sum(0);
			setPIDAltitude(Disable);
			setState(Landing);
		}
	} else i = 0;
}
