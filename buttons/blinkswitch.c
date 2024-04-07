/* blinkswitch.c This code blinks an LED when a 
momemtary pushbutton  switch is pressed. 
LED on PD7, Switch on PD4
D. McLaughlin 2/21/22 */

#include <avr/io.h>
#include <util/delay.h>
#define DURATION 2000

int main(void){
    DDRD = 1<<DDD7;     // D7 as output; other pins input
    PORTD = 1<<PORTD4;  // Set internal pullup resistor on D4
    while(1){

        if  ((PIND & (1<<PIND4)) == 0){ // PIND4=0 when pressed
            PORTD ^= (1<<PORTD7);
            _delay_ms(DURATION);
        } else {
            PORTD &= ~(1<<PORTD7);      // When button isn't pressed
        }
    }
    return(0);
}

