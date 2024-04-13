/* switches3.c This code turns on LEDs when  momentary pushbutton  
switches are pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
This is an updated version of switches2.c D. McLaughlin 2/21/22 
and uses #define macros and other variables to clean up code
D. McLaughlin 4/13/24 */

#include <avr/io.h>
#include <util/delay.h>
#define REDBUTTON PD3   // Arduino Uno pin 3
#define GREENBUTTON PD4 // Arduino Uno pin 4
#define REDLED PD6      // Arduino Uno pin 6
#define GREENLED PD7    // Arduino Uno pin 7

int main(void){
    unsigned char r_button, g_button;
    DDRD = 1<<REDLED|1<<GREENLED;           // Set as outputs
    PORTD = 1<<REDBUTTON|1<<GREENBUTTON;    // Enable internal pull-ups
                   
    while(1){

        r_button = (PIND & (1<<REDBUTTON));     // 1 when not pressed
        g_button = (PIND & (1<<GREENBUTTON));   // 0 when pressed

        if  (r_button){   
            PORTD &= ~(1<<REDLED);      // Off when button not pressed
        } else {
            PORTD |= (1<<REDLED);       // On when pressed
        }

        if  (g_button){                 
            PORTD &= ~(1<<GREENLED);     // Off when not pressed
        } else {
            PORTD |= (1<<GREENLED);       // On when pressed
        }

    }
}

/**** End of File *****/


