/************************************************************
Lab8_1.c Blinks LEDs when buttons are pressed:  
    Button on PD3 blinks a red LED
    Button on PD4 blinks a green LED
    Button on PD5 blinks both red & green LEDs
    No blinking when more than one button is simultaneously pressed.
V1.0    D. McLaughlin   4/13/24 
************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#define REDBUTTON PD3   // Arduino Uno pin 3
#define GREENBUTTON PD4 // Arduino Uno pin 4
#define THIRDBUTTON PD5 // Arduino Uno pin 5
#define REDLED PD6      // Arduino Uno pin 6
#define GREENLED PD7    // Arduino Uno pin 7
#define MYDELAY 100     // Half-period for 5 Hz blink

int main(void){
    unsigned char r_button, g_button, t_button;
    DDRD = 1<<REDLED|1<<GREENLED;                           // Set as outputs
    PORTD = 1<<REDBUTTON|1<<GREENBUTTON|1<<THIRDBUTTON;     // Enable internal pull-ups
                   
    while(1){

        r_button = (PIND & (1<<REDBUTTON));                 // These variables will be
        g_button = (PIND & (1<<GREENBUTTON));               // 0 when button pressed
        t_button = (PIND & (1<<THIRDBUTTON));               // 1 when not pressed

        if  (!r_button && g_button && t_button){            // Only r_button pressed
            PORTD ^= (1<<REDLED);                           // Toggle RED
        } else if (r_button && !g_button && t_button) {
            PORTD ^= (1<<GREENLED);                         // Toggle GREEN
        } else if  (r_button && g_button && !t_button){                 
            PORTD ^= (1<<GREENLED|1<<REDLED);               // Toggle Both
        } else {
            PORTD &= ~(1<<REDLED|1<<GREENLED);              // Both off
        }
        _delay_ms(MYDELAY);                                 // Gives us 5 HZ
    }
}

/**** End of File *****/


