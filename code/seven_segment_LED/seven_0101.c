/* seven_0101.c  This code displays the digits 0, 1, 0., 1.
in sequence on DIG4 of the 4 digit, 7 segment (+ dp) LED
display. This is a demo for ECE-231 Spring 2023
D. McLaughlin 3/7/23 */

#include <avr/io.h>
#include <util/delay.h>
#define MYDELAY 500

int main(void){
    DDRD = 0xFF;       // Set all 8 pins as output
    
    while(1){
        PORTD = 0x3f;   // Illuminate 0
        _delay_ms(MYDELAY);
        PORTD = 0x06;   // Illuminate 1
        _delay_ms(MYDELAY);
        PORTD = 0xBF;   // Illuminate 0.
        _delay_ms(MYDELAY);
        PORTD = 0x86;   // Illuminate 1.
        _delay_ms(4*MYDELAY); // Longer delay before repeating
    }
}

/*** End of File ***/

