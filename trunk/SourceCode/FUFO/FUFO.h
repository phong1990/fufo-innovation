#include "p30f4012.h"
#include "LCD/LCD.h"
#include "Delay/DelayTMR1.h"
#include "PWM/pwmControl.h"
#include "Bluetooth/Bluetooth.h"
#include "UART/UART.h"
#include "Control/Control.h"
#include "math.h"
#include "Filter/Filter.h"
#include "ADXL345_accel/ADXL345.h"
#include "L3G4200D_gyro/L3G4200D.h"
#include "I2C/I2C.h"
#include "stdlib.h"
#include "BMP085_barometric/BMP085.h"
#include "HMC5883L_magneto/HMC5883L.h"


// Khao bao bien hoac method dung chung cho ca project
#define Fcy		(8000000*8/4)			//Tan so thuc thi lenh
#define	Fpwm		400
#define Fsp			50
#define PLL			8
#define FOSC 	8000000
#define Start						0
#define	Waiting_for_connection		1
#define	Verify						2
#define	Pending						3
#define	Setup						4
#define	Ready						5
#define	Hovering					6
#define Landing						7
#define End							10
#define Enable		1
#define	Disable		0
#define True 		1
#define False		0
#define	On			1
#define Off			0

int getConnectStatus(void);
void setConnectStatus(int Connect);
int getPIDStatus(void);
void setPIDAltitude(int sta);
int getPIDAltitude(void);
void setPIDStatus(int status);
int getState(void);
void setState(unsigned int State);
int calcTimeMS(unsigned int time);
void setPhiAngle(float Phi);
float getPhiAngle(void);
void setThetaAngle(float Theta);
float getThetaAngle(void);
void setPsiAngle(float Psi);
float getPsiAngle(void);
void setGyrosOutputR(float GyrosR);
float getGyrosOutputR(void);
void setGyrosOutputP(float GyrosP);
float getGyrosOutputP(void);
void setGyrosOutputY(float GyrosY);
float getGyrosOutputY(void);
void setAccelAlt(float Alt);
float getAccelAlt(void);
float constrain(float valueConstrain, float min, float max);
void initTMR2(void);
void initTMR3(void);
void setPID1(int p1);
int getPID1(void);
void setPID2(int p2);
int getPID2(void);
void setPID3(int p3);
int getPID3(void);
void setPID4(int p4);
int getPID4(void);


/* QUy dinh: 
	- Trang thai Start:
		+ Dieu kien: khi nhan nut nguon, bat nguon cho FUFO. 
		+ State = 0.
		+ Trong trang thai nay FUFO se init tat ca cac modul nhu PWM, timer, LCD...
	- Trang thai Waiting for connection:
		+ Dieu kien: khi init xong tat ca cac thu.
		+ State = 1
		+ Trong trang thai nay FUFO cu chay trong vong lap khong lam gi ca.
	- Trang thai Verify:
		+ Dieu kien: khi User nhan connect tren phone(neu dk = Phone) hoac PC(neu dk = PC), va Phone da ket noi voi FUFO
		+ State = 2
		+ Trong trang thai nay FUFO se kiem tra ket noi cua He Thong, neu chi dung tren Phone thi se ktr ket noi giua FUFO voi Phone, 
			con neu dung PC thi se kiem tra ket noi giua phone va PC
	- Trang thai Pending:
		+ Dieu kien: khi da hoan tat kiem tra ket noi, ket noi da thanh cong hoac FUFO dang o trang thai Landing.
		+ State = 3
		+ Trong trang thai nay FUFO se chay trong vong lap khong lam gi ca/
	- Trang thai Setup:
		+ Dieu kien: khi User an nut Start tren Phone(neu dk = phone) hoac PC(neu dk = PC)
		+ State = 4
		+ Trong trang thai nay FUFO se tinh R0 cua Thang, set PWM den 1 muc nao do(cai nay setup dc)
	- Trang thai Ready:
		+ Dieu kien: Da tim xong R0 va tang xong PWM den 1 muc nao do.
		+ State = 5
		+ Trong trang thai nay FUFO FUFO se chay trong vong lap ko lam gi ca.
	- Trang thai Hovering:
		+ Dieu kien: nguoi dung an "Up" tren phone(neu dk = phone) hoac pc(neu dk = PC) de tang PWM.
		+ State = 6
		+ Trong trang thai nay FUFO bat dau hoat dong PID va nhan len dieu khien FUFO cua User.
	- Trang thai Landing:
		+ Dieu kien: Khi User nhan nut "Down" cho FUFO ha canh, va PWM giam den 1 muc nao do(muc canh quat ko quay nua)
		+ State = 7
		+ Trong trang thai nay FUFO se khong nhan bat ky 1 lenh dk nao tu User trong 5s. Sau do tu chuyen sang trang thai Pending
	- Trang thai End:
		+ Dieu kien: tat ca loi sinh ra trong qua trinh hoat dong deu dan den trang thai nay. 
					 Tat nut nguon FUFO, 
					 hoac thich thi them cai button end tren phone hoac PC cho User nhan!
		+ State = 10
		+ Trong trang thai nay FUFO se xuat loi len tren LCD hoac man hinh phone hay PC
			Neu xuat hien loi trong trang thai Hovering thi FUFO se tu dong giam PWM ha canh.
*/
