/******************************
 * example2_main.c Alternately blinks LEDS on PD0-PD3 and
 * PD4-PD7 with 250 mS beteeen blinks. 
 * Uses pins 0-3 (PD0-PD3) and 4-7 (PD4-PD7) on Arduino Uno
 * Date         Author          Revision
 * 2/14/22      D. McLaughlin   initial release
 * *****************************/

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    
    DDRD = 0xFF;        // Make all pins output

    while(1){           // Loop forever
        PORTD = 0xF0;   // PD0-PD3 low; PD4-PD7 high
        _delay_ms(250); // Wait 250 mSec
        PORTD = 0x0F;   // PD0-PD3 high; PD4-PD7 low
        _delay_ms(250);
    }
    
    return(0);
}

