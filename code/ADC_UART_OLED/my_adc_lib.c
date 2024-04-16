/***************************************
 * my_adc_lib.c 
 * Implementation of a library for initializing ADC peripheral
 * and obtaining digitized samples using ATmega328P MCU
 * Version Author           Date        Comment
 * 1.0      D. McLaughlin   4/16/24     initial release as a contributed libary
 * **************************************/

#include "my_adc_lib.h"

#include <avr/io.h>

// Initialize ADC peripheral
void adc_init(void)
{
    if (V_REF == 1.1){
        ADMUX = (1 << REFS1) | (1 << REFS0);    // Set reference voltage to 1.1 volts
    } else {
        ADMUX = 1 << REFS0;                     // Set ref voltage to AVcc
    }
    ADMUX |= ADC_CHANNEL;                       // Select appropriate input channel

    if (F_CPU == 16000000)
        ADCSRA = 0x87;                          // Enable ADC; divide by 128 for 16 MHz clock
    else
        ADCSRA = 0x83;                          // Enable ADC; divide by 8 for 1 MHZ clock
}

// Read ADC value
unsigned int get_adc()
{
    ADCSRA |= (1 << ADSC);                      // Start ADC conversion
    while ((ADCSRA & (1 << ADIF)) == 0);        // Wait till ADC finishes
    return ADCL | (ADCH << 8);                  // Read ADCL first !
}