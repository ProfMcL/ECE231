/*********************************************************************
 * serialnofunctions_main.c - this program continuously sends
 * the letter 'G' to the serial monitor via the UART on the ATmega328P MCU. 
 * Revision history:
 * Date         Author          Revision
 * 1/22/21      D. McLaughlin   Written using MPLABX for ECE-231 Spring 2021
 * 12/29/21     D. McLaughlin   Improved comment style for ECE-231 Spring 2022
 * 1/15/22		D. McLaughlin	using UART instead of USART functions
 * 2/26/22		D. McLaughlin	everything in main instead of in functions
 *************************************************************************/ 

#include <avr/io.h>				// Defines constants USCR0B, USCR0C, etc...

int main(void){                	
	
	// Initialize the UART
	UCSR0B = (1<<TXEN0);					// Enable Tx		
	UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);		// 8 ASCII bits, 1 stop bit, no parity
	UBRR0L = 103; 							// Gives us 9600 baud from 16 MHz clock
	
	while (1) {

		while (! (UCSR0A&(1<<UDRE0))){ 		// Wait until Tx buffer is empty
			;
		}
		
		UDR0='P';							// Transmit the ASCII character
    }
}

/********** End of File *********/