# makefile for AVR ATmega328P projects using Arduino Uno
# ECE-231 Spring 2023. Based on a makefile downloaded 2/22 from
# # https://ece-classes.usc.edu/ee459/library/samples/AVR/Makefile-ATmega328P
# revision history
#	Date		Author			Revision
#	2/14/22		D. McLaughlin	initial release 
# 	2/15/22		D. McLaughlin	updated with corrections (thanks S. Kaza)
#	3/30/22		D. McLaughlin	updated for use with Sparkfun Pocket Programmer
# 	4/3/22		D. McLaughlin	tested on Windows 10 (parallels 17 on MBP Apple Silicon)
#	2/13/23		D. McLaughlin	simplified for Arduino Uno dev board only, ECE231 Spring 2023

#______________ MODIFY SERIALPORT AND SOURCEFILE_______________________
# Specify the com port (windows) or USB port (macOS)
# Use Device Manager to identify COM port number for Arduino Uno board in Windows
# In Terminal, type ls /dev/tty.usb* to determine USB port number in macOS
SERIALPORT = /dev/tty.usbmodem143101
# Specify the name of your source code here:
SOURCEFILE = blink.c
#_____________________________________________________________________
# Don't change anything below unless you know what you're doing....
CLOCKSPEED = 16000000	
PROGRAMMER = Arduino

begin:	main.hex

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=atmega328p main.elf

main.elf: $(SOURCEFILE)
	avr-gcc -Wall -Os -DF_CPU=$(CLOCKSPEED) -mmcu=atmega328p -o main.elf $(SOURCEFILE)

flash:	begin
	avrdude -c $(PROGRAMMER) -b 115200 -P $(SERIALPORT) -p atmega328p -U flash:w:main.hex:i
