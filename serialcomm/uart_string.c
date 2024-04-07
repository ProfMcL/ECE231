/***************************************************************** 
 * uart_string.c - This code sends strings to com port via uart.
 * Date     Author          Revision
 * 12/16/21 D. McLaughlin   Initial writing of the code
 * 1/15/22  D. McLaughlin   Tested on Arduino Uno w/ Apple M1 pro
 *                          host running Monterey
 * 2/27/22  D. McLaughlin   tested on Windows 11 on Parallels VM
 *****************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>  //so that we can use the  strlen() function

void uart_init(void);
void uart_send(unsigned char);
void send_string(char *stringAddress);

int main(void){
    char mystring[]= "How cool is this, right?";
    uart_init(); // initialize the USART
    while (1) {
        send_string(mystring);
        uart_send(13); // Carriage return (goto beginning of line)
        uart_send(10); //line feed (new line)
        _delay_ms(500);
    }
}

// Send a string, char by char, to uart via uart_send()
// Input is pointer to the string to be sent
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

/***** End of file *****/
