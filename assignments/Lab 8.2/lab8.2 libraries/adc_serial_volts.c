/**********************************************
* adc_serial_volts.c  Reads analog voltage and writes
* both digital value and corresponding voltage result 
* to the serial port and the SSD1306 OLED
* Version 1.0 D. McLaughlin initial release
***********************************************/

#include "my_adc_lib.h"
#include "my_uart_lib.h"
#include "SSD1306.h"
#include "i2c.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

int main(void) {
    unsigned int digitalValue;
    double analogValue;
    char buffer[6];
    
    uart_init();
    adc_init();
    OLED_Init();

    while (1) {
        digitalValue = get_adc();
        itoa(digitalValue, buffer, 10); //convert to a decimal character string
        send_string("Digital: ");
        send_string(buffer);
        analogValue = digitalValue * V_REF / 1023;
        dtostrf(analogValue, 5, 3, buffer); // Convert to a character string
        send_string("   Analog: ");
        send_string(buffer);
        uart_send(13);
        uart_send(10);

        // Send the digital and analog values to the OLED
        OLED_GoToLine(1);
        OLED_DisplayString("Digital: ");
        OLED_GoToLine(3);
        OLED_DisplayNumber(10, digitalValue, 4);
        OLED_GoToLine(5);
        OLED_DisplayString("Analog:");
        OLED_GoToLine(6);
        OLED_DisplayString(buffer);
        _delay_ms(1000);
    }
  
}
