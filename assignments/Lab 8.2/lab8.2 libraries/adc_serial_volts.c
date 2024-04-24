/**********************************************
* adc_serial_volts.c  Reads analog voltage and writes
* both digital value and corresponding voltage result 
* to the serial port and the SSD1306 OLED
* Version     Author            Date     Description
*  1.0        D. McLaughlin     4/22/24  initial release
*  1.1        D. McLaughlin     4/25/24  better formatting and comments
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
    char buffer1[6], buffer2[6];
    
    uart_init();
    adc_init();
    OLED_Init();

    while (1) {

        // Take an ADC reading and create ASCII strings for digital representation & corresponding analog voltage
        digitalValue = get_adc();                     // The an ADC reading
        analogValue = digitalValue * V_REF / 1023;    // Convert digitalValue to corresponding analog voltage
        itoa(digitalValue, buffer1, 10);              // Convert the int to a character string in decimal
        dtostrf(analogValue, 5, 3, buffer2);          // Convert floating point to a character string
        
        // Send the digital and analog strings to the serial monitor
        send_string("Digital: ");
        send_string(buffer1);
        send_string("   Analog: ");
        send_string(buffer2);
        uart_send(13);
        uart_send(10);

        // Display the digital value and the analog character string on the OLED
        OLED_GoToLine(1);
        OLED_DisplayString("Digital: ");
        OLED_GoToLine(3);
        OLED_DisplayNumber(10, digitalValue, 4);
        OLED_GoToLine(5);
        OLED_DisplayString("Analog:");
        OLED_GoToLine(6);
        OLED_DisplayString(buffer2);
        _delay_ms(1000);
    }
  
}
