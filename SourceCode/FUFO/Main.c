#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "math.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

int main(void) {
	while(1){
		
	}
}