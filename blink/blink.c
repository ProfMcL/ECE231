/*******************************************************************
 * blink.c   -- Blink an LED on Port B pin5 (PB5).  
 * This is the built-in LED (pin13) on the Arduino Uno.
 * Date         Author          Revision
 * 12/14/21     D. McLaughlin   initial code creation
 * 1/9/22       D. McLaughlin   tested on host MacOS Monterey, Apple M1 pro
 * 2/12/22      D. McLaughlin   cleaned up formatting, added comments
 * 2/21/23      D. McLaughlin   changed PB5 to DDB5 and PORTB5 in lines 17, 20, 22
 * *****************************************************************/
 
 #include <avr/io.h>            // Defines port pins
 #include <util/delay.h>        // Declares _delay_ms
 #define MYDELAY 1000           // This will be the delay in msec
 
 int main(void){

     DDRB = 1<<DDB5;            // Initialize PB5 as output pin

     while(1){                  // Loop forever
         PORTB = 1<<PORTB5;     // Make PB5 high; LED ON
         _delay_ms(MYDELAY);    // Wait
         PORTB = ~ (1<<PORTB5); // Make PB5 low; LED off
         _delay_ms(MYDELAY);    // Wait
     }

     return 0;                  // Code never gets here. 
 }

 /******* End of File *********/

