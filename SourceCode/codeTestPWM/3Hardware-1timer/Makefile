# MPLAB IDE generated this makefile for use with GNU make.
# Project: 3Hardware-1Timer.mcp
# Date: Fri Jun 01 15:26:48 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

3Hardware-1Timer.hex : 3Hardware-1Timer.cof
	$(HX) "3Hardware-1Timer.cof"

3Hardware-1Timer.cof : 3Hardware-1Timer.o
	$(CC) -mcpu=30F4012 "3Hardware-1Timer.o" -o"3Hardware-1Timer.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",--script="..\..\..\..\..\Program Files\Microchip\MPLAB C30\support\gld\p30f4012.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,-Map="3Hardware-1Timer.map",--report-mem

3Hardware-1Timer.o : ../../../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h mainLCD.h ../../../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h 3Hardware-1Timer.c
	$(CC) -mcpu=30F4012 -x c -c "3Hardware-1Timer.c" -o"3Hardware-1Timer.o" -D__DEBUG -g -Wall

clean : 
	$(RM) "3Hardware-1Timer.o" "3Hardware-1Timer.cof" "3Hardware-1Timer.hex"

