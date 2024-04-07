/* switches_with_blinker.c This code allows us to experiment with input
pins connected to switches with and without internal pullup
resistors. blinks an LED when a momemtary pushbutton  switch is 
pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
This code adds a blinking internal LED as a debugging tool
D. McLaughlin 2/21/22 */

#include <avr/io.h>
#include <util/delay.h>
#define MYDELAY 100

int main(void){
    DDRD = 1<<DDD6|1<<DDD7;             // Set D6, D7 as output
    PORTD = 1<<PORTD3|1<<PORTD4;        // Set pullup on D3 & D4
    DDRB = 1<< DDB5;                   // PB5 as output              
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

        //PORTB ^= 1<<PORTB5;             // Toggle the internal blinker
        _delay_ms(MYDELAY);
    }
    return(0);
}

/**** End of File *****/


