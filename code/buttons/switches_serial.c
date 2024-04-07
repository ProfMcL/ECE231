/* switches_serial.c This code turns on LEDs when  momemtary pushbutton  
switches are pressed. Input pins on PD3 and PD4. LEDS on PD6 on PD7
Code also sends text string to serial monitor via UART
D. McLaughlin 2/22/22 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>  //so that we can use the  strlen() function
#include <stdlib.h>  //need for itoa function
void uart_init(void);
void uart_send(unsigned char);
void send_string(char *stringAddress);

int main(void){
    DDRD = 1<<DDD6|1<<DDD7;             // Set D6, D7 as output
    PORTD = 1<<PORTD3|1<<PORTD4;        // Set pullup on D3 & D4
    uart_init();                        // Initialize the UART
    while(1){

        if  ((PIND & (1<<PIND3)) == 0){ // PIND3 is 0 when pressed
            PORTD |= (1<<PORTD6);       // P6 high when P3 is pressed
            send_string("Left button is pressed!\n");
            uart_send(13);
        } else {
            PORTD &= ~(1<<PORTD6);      // P6 low when P3 not pressed
        }

        if  ((PIND & (1<<PIND4)) == 0){ // PIND4=0 when pressed
            PORTD |= (1<<PORTD7);       // P7 high when P4 is pressed
            send_string("\t\t\tRight button is pressed!\n");
            uart_send(13);
        } else {
            PORTD &= ~(1<<PORTD7);      // P7 low when P4 not pressed
        }
    }
    return(0);
}

void uart_init(void){
    UCSR0B = (1 << TXEN0); //enable the USART transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //set 8 bit character size
    UBRR0L = 103; //set baud rate to 9600 for 16 MHz crystal
}

void uart_send(unsigned char ch){
    while (!(UCSR0A & (1 << UDRE0))); //wait til tx data buffer empty
    UDR0 = ch; //write the character to the USART data register
}

void send_string(char *stringAddress){
    unsigned char i;
    for (i = 0; i < strlen(stringAddress); i++)
        uart_send(stringAddress[i]);
}

/**** End of File *****/
