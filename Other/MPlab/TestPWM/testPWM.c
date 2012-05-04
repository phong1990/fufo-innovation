#include	<p30f4012.h>

	_FOSC(CSW_FSCM_OFF & FRC);
	_FWDT(WDT_OFF);
	_FBORPOR(PBOR_OFF & MCLR_EN);
	_FGS(CODE_PROT_OFF);

//------------------------------------------------------------------------------
#define	PWM_PORT	PORTE		//Cac tin hieu PWM nam o cong E
#define	PWM_TRIS	TRISE		//Thanh ghi 3 trang thai cho cac tin hieu PWM
#define	PWM_LAT		LATE		//Thanh ghi chot cac tin hieu PWM
#define	Fcy			2000000		//Tan so thuc thi lenh     Fcy = (Fosc*PLLz)/4 = 7232800*1/4
#define	Fpwm		50			//Tan so PWM = 50Hz vi 50Hz la tan so hoat dong cua ESC
								
								

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
	PTPER = Fcy/Fpwm - 1;	//Dat thanh ghi chu ky voi tan so PWM = 50Hz
							//Cong thuc tinh PTPER = (Fcy/(Fpwm*prescaler))-1
							//voi Fcy va Fpwm nhu tren va Prescaler la 1:1 thi PTPER = 39999 (0x8D43)
							//Cong thuc tinh resolution : log(2*Fcy/Fpwm)/log(2)
							//O day resolution la 16 (0xFFFF)
	PWMCON1 = 0x070F;		//1. Chinh mode Independent;  2. Chinh PWM chi ra o pin L, khong ra pin H;
	OVDCON = 0xFF00;		//Khong dung overdrive
	PDC1 = 2999;			//Khoi tao PWM1 chay o 15%  duty- 1ms: 1808;	 1.5ms: 2712;	 2ms: 3616
	PDC2 = 2000;
	PTCON = 0x8000;			//Kich hoat module PWM
}
