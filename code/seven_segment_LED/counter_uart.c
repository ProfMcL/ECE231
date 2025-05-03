/* counter_uart.c This code implements a 0- 9999 ring counter 
and displays the count value on the monitor using the UART.
Uses itoa() function to convert count to a string.
This is a demo for ECE-231 Spring 2022
D. McLaughlin 3/18/22 */

#include <avr/io.h>     // #defines all the port pins
#include <util/delay.h> // Declares _delay_ms() function
#include <stdlib.h>     // Declares itoa() function 
#include <string.h>     // Declares strlen() function

void uart_init(void);
void uart_send(unsigned char);
void send_string(char *stringAddress);

int main(void){
    char mystring[10];
    uart_init(); // initialize the USART
    while (1) {
        for (unsigned int i=0; i<10000; i++){
            itoa(i, mystring, 10); // Convert i to a string, base 10
            send_string(mystring);
            uart_send(13); // Carriage return (goto beginning of line)
            uart_send(10); //line feed (new line)
            _delay_ms(1000);
        }
       
    }
}

// Send a string, char by char, to uart via uart_send()
// Input is pointer to the string to be sent
void send_string(char *stringAddress){
    for (unsigned char i = 0; i < strlen(stringAddress); i++)
        uart_send(stringAddress[i]);
}

// Initialize the uart, 8,1,0, 9600 baud
void uart_init(void){
    UCSR0B = (1 << TXEN0); //enable the UART transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set 8 bit character size
    UBRR0L = 103; //set baud rate to 9600 for 16 MHz crystal
}

// Send a single character to the UART transmitter
void uart_send(unsigned char ch){
    while (!(UCSR0A & (1 << UDRE0))); //wait til tx data buffer empty
    UDR0 = ch; //write the character to the USART data register
}

/***** End of file *****/


