/**********************************************
* adc_serial.c  Reads analog voltage and writes
* result to the serial port. 
* Version 1.0 D. McLaughlin initial release
***********************************************/

#include "my_adc_lib.h"
#include "my_uart_lib.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

int main(void) {
    unsigned int digitalValue;
    char buffer[6]
    
    uart_init();
    adc_init();

    while (1) {
        digitalValue = get_adc();
        itoa(digitalValue, buffer, 10); //convert to a decimal character string
        send_string("Digitized value: ");
        send_string(buffer);
        uart_send(13); //send carriage return
        uart_send(10); //end line feed
        _delay_ms(1000);
    }
  
}
