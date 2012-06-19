# MPLAB IDE generated this makefile for use with GNU make.
# Project: FUFO.mcp
# Date: Mon Jun 18 15:42:39 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

FUFO.hex : FUFO.cof
	$(HX) "FUFO.cof"

FUFO.cof : Main.o DelayTMR1.o LCD.o pwmControl.o Bluetooth.o UART.o Control.o
	$(CC) -mcpu=30F4012 "Main.o" "DelayTMR1.o" "LCD.o" "pwmControl.o" "Bluetooth.o" "UART.o" "Control.o" -o"FUFO.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",--script="p30f4012.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,-Map="FUFO.map",--report-mem

Main.o : FUFO.h ../../../program\ files/microchip/mplab\ c30/include/math.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h UART/UART.h Bluetooth/Bluetooth.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h Main.c
	$(CC) -mcpu=30F4012 -x c -c "Main.c" -o"Main.o" -D__DEBUG -g -Wall

DelayTMR1.o : DELAY/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h DELAY/DelayTMR1.c
	$(CC) -mcpu=30F4012 -x c -c "DELAY\DelayTMR1.c" -o"DelayTMR1.o" -D__DEBUG -g -Wall

LCD.o : Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.c
	$(CC) -mcpu=30F4012 -x c -c "LCD\LCD.c" -o"LCD.o" -D__DEBUG -g -Wall

pwmControl.o : FUFO.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.c
	$(CC) -mcpu=30F4012 -x c -c "PWM\pwmControl.c" -o"pwmControl.o" -D__DEBUG -g -Wall

Bluetooth.o : ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h UART/UART.h Bluetooth/Bluetooth.h Bluetooth/Bluetooth.c
	$(CC) -mcpu=30F4012 -x c -c "Bluetooth\Bluetooth.c" -o"Bluetooth.o" -D__DEBUG -g -Wall

UART.o : ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h UART/UART.h Bluetooth/Bluetooth.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h Control/Control.h UART/UART.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h UART/UART.c
	$(CC) -mcpu=30F4012 -x c -c "UART\UART.c" -o"UART.o" -D__DEBUG -g -Wall

Control.o : ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h UART/UART.h Bluetooth/Bluetooth.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h Control/Control.h Control/Control.c
	$(CC) -mcpu=30F4012 -x c -c "Control\Control.c" -o"Control.o" -D__DEBUG -g -Wall

clean : 
	$(RM) "Main.o" "DelayTMR1.o" "LCD.o" "pwmControl.o" "Bluetooth.o" "UART.o" "Control.o" "FUFO.cof" "FUFO.hex"

