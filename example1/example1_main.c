/******************************
 * example1_main.c makes PC4-PC7 high and 
 * glows LEDs connected to these pins. 
 * These are pins 4-7 on Arduino Uno
 * Date         Author          Revision
 * 2/14/22      D. McLaughlin   initial release
 * *****************************/

#include <avr/io.h>

int main(void){
    DDRD = 0xFF;    // Corresponds to 1111 1111
    PORTD = 0xF0;   // Corresponds to 1111 0000

    while(1);       // Wait forever
}