#include "p30f4012.h"

	_FOSC(CSW_FSCM_OFF & XT);		//Clock = 7.3728 MHz
	_FWDT(WDT_OFF);
	_FBORPOR(MCLR_EN & PBOR_OFF & PWMxL_ACT_HI & PWMxH_ACT_HI);
	_FGS(CODE_PROT_OFF);

//Cac prototype cho cac chuong trinh con
void Init_TMR1(void);
void Init_UART1_Module(void);

//Bang hang so trong ROM
const unsigned char __attribute__ ((space(psv), address (0x0400))) 
Chuoi1[] = "Xin chao! \0";

//Cac bien toan cuc
unsigned char flag, idx;

//------------------------------------------------------------------------------
//Chuong trinh chinh
int main(void) {
	Init_TMR1();			//Khoi tao Timer 1
	Init_UART1_Module();	//Khoi tao module UART1
	_PSV=1;
	PSVPAG = __builtin_psvpage(Chuoi1);
	flag = 0;				//Xoa co bao het thoi gian cho
	while (1) {
		if (flag) {			//Cho den khi het thoi gian cho
			idx = 0;
			while (Chuoi1[idx]) {	//Neu chua het chuoi thi
				U1TXREG = Chuoi1[idx++];	//Xuat tiep 1 ky tu
				while (!U1STAbits.TRMT);	//Cho den khi truyen xong ky tu
			};
			flag = 0;
		};
	};
}

//Chuong trinh con khoi tao module UART1
void Init_UART1_Module(void) {
	U1MODE = 0x8000;		//Main I/O, 8-bit, no parity, 1 stop bit
	U1STA = 0x0400;			//bit10=UTXEN
	U1BRG = ((((7372800/4)/9600)/16)-1);	//38400 bps @ Fcy = 8 MHz
}

//Chuong trinh con khoi tao Timer 1, tran sau moi 1 giay o muc xung 8 Mips
void Init_TMR1(void) {
	TMR1 = 0;			//Xoa so dem trong TMR1
	PR1 = 0x1C20;		//Nguong tran la 1 giay tuong ung voi clock = 32 MHz
	_T1IF = 0;			//Xoa co ngat cua Timer 1
	T1CON = 0x8030;		//Dung fcy lam clock, prescale = 1:256
	_T1IE = 1;			//Cho phep ngat khi Timer 1 tran
}

//Chuong trinh xu ly ngat Timer 1
void _ISR_T1Interrupt(void) {
	_T1IF = 0;			//Xoa co ngat
	flag = 1;			//Bat co cho phep xuat chuoi ky tu
}
