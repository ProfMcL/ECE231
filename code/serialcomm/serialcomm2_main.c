/*********************************************************************
 * serialcomm2_main.c - this program continuously sends
 * the letter 'G' to the serial monitor via the UART on the ATmega328P MCU. 
 * Note that this version gives the user-defined function definitions
 * up top.
 * 
 * Revision history:
 * Date         Author          Revision
 * 3/1/22      	D. McLaughlin   initial writing of code
 *************************************************************************/ 

#include <avr/io.h>				// Defines constants USCR0B, USCR0C, etc...

// This function initializes the UART peripheral 
// enable; 8 data bits; 1 stop bit, no parity
// 9600 baud from 16 MHz clock
void uart_init(void)  {
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);
	UBRR0L = 103; // Gives us 9600 baud from 16 MHz clock
}

// This function sends a single character to the serial comm port
void send_char(char letter){
	while (! (UCSR0A&(1<<UDRE0))); // Wait until Tx buffer is empty
	UDR0=letter;
}

// Here is main
int main(void){                	// Main function definition

	uart_init();               	// Initialize the UART

	while (1) {
		send_char('G');	        // Send  over and over again
    }
}

/********* End of File *******/