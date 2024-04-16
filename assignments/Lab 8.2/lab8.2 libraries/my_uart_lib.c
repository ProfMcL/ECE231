/***************************************
 * my_uart_lib.c 
 * Implementation of a library for initializing UART
 * and transmitting characters and strings on ATmega328P MCU
 * Version Author           Date        Comment
 * 1.0      D. McLaughlin   4/16/24     Assumes 16 MHZ clock
 * **************************************/

#include "my_uart_lib.h"

// Initialize the UART
void uart_init(void){
    UCSR0B = (1 << TXEN0);                  //enable the UART transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set 8 bit character size
    UBRR0L = 103;                           //set baud rate to 9600 for 16 MHz crystal
}

// Send a single character
void uart_send(unsigned char ch){
    while (!(UCSR0A & (1 << UDRE0)));       //wait til tx data buffer empty
    UDR0 = ch;                              //write the character to the USART data register
}

// Send a string of characters using uart_send
void send_string(char *stringAddress){
    for (unsigned char i = 0; i < strlen(stringAddress); i++)
        uart_send(stringAddress[i]);
}