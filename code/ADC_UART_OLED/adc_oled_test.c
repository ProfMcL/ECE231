/*****************************************************************
 * adc_oled_test.c  Program to test the SSD1306 OLED display
 * using ADC inputs.
 *
 * Date         Author              Revision
 * 4/16/24     D. McLaughlin       initial writing of this code
 *******************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "SSD1306.h"
#include "my_adc_lib.h"

int main(void)
{
  unsigned int digValue;
  OLED_Init(); 
  adc_init();

  while (1)
  {
    digValue = get_adc();
    OLED_GoToLine(4);
    OLED_DisplayString("Dig Value : ");
    OLED_GoToLine(6);
    OLED_DisplayNumber(10, digValue, 4);
    _delay_ms(1000);
  }
}

/*** End of File***/