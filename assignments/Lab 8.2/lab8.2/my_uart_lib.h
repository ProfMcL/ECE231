/***************************************
 * my_uart_lib.h 
 * header file for my_uart_lib.c
 * user-contributed library for initializing UART
 * and transmitting characters and strings on ATmega328P MCU
 * Version Author           Date        Comment
 * 1.0      D. McLaughlin   4/16/24     Assumes 16 MHZ clock
 * **************************************/


#include <avr/io.h>
#include <string.h>

/* Initialize the UART: Enables the UART transmitter; 
* Sets 8 bit character size
* Sets baud rate to 9600 for 16 MHz crystal
* Arguments: none
* Returns: none */
void uart_init(void);

/* Transmit a single character via UART
* Arguments: 
*       letter - ASCII character to be transmitted
* Returns: none */
void uart_send(unsigned char letter);

/* Transmit a character string via UART.
* Sends the string, char by char, to the UART
* via uart_send()
* Arguments: 
*       *stringAddress - pointer to the string
* Returns: none */
void send_string(char *stringAddress);
