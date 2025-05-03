/* counter_uart2.c This code implements a 0- 9999 ring counter 
and displays the count value on the monitor using the UART.
and on a 4 digit 7 segment LED 
This is a demo for ECE-231 Spring 2022
D. McLaughlin 3/18/22 */

#include <avr/io.h>     // #defines all the port pins
#include <util/delay.h> // Declares _delay_ms() function
#include <string.h>     // Declares strlen() function

void uart_init(void);
void uart_send(unsigned char);
void send_string(char *stringAddress);

int main(void){
    char digit;
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};
    unsigned int i=0;
    unsigned char DIG1, DIG2, DIG3, DIG4;
    
    DDRD = 0xFF;    // 7segment pins
    DDRB = 0xFF;    // Digit enable pins
    PORTB = 0xFF;   // Disable all the digits initially
    uart_init(); // initialize the USART
    
    while (1) {
        
        for (unsigned int i=0; i<10000; i++){
        
        DIG1 = (i/1000);            // 1000's digit (Most signif digit)
        uart_send(digit+'0');
        PORTD = ledDigits[DIG1];
        PORTB = ~ (1<<4);           // Enable 1000's digit (DIG1)
        _delay_ms(PERSISTENCE);

        DIG2 = (i/100)%10;          // 100's digit
        uart_send(digit+'0'); 
        PORTD = ledDigits[DIG2];
        PORTB = ~ (1<<3);           // Enable 100's digit (DIG2)
        _delay_ms(PERSISTENCE);
     
        DIG3= (i/10)%10;            // 10's digit
        uart_send(digit+'0');
        PORTD = ledDigits[DIG3];   
        PORTB = ~ (1<<2);           // Enable 10's digit (DIG3)
        _delay_ms(PERSISTENCE);
            
        DIG4 = i%10;                // 1's digit (Least Significant Digit)
        uart_send(digit+'0');
        PORTD = ledDigits[DIG4];
        PORTB = ~ (1<<1);           // enable 1's digit (DIG4)
        _delay_ms(PERSISTENCE);     // stay on for small amount of time

        uart_send(13); // Carriage return (goto beginning of line)
        uart_send(10); //line feed (new line)
        
                   

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


