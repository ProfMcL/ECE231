/*******************************************************************
 * RGB_sequencer.c   Blinks the LED's of the RGB LED Light Strip 
 * in sequence. This code uses bitl-level manpulations to to turn on 
 * and off individual R, G, B bits to achieve desired colors. 
 * Assume R = PB1; G = PB2; B = PB3.  
 * Version  Date         Author          Revision
 * 1.0      4/8/25     D. McLaughlin   initial code creation
 * *****************************************************************/
 
 
 // __________ preamble __________
 #include <avr/io.h>            // Defines port pins
 #include <util/delay.h>        // Declares _delay_ms
 #define ONDELAY 2000           // LEDs ON in msec
 #define RED PB1
 #define GREEN PB2
 #define BLUE PB3
 
 int main(void){

    // __________ inits __________
     DDRB = 1<<DDB1|1<<DDB2|1<<DDB3;            // Make PB1, PB2, PB3 outputs; PB0 & PB4-PB7 inputs

    // __________ event loop __________
     while(1){                                  // Loop forever
         
        // Make the light strip Red
        PORTB = 1<<RED;                         // Red ON
        PORTB &= ~(1<<GREEN);                   // Green off
        PORTB &= ~(1<<BLUE);                    // Blue off
         _delay_ms(ONDELAY);                    // Wait
         
        //  Make the light strip green
        PORTB &= ~(1<<RED);                     // Red off
        PORTB |= (1<<GREEN);                    // Green ON
        PORTB &= ~(1<<BLUE);                    // Blue off
        _delay_ms(ONDELAY);                     // Wait

        //  Make the light strip blue
        PORTB &= ~(1<<RED);                     // Red off
        PORTB &= ~(1<<GREEN);                   // Green off
        PORTB |= (1<<BLUE);                     // Blue ON
        _delay_ms(ONDELAY);                     // Wait

        //  Make the light strip magenta (red + blue)
        PORTB |= (1<<RED);                      // Red ON
        PORTB &= ~(1<<GREEN);                   // Green off
        PORTB |= (1<<BLUE);                     // Blue ON
        _delay_ms(ONDELAY);                     // Wait

     } // end event loop

     return 0;                  // Code never gets here. 
 }

 /******* End of File *********/
