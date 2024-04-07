/* switches2.c This code turns on LEDs when  momentary pushbutton  
switches are pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
D. McLaughlin 2/21/22 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRD = 1<<DDD6|1<<DDD7;             // Set D6, D7 as output
    PORTD = 1<<PORTD3|1<<PORTD4;        // Set pull-up on D3 & D4
                   
    while(1){

        if  ((PIND & (1<<PIND3)) == 0){ // PIND3 is 0 when pressed
            PORTD |= (1<<PORTD6);       // P6 high when P3 is pressed
        } else {
            PORTD &= ~(1<<PORTD6);      // P6 low when P3 not pressed
        }

        if  ((PIND & (1<<PIND4)) == 0){ // PIND4=0 when pressed
            PORTD |= (1<<PORTD7);       // P7 high when P4 is pressed
        } else {
            PORTD &= ~(1<<PORTD7);      // P7 low when P4 not pressed
        }

    }
    return(0);
}

/**** End of File *****/


