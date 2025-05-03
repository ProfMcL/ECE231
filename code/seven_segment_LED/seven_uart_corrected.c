/* seven_uart_corrected.c  Demonstrates simultaneous display
of a 4 digit ring counter (0000-9999) to UART & 4 digit, 7 
segment LED. PC0-3 & PD4-7 used for segments a-d, e-dp.
D. McLaughlin 3/19/22 ECE-231 Demo */

#include "avr/io.h"
#include "util/delay.h"
#define PERSISTENCE 5
#define COUNTTIME 1000           // # ms between counts
void uart_init(void);
void uart_send(unsigned char);

int main(void){
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};
    unsigned int i=0;
    unsigned char DIG1, DIG2, DIG3, DIG4;
    uart_init();    // Initialize the UART
    DDRC = 0x0F;    // Segments a-d use PC0-PC3
    DDRD = 0xF0;    // Segments e-g & dp  use PD4-PD7
    DDRB = 0xFF;    // Digit enable pins
    
    while (1) {
        i++;
        if(i>9999) i=0;
       
        DIG4 = i%10;        // 1's digit (least significant digit)
        DIG3= (i/10)%10;    // 10's digit
        DIG2 = (i/100)%10;  // 100's digit
        DIG1 = (i/1000);    // 1000's digit (most significant digit)
        
        for (int j=0; j<COUNTTIME/PERSISTENCE/4; j++){
        
            // Show 1000's digit
            PORTC = ledDigits[DIG1];
            PORTD = ledDigits[DIG1];
            uart_send(DIG1+'0');                // Tx 1000's digit
            PORTB = ~ (1<<4);                   // Enable DIG1           
            _delay_ms(PERSISTENCE);

            // Show 100's digit
            PORTC = ledDigits[DIG2];      
            PORTD = ledDigits[DIG2];      
            uart_send(DIG2+'0');                // Tx 100's digit
            PORTB = ~ (1<<3);                   // Enable DIG2
            _delay_ms(PERSISTENCE);

            // Show 10's digit
            PORTC = ledDigits[DIG3];     
            PORTD = ledDigits[DIG3];     
            uart_send(DIG3+'0');                // Tx 100's digit
            PORTB = ~ (1<<2);                   // Enable DIG3
            _delay_ms(PERSISTENCE);

            // Show 1's digit
            PORTC = ledDigits[DIG4];
            PORTD = ledDigits[DIG4];
            uart_send(DIG4+'0');                // Tx 10's digit              
            PORTB = ~ (1<<1);                   // Enable DIG4
            _delay_ms(PERSISTENCE);

            PORTB = 0xFF;                       // Disable all digits
            uart_send(13);                      // Tx carriage return 
            uart_send(10);                      // Tx line feed
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

/*** End of File ***/
