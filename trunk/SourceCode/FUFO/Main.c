#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "PWM/pwmControl.h"
#include "Bluetooth/Bluetooth.h"
#include "UART/UART.h"
#include "Control/Control.h"
#include "math.h"
#include "FUFO.h"


	_FOSC(CSW_FSCM_OFF & XT_PLL4);		//Clock = 7.3728 MHz
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
unsigned int FUFO_thrust = 0;
unsigned int userInputFlag = 0;
unsigned int FUFO_State;

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
					break;

			case Verify: // Trang thai Verify
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Choose connect!");
					checkConnection();
					break;

			case Pending: // Trang thai Pending 
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Press Start!!!");
					getStartInstruction();
					fufoDelayMs(500);
					fufoOutputInt(getState());
					break;

			case Setup: // Trang thai Setup
					//CalcR0();
					fufoDelayMs(50);
					FUFO_thrust++;
					if(FUFO_thrust >= 21) {
						FUFO_thrust = 21;
						setState(Ready);
						T2CONbits.TON = 1;
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
					fufoOutputInt(getThrustRate());
					fufoCmd4LCD(LCD_HOMEL2);
					fufoOutputInt(PDC2);
					if (userInputFlag == 0){
						getInstruction();
						userInputFlag = getUserInput();
					}
					break;
			
			case Landing: // Trang thai Landing
					// Auto landing
					fufoCmd4LCD(LCD_CLEAR);
					fufoOutputChar("Doi xiu di!");
					fufoCmd4LCD(LCD_HOMEL2);
					fufoDelayMs(1000);
					fufoOutputChar("5 ");
					fufoDelayMs(1000);
					fufoOutputChar("4 ");
					fufoDelayMs(1000);
					fufoOutputChar("3 ");
					fufoDelayMs(1000);
					fufoOutputChar("2 ");
					fufoDelayMs(1000);
					fufoOutputChar("1 ");
					T2CONbits.TON = 0;
					setState(Pending);
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
	fufoOutputChar("....");
	initTMR2();
	setState(Waiting_for_connection);
//	fufoInitBluetooth(receiOK);
//	testConnectBluetooth(receiOK);
}

void initTMR2(void){
	IPC1bits.T2IP = 7;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = calcTimeMS(20);		
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 0;		//timer 2 on
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{	
	TMR2 = 0;
	//T2CONbits.TON = 0;		//timer 2 off
	controlFUFO();
	if(userInputFlag == 1){
		
		_RE8 = 1;
		index++;
		if(index == 25){
			index = 0;
			userInputFlag = 0;
			_RE8 = 0;
		}
	}
	//T2CONbits.TON = 1;
	IFS0bits.T2IF = 0;	// clear interrupt flag manually
}