/* seven_main.c  This code demonstrates the use of a 4 digit 
7 segment LED. 
D. McLaughlin 3/16/22 ECE-231 Demo */

#include "avr/io.h"
#include "util/delay.h"

int main(void)
{
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,
        0x07, 0x7F, 0x67};
    unsigned char i=0;
    DDRD = 0xFF; //7segment pins
    
    while (1) {
        i++;
        if(i>9)
            i=0;
        PORTD = ledDigits[i]; //digit
        _delay_ms(10);
    }
}

/**** End of File ****/

