 /**************************************
* Author: Nathan House				  *
* Device: dsPIC30f4011				  *
* E-Mail: roboticsguy@roboticsguy.com *
* Website: www.roboticsguy.com		  *
* Date Modified: 09/07/2009			  *
**************************************/

#include "p30f4011.h" // Include this in your MPLAB project under "Header Files" from C:\Program Files (x86)\Microchip\MPLAB C30\support\dsPIC30F\h
					  // And include the p30f4011.gld linker script under "Linker Script" from C:\Program Files (x86)\Microchip\MPLAB C30\support\dsPIC30F\gld

/**************************************
*          Configure Fuses            *
**************************************/
_FOSC(CSW_FSCM_OFF & XT);  								// Disable clock monitor, external 10MHz oscillator
_FWDT(WDT_OFF);             							// Disable Watch-Dog Timer.
_FBORPOR(PBOR_OFF & MCLR_EN & PWRT_OFF & PWMxH_ACT_HI); // Brown out reset disabled, enable MCLR reset pin, turn off power-up timer, PWMxH acts high
_FGS(CODE_PROT_OFF);        							// Disable Code Protection

/**************************************
*      Oscillator Calculations        *
**************************************/
#define FOSC 10000000  // 10Mhz
#define FCY (FOSC / 4) // 1 inscruction cycle = 4 clock cycles

/****************************************************
* Function: int main(void)			  		        *
* Purpose: program entry point		 		        *
* Description: This is where the main loop resides. *
****************************************************/
int main(void)
{
	Init_PWM();   // Initialize PWM module
		
	while(1) // Loop forever
	{
		PDC1 = 1875; // This sets the duty cycle, for or servo (or motor) 1875 is neutral.
	}//while
}//main	

void Init_PWM(void)
{
	/**** PTCON: PWM Time Base Control Register ****/
	PTCONbits.PTEN   = 0;   // Timer Enable bit:		    DISABLE MCPWM
	PWMCON1bits.PEN1H = 1;  // PWM1H (pin 37) is enabled for PWM output
	PWMCON1bits.PEN2H = 1;  // PWM2H (pin 35) is enabled for PWM output
	PTCONbits.PTCKPS = 1;   // Input Clock Prescale bits:   1:4
	PTCONbits.PTOPS  = 0;   // Output Clock Postscale bits: 1:1
	PTCONbits.PTSIDL = 1;	// Stop in Idle Mode:           YES
	PTCONbits.PTMOD  = 0;   // Mode Select bits:			Free Running Mode
	PTCONbits.PTEN   = 1;   // Timer Enable bit:		 	ENABLE MCPWM
	
	/**** PTPER: PWM Time Base Period Register ****/
	PTPERbits.PTPER = 11250; // Period Value bits
}	
