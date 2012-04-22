#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & FRC_PLL4);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy			7232800		//Tan so thuc thi lenh
#define	Fpwm		50000		//Tan so PWM = 50 kHz vi 50kHz la tan so hoat dong cua ESC
								
								

void Init_PORTS(void);
void Init_MCPWM(void);


int main(void) {
	Init_PORTS();			//Khoi tao cac cong I/O
	Init_MCPWM();			//Khoi tao module PWM
	while (1) Nop();
}

void Init_PORTS(void) {
	PWM_LAT = 0;			//Xoa thanh ghi chot cac tin hieu PWM
	PWM_TRIS = 0xFFC0;		//Cac tin hieu PWM nam tai RE0..RE5
}

//Chuong trinh con khoi tao module PWM
void Init_MCPWM(void) {
	PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 50 kHz
							//Cong thuc tinh PTPER = (Fcy/(Fpwm*prescaler))-1
							//voi Fcy va Fpwm nhu tren va Prescaler la 1:1 thi PTPER = 144 (0x90)
							//Cong thuc tinh resolution : log(2*Fcy/Fpwm)/log(2)
							//O day resolution la 255 (0xFF)
	PWMCON1 = 0x070F;		//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 0x007D;			//Khoi tao PWM1 chay o resolution la 125; duty_cycle = PDCx/((PTPER + 1)*2) = 43%
	PDC2 = 0x007D;
	PTCON = 0x8000;			//Kich hoat module PWM
}
