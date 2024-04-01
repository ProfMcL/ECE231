# makefile V2.0. This is a makefile for AVR ATmega328P projects using Arduino Uno Dev board
# ECE-231 Spring 2024. 
# 
# Instructions: 
# Put this file (makefile, no extension) into the source code folder for each 
# programming project. You should only need to change the SERIALPORT and SOURCEFILE. 
# Options for running this makefile from Command Prompt (Windows) or Terminal (macOS):
# "make" compiles code & creates a hex file for uploading to the MCU
# "make -B" will force compiling even if the source code hasn't changed
# "make flash" will compile, create hex file, and upload the hex file to the MCU
# "make clean" will delete intermediate files make.elf and make.hex

#______________ MODIFY SERIALPORT AND SOURCEFILE_______________________
# Specify the com port (windows) or USB port (macOS)
# Use Device Manager to identify COM port number for Arduino Uno board in Windows
# In Terminal, type ls /dev/tty.usb* to determine USB port number in macOS
SERIALPORT = /dev/tty.usbmodem2101
# Specify the name of your source code here:
SOURCEFILE = example2.c
#_____________________________________________________________________
# Don't change anything below unless you know what you're doing....
CLOCKSPEED = 16000000	
PROGRAMMER = arduino

begin:	main.hex

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=atmega328p main.elf

main.elf: $(SOURCEFILE)
	avr-gcc -Wall -Os -DF_CPU=$(CLOCKSPEED) -mmcu=atmega328p -o main.elf $(SOURCEFILE)

flash:	begin
	avrdude -c $(PROGRAMMER) -b 115200 -P $(SERIALPORT) -p atmega328p -U flash:w:main.hex:i

clean: 
	rm -f main.elf main.hex


# revision history
#	Date		Author			Revision
#	2/14/22		D. McLaughlin	V1.0 initial release 
# 	2/15/22		D. McLaughlin	V1.1 updated with corrections (thanks S. Kaza)
#	3/30/22		D. McLaughlin	V1.2 updated for use with Sparkfun Pocket Programmer
# 	4/3/22		D. McLaughlin	V1.3 tested on Windows 10 (parallels 17 on MBP Apple Silicon)
#	2/13/23		D. McLaughlin	V1.4 simplified for Arduino Uno dev board only, ECE231 Spring 2023
#	3/25/24		D. McLaughlin	V2.0 reformatted, added clean, added version #'s for ECE231 Sp 2024
