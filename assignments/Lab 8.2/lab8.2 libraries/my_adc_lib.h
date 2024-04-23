/***************************************
 * my_adc_lib.h 
 * header file for my_adc_lib.c: a library for initializing ADC peripheral
 * and obtaining digitized samples using ATmega328P MCU
 * Version Author           Date        Comment
 * 1.0      D. McLaughlin   4/16/24     initial release as a contributed libary
 * **************************************/


// Change these two defines as needed for your application.
// See Section 24.9 of the ATmega328P data sheet for reference
#define ADC_CHANNEL 0       
#define V_REF   5.        


/* Initialize the ADC module: selects ADC input and reference
* voltage. Sets sampling speed depending on clock rate
* Arguments:  none
* Returns: none 
*/
void adc_init(void);


/* Read ADC input from ADC_CHANNEL
* Arguments: none
* Returns: 10 bit right-justified digitized word
*/
unsigned int get_adc(void);