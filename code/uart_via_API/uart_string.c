/***************************************************************** 
 * uart_string.c - This code sends strings to com port via uart.
 * Version     Date     Author          Revision
 * 1.0      12/16/21     D. McLaughlin   Initial writing of the code
 * 1.1      1/15/22     D. McLaughlin   Tested on Arduino Uno w/ Apple M1 pro
 *                          host running Monterey
 * 1.2      2/27/22     D. McLaughlin   tested on Windows 11 on Parallels VM
 * 1.3      4/21/22     D. McLaughlin   re-written using uart.c/uart.h API
 * 2.0      4/7/24      D. McL          improved formatting   
 *****************************************************************/

// __________ preamble __________
#include <util/delay.h>
#include "my_uart_lib.h"

int main(void){

    // __________ inits __________
    char mystring[]= "This is pretty cool stuff!";
    uart_init(); // initialize the USART

    // __________ event loop __________
    while (1) {
        send_string(mystring);
        uart_send(13); // Carriage return (goto beginning of line)
        uart_send(10); //line feed (new line)
        _delay_ms(50);
    }  // end of event loop
}

/***** End of file *****/
