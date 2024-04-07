// Written 4/21/22 D.McLaughlin
// here are the necessary includes and function prototypes
#include <avr/io.h>
#include <string.h>
void uart_init(void);
void uart_send(unsigned char letter);
void send_string(char *stringAddress);

// here are the function definitions
void send_string(char *stringAddress){
    for (unsigned char i = 0; i < strlen(stringAddress); i++)
        uart_send(stringAddress[i]);
}

void uart_init(void){
    UCSR0B = (1 << TXEN0); //enable the UART transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set 8 bit character size
    UBRR0L = 103; //set baud rate to 9600 for 16 MHz crystal
}

void uart_send(unsigned char ch){
    while (!(UCSR0A & (1 << UDRE0))); //wait til tx data buffer empty
    UDR0 = ch; //write the character to the USART data register
}
