/* seven_counter_main.c  This code demonstrates the use of a 4 digit 
7 segment LED. This version counts 0-1000 repeatedly and uses retinal
persistence to create an always-on effect in the digits
D. McLaughlin 3/16/22 ECE-231 Demo */


#include "avr/io.h"
#include "util/delay.h"
#define PERSISTENCE 5

int main(void){

    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};
    unsigned int i=0;
    unsigned char DIG1, DIG2, DIG3, DIG4;

    DDRD = 0xFF;    // 7segment pins
    DDRB = 0xFF;    // Digit enable pins
    PORTB = 0xFF;   // Disable all the digits initially

    while (1) {
        i++;
        if(i>9999) i=0;
        
        DIG4 = i%10;                // 1's digit (Least Significant Digit)
        PORTD = ledDigits[DIG4];
        PORTB = ~ (1<<1);           // enable 1's digit (DIG4)
        _delay_ms(PERSISTENCE);     // stay on for small amount of time

        DIG3= (i/10)%10;            // 10's digit
        PORTD = ledDigits[DIG3];   
        PORTB = ~ (1<<2);           // Enable 10's digit (DIG3)
        _delay_ms(PERSISTENCE);
        
        DIG2 = (i/100)%10;          // 100's digit
        PORTD = ledDigits[DIG2];
        PORTB = ~ (1<<3);           // Enable 100's digit (DIG2)
        _delay_ms(PERSISTENCE);
        
        DIG1 = (i/1000);            // 1000's digit (Most signif digit)
        PORTD = ledDigits[DIG1];
        PORTB = ~ (1<<4);           // Enable 1000's digit (DIG1)
        _delay_ms(PERSISTENCE);
    }
}

/*** End of File ***/
