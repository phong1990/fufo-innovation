#include	<p30f4012.h>
#include	"mainLCD.h"

	_FOSC(CSW_FSCM_OFF & XT);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
//Cac hang so cua chuong trinh (gia tri tuc thoi dung trong chuong trinh)
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy			(7372800/4)		//Tan so thuc thi lenh
#define	Fpwm		50		//Tan so PWM = 40 kHz

void Init_PORTS(void);
void Init_MCPWM(void);

//Cac bien toan cuc
unsigned int ms;
unsigned int max;
unsigned int PWMValue;
volatile unsigned int PR2_value;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	PWMValue = 3686;
	Init_MCPWM();			//Khoi tao module PWM
	LCD_Init();
	PR2_value = 1843;
	setup_TMR2();
	PTCON = 0x8000;			//Kich hoat module PWM
	T2CONbits.TON = 1;		//timer 2 on
	max = 0;
	Delay_ms(500);
	while (1){
		LCD_cmd4(LCD_clear);
		Delay_ms(500);
		ms = PWMValue*(0.542)/2;
		Delay_ms(300);
		xuatint1(ms);
		xuat1(" us ");
		xuatint1(PWMValue);
		xuatint2(PR2_value*2 - 200);
		//xuatint1(ADCValue);	
		if (max < 8){
			Delay_ms(1000);
			PWMValue += 50;
			if (PWMValue > 5170)  {max += 1; 	// da len toi max
			PWMValue = 5170;
			}
		} 
		if (max == 8) {
			Delay_ms(1000);
			PWMValue -= 25;
			if (PWMValue < 3700) max = 0;	// da xuong min
		}
		PDC1 = PWMValue;			//E1
		PDC2 = PWMValue;			//E3
		PDC3 = PWMValue + 450;			//E5
		PR2_value = 100 + PWMValue/2;			//E6
	}
}

//Chuong trinh con khoi tao cac cong I/O, de xuat cac tin hieu PWM, va doc tin
//hieu dieu chinh cua bien tro tai AN0
void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0;		//Cac tin hieu PWM nam tai RE0..RE5
}

void Init_MCPWM(void) {
	PTPER = 4608;	//Dat thanh ghi chu ky voi tan so PWM = 50Hz
							//Cong thuc tinh PTPER = (Fcy/(Fpwm*prescaler))-1
							//voi Fcy va Fpwm nhu tren va Prescaler la 1:1 thi PTPER = 36863 (0x8D43)
							//Cong thuc tinh resolution : log(2*Fcy/Fpwm)/log(2)
							//O day resolution la 16 (0xFFFF)
	SEVTCMP = PTPER;
	PWMCON1 = 0x070F;		//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = PWMValue;			//Khoi tao ESC1 chay o 1ms
	PDC2 = PWMValue;			//Khoi tao ESC3 chay o 1ms
	PDC3 = PWMValue;			//Khoi tao ESC5 chay o 1ms
	//PTCON = 0x8000;			//Kich hoat module PWM
}

void setup_TMR2(void)
{
	IPC1bits.T2IP = 7;  	//highest priority interrupt
	T2CONbits.TCKPS = 0;	// timer 2 prescale = 1
	TMR2 = 0;
	PR2 = PR2_value;			// 19 ms	for downtime
	IFS0bits.T2IF = 0;		//interupt flag clear
    IEC0bits.T2IE = 1;  	//Enable Timer1 Interrupt Service Routine
	T2CONbits.TON = 0;		//timer 2 off
	_RE5 = 1;
	return;
}

void __attribute__((__interrupt__ , auto_psv)) _T2Interrupt (void)
{
	IFS0bits.T2IF = 0;	// clear interrupt flag manually	
	T2CONbits.TON = 0;	//timer 2 off
	if (PR2 == (4608 - PR2_value)){
		PR2 = PR2_value;		// HIGH on 1 ms
		_RE5 = 1;
	}else{
		PR2 = 4608 - PR2_value;		// LOW on 2.5 ms
		_RE5 = 0;
	}
	T2CONbits.TON = 1;		//timer 2 on
}