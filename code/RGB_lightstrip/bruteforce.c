/*******************************************************************
 * bruceforce.c   Blinks the RGB LED Light Strip 
 * This code uses "brute force" to turn all bits of portB on and
 * off in a blinking pattern. Result is white LED's only. 
 * Version  Date         Author          Revision
 * 1.0      4/8/25     D. McLaughlin   initial code creation
 * *****************************************************************/
 
 
 // __________ preamble __________
 #include <avr/io.h>            // Defines port pins
 #include <util/delay.h>        // Declares _delay_ms
 #define ONDELAY 3000           // LEDs ON in msec
 #define OFFDELAY 1000          // LEDs OFF in msec
 
 int main(void){

    // __________ inits __________
     DDRB = 0xFF;            // Make all of PortD output pins

    // __________ event loop __________
     while(1){                  // Loop forever
         PORTB = 0xFF;          // Make all pins of Port D high
         _delay_ms(ONDELAY);    // Wait
         PORTB = 0x00;          // Make all pins of Port D low
         _delay_ms(OFFDELAY);    // Wait
     } // end event loop

     return 0;                  // Code never gets here. 
 }

 /******* End of File *********/

 