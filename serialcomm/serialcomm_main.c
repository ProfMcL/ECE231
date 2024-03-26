/*********************************************************************
 * serialcomm_main.c - this program continuously sends
 * the letter 'G' to the serial monitor via the UART on the ATmega328P MCU. 
 * This version uses forward  function declarations, main() definined up top. 
 * Revision history:
 * Date         Author          Revision
 * 1/22/21      D. McLaughlin   Written using MPLABX for ECE-231 Spring 2021
 * 12/29/21     D. McLaughlin   Improved comment style for ECE-231 Spring 2022
 * 1/15/22		D. McLaughlin	using UART instead of USART functions; split braces for structures
 *************************************************************************/ 

#include <avr/io.h>				// Defines constants USCR0B, USCR0C, etc...

void uart_init(void);		    // Function prototype (declaration)
void send_char(char);			// Function prototype (declaration)

int main(void){                	// Main function definition

	uart_init();               	// Initialize the UART
 
	while (1) {
		send_char('M');	        // Send  over and over again
    }
}

// This function initializes the UART peripheral 
// enable; 8 data bits; 1 stop bit, no parity
// 9600 baud from 16 MHz clock
void uart_init(void)  {
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);
	UBRR0L = 103; // Gives us 9600 baud from 16 MHz clock
	//UBRR0L = 12; // Gives us 2400 baud from 1 MHz clock
}


// This function sends a single character to the serial comm port
void send_char(char letter){
	while (! (UCSR0A&(1<<UDRE0))); // Wait until Tx buffer is empty
	UDR0=letter;
}
/******** End of File *************/
