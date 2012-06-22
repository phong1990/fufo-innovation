// Khao bao bien hoac method dung chung cho ca project
#define Fcy		(7372800/4)			//Tan so thuc thi lenh
#define	Fpwm		400
#define Fsp			50

int getState(void);
void setState(unsigned int State);

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
