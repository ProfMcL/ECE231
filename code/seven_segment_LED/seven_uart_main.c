/* seven_uart_main.c  This code demonstrates the use of a 4 digit 
7 segment LED. This version counts 0-1000 repeatedly and uses
persistence to create an always-on effect in the digits. Digits
are also sent via UART. This code has D1 contention between UART &
the display. D. McLaughlin 3/20/22 ECE-231 Demo  */

#include "avr/io.h"
#include "util/delay.h"
#define PERSISTENCE 5
#define COUNTTIME 1000           // This is the # of ms beteen counts
void uart_init(void);
void uart_send(unsigned char);

int main(void){
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};
    unsigned int i=0;
    unsigned char DIG1, DIG2, DIG3, DIG4;
    uart_init();
    DDRD = 0xFF;    // 7segment pins
    DDRB = 0xFF;    // Digit enable pins
    
    while (1) {
        i++;
        if(i>9999) i=0;
       
        DIG4 = i%10;                // Compute 1's digit (Least sig digit)
        DIG3= (i/10)%10;            // Compute 10's digit
        DIG2 = (i/100)%10;          // Compute 100's digit
        DIG1 = (i/1000);            // Compute 1000's digit (Most sig digit)
        
        for (int j=0; j<COUNTTIME/PERSISTENCE/4; j++){
            PORTD = ledDigits[DIG1];        // 1000's digit (Most significant)
            uart_send(DIG1+'0');            // Tx 1000's digit
            PORTB = ~ (1<<4);               // Enable 1000's digit
            _delay_ms(PERSISTENCE);

            PORTD = ledDigits[DIG2];        // 100's digit
            uart_send(DIG2+'0');            // Tx 100's digit
            PORTB = ~ (1<<3);               // Enable 100's digit
            _delay_ms(PERSISTENCE);

            PORTD = ledDigits[DIG3];        // 10's digit
            uart_send(DIG3+'0');            // Tx 10's digit
            PORTB = ~ (1<<2);               // Enable 10's digit
            _delay_ms(PERSISTENCE);

            PORTD = ledDigits[DIG4];        // 1's digit (Lease sig digit)
            uart_send(DIG4+'0');            // Tx 1's digit 
            PORTB = ~ (1<<1);               // Enable 1's digit
            _delay_ms(PERSISTENCE);

            PORTB = 0xFF;                   // Disable all digits

            uart_send(13); // Carriage return (goto beginning of line)
            uart_send(10); //line feed (new line)
        }
    }
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