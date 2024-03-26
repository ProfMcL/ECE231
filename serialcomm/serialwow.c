/*********************************************************************
 * serialcomm_main.c - this program continuously sends
 * the letter 'WOW!' to the serial monitor via the UART on the ATmega328P MCU. 
 * Date         Author          Revision
 * 3/1/22      	D. McLaughlin   initial release. based on serialcomm_main.c
 * 3/29/22		D. McLaughlin	added a blinking LED on PB5 w/ 100 ms delay
 *************************************************************************/ 

#include <avr/io.h>				// Defines constants USCR0B, USCR0C, etc...
#include <util/delay.h>

void uart_init(void);		    // Function prototype (declaration)
void send_char(char);			// Function prototype (declaration)

int main(void){                	// Main function definition
	DDRB = 1<<DDB5;
	uart_init();               	// Initialize the UART

	while (1) {					// Send repeatedly
		send_char('W');	        
		send_char('o');
		send_char('W');
		send_char(10);			// Carriage Return
		send_char(13);			// Line feed
		PORTB ^= 1<<PORTB5;		// Toggle the LED
		_delay_ms(100);
    }
}

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
/******** End of File *************/
