# MPLAB IDE generated this makefile for use with GNU make.
# Project: FUFO.mcp
# Date: Mon Jul 09 10:45:32 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

FUFO.hex : FUFO.cof
	$(HX) "FUFO.cof"

FUFO.cof : Main.o DelayTMR1.o LCD.o pwmControl.o Bluetooth.o UART.o Control.o FUFO.o ADXL345.o I2C.o L3G4200D.o Filter.o
	$(CC) -mcpu=30F4012 "Main.o" "DelayTMR1.o" "LCD.o" "pwmControl.o" "Bluetooth.o" "UART.o" "Control.o" "FUFO.o" "ADXL345.o" "I2C.o" "L3G4200D.o" "Filter.o" -o"FUFO.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",--script="p30f4012.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,-Map="FUFO.map",--report-mem

Main.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h Main.c
	$(CC) -mcpu=30F4012 -x c -c "Main.c" -o"Main.o" -D__DEBUG -g -Wall

DelayTMR1.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h DELAY/DelayTMR1.c
	$(CC) -mcpu=30F4012 -x c -c "DELAY\DelayTMR1.c" -o"DelayTMR1.o" -D__DEBUG -g -Wall

LCD.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h LCD/LCD.c
	$(CC) -mcpu=30F4012 -x c -c "LCD\LCD.c" -o"LCD.o" -D__DEBUG -g -Wall

pwmControl.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h PWM/pwmControl.c
	$(CC) -mcpu=30F4012 -x c -c "PWM\pwmControl.c" -o"pwmControl.o" -D__DEBUG -g -Wall

Bluetooth.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h Bluetooth/Bluetooth.c
	$(CC) -mcpu=30F4012 -x c -c "Bluetooth\Bluetooth.c" -o"Bluetooth.o" -D__DEBUG -g -Wall

UART.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h UART/UART.c
	$(CC) -mcpu=30F4012 -x c -c "UART\UART.c" -o"UART.o" -D__DEBUG -g -Wall

Control.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h Control/Control.c
	$(CC) -mcpu=30F4012 -x c -c "Control\Control.c" -o"Control.o" -D__DEBUG -g -Wall

FUFO.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h FUFO.c
	$(CC) -mcpu=30F4012 -x c -c "FUFO.c" -o"FUFO.o" -D__DEBUG -g -Wall

ADXL345.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h ADXL345_accel/ADXL345.c
	$(CC) -mcpu=30F4012 -x c -c "ADXL345_accel\ADXL345.c" -o"ADXL345.o" -D__DEBUG -g -Wall

I2C.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h I2C/I2C.c
	$(CC) -mcpu=30F4012 -x c -c "I2C\I2C.c" -o"I2C.o" -D__DEBUG -g -Wall

L3G4200D.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h L3G4200D_gyro/L3G4200D.c
	$(CC) -mcpu=30F4012 -x c -c "L3G4200D_gyro\L3G4200D.c" -o"L3G4200D.o" -D__DEBUG -g -Wall

Filter.o : I2C/I2C.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h UART/UART.h I2C/I2C.h Delay/DelayTMR1.h L3G4200D_gyro/L3G4200D.h ADXL345_accel/ADXL345.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h ../../../program\ files/microchip/mplab\ c30/include/math.h Filter/Filter.h ../../../program\ files/microchip/mplab\ c30/include/math.h Control/Control.h UART/UART.h Bluetooth/Bluetooth.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h PWM/pwmControl.h Delay/DelayTMR1.h ../../../program\ files/microchip/mplab\ c30/support/h/p30f4012.h LCD/LCD.h p30f4012.h FUFO.h Filter/Filter.c
	$(CC) -mcpu=30F4012 -x c -c "Filter\Filter.c" -o"Filter.o" -D__DEBUG -g -Wall

clean : 
	$(RM) "Main.o" "DelayTMR1.o" "LCD.o" "pwmControl.o" "Bluetooth.o" "UART.o" "Control.o" "FUFO.o" "ADXL345.o" "I2C.o" "L3G4200D.o" "Filter.o" "FUFO.cof" "FUFO.hex"

