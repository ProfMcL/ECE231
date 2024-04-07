/***************************************************************** 
 * uart_string.c - This code sends strings to the com port via the
 * uart. Also blinks the built-in LED & displays a counter.
 * Date     Author          Revision
 * 12/16/21 D. McLaughlin   Initial writing of the code
 * 1/15/22  D. McLaughlin   Tested on Arduino Uno w/ Apple M1 pro
 *                          host running Monterey
 * 2/27/22  D. McLaughlin   tested on Arduino Uno w/ Apple M1 running
 *                          Windows 11 on Parallels VM
 *****************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>  //so that we can use the  strlen() function
#include <stdlib.h>  //need for itoa function
void uart_init(void);
void uart_send(unsigned char);
void send_string(char *stringAddress);

int main(void){
    char mystring[]= "Shall I compare thee to a summer's day?";
    char buffer[10];
    unsigned char count=0;
    // make PB5 output (Arduino Uno internal LED on PB5)
    DDRB = 1<<PB5; 
    uart_init(); // initialize the USART
    
    while (1) {
        PORTB ^= 1<<PB5;   //toggle the LED on PB5
        count++;
        itoa(count, buffer, 16); //convert the count to ascii in hex 
        send_string("Count = ");
        send_string(buffer);
        uart_send(' ');
        send_string(mystring);
        uart_send(13); //tx carriage return
        uart_send(10); //tx new line
        _delay_ms(50);
    }
}

void uart_init(void){
    UCSR0B = (1 << TXEN0); //enable the USART transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set 8 bit character size
    UBRR0L = 103; //set baud rate to 9600 for 16 MHz crystal
}

void uart_send(unsigned char ch){
    while (!(UCSR0A & (1 << UDRE0))); //wait til tx data buffer empty
    UDR0 = ch; //write the character to the USART data register
}

void send_string(char *stringAddress){
    unsigned char i;
    for (i = 0; i < strlen(stringAddress); i++)
        uart_send(stringAddress[i]);
}