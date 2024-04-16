//
//  i2c.h
//  
//
//  Created by NullWolf on 09/07/17.
//  Copyright © 2017 NullWolf. All rights reserved.
//


#include <avr/io.h>
#include "i2c.h"

static bool masterMode;

// MODS TO THIS CODE BY DM FOR 16MHz CLOCK 4/4/22
void i2c_init(void)
{
    TWSR &= ~((1 << TWPS1) | (1 << TWPS0)); // pre-scalar 1
   // TWSR |=  (1<< TWPS1);  // This code changed by DM 4/4/22
   // TWSR &=  ~(1<< TWPS0); // pre-scaler = 16 
   // TWBR = ((F_CPU / F_I2C) - 16) / 2; // baud rate factor 12
     TWBR = ((F_CPU / F_I2C) - 16) /32; // baud rate factor 19.5 DM 4/4/22
}

uint8_t i2c_tx_start(bool mode)
{
    int8_t status = 0;
    masterMode = mode; // set global state of R/W bit

    /* clear interrupt flag, issue start command (gain control of bus as
       master), enable I2C (SCL and SDA are automatically reconfigured) */
    TWCR |=  (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* wait until start transmitted */
    while (!(TWCR & (1 << TWINT)));

    switch (TWSR & 0xF8) {
        /* start condition sent from master */
        case 0x08:
            status = TRANSMISSION_SUCCESS;
            break;

        /* repeat start condition sent from master */
        case 0x10:
            status = TRANSMISSION_SUCCESS;
            break;

        default:
            status = TRANSMISSION_ERROR;
            break;
    }

    return status;
}

uint8_t i2c_tx_address(uint8_t address)
{
    int8_t status = 0;

    TWDR = (address << 1) | masterMode;
    /* clear start command to release bus as master */
    TWCR &= ~(1 << TWSTA);
    /* clear interrupt flag */
    TWCR |=  (1 << TWINT);

    /* wait until address transmitted */
    while (!(TWCR & (1 << TWINT)));

    if (masterMode == MASTER_TRANSMITTER) {
        switch (TWSR & 0xF8) {
            /* address|write sent and ACK returned */
            case 0x18:
                status = TRANSMISSION_SUCCESS;
                break;

           /* address|write sent and NACK returned slave */
           case 0x20:
                status = TRANSMISSION_ERROR;
                break;

            /* address|write sent and bus failure detected */
            case 0x38:
                status = TRANSMISSION_ERROR;
                break;

            default:
                status = TRANSMISSION_ERROR;
                break;
        }
    } else if (masterMode == MASTER_RECEIVER) {
        switch (TWSR & 0xF8) {
            /* address|read sent and ACK returned */
            case 0x40:
                status = TRANSMISSION_SUCCESS;
                break;

            /* address|read sent and NACK returned */
            case 0x48:
                status = TRANSMISSION_ERROR;
                break;

            case 0x38:
                status = TRANSMISSION_ERROR;
                break;

            default:
                status = TRANSMISSION_ERROR;
                break;
        }
    }

    return status;
}

uint8_t i2c_tx_byte(uint8_t byteData)
{
    int8_t status = 0;
    TWDR  = byteData; // load data buffer with data to be transmitted
    TWCR |= (1 << TWINT); // clear interrupt flag

    /* wait until data transmitted */
    while (!(TWCR & (1 << TWINT)));

    /* retrieve transmission status codes */
    switch (TWSR & 0xF8) {
        /* byte sent and ACK returned */
        case 0x28:
            status = TRANSMISSION_SUCCESS;
            break;

        /* byte sent and NACK returned */
        case 0x30:
            status = TRANSMISSION_ERROR;
            break;

        /* byte sent and bus failure detected */
        case 0x38:
            status = TRANSMISSION_ERROR;
            break;

        default:
            status = TRANSMISSION_ERROR;
            break;
    }

    return status;
}

bool i2c_timeout(void)
{
    uint8_t time = TIMEOUT;
    int8_t status = BUS_DISCONNECTED;

    while (time-- > 0) {
        /* check to see if bus is ready */
        if ((TWCR & (1 << TWINT))) {
            status = BUS_CONNECTED;
            break;
        }
    }

    return status;
}

uint8_t i2c_rx_byte(bool response)
{
    int8_t status;

    if (response == ACK) {
        TWCR |= (1 << TWEA); // generate ACK
    } else {
        TWCR &= ~(1 << TWEA); // generate NACK
    }

    /* clear interrupt flag */
    TWCR |= (1 << TWINT);

    /* detect bus time-out */
    if (i2c_timeout() != BUS_DISCONNECTED) {
        /* retrieve transmission status codes or received data */
        switch (TWSR & 0xF8) {
            /* data byte read and ACK returned by master */
            case 0x50:
                status = TWDR;
                break;

            /* data byte read and NACK returned by master */
            case 0x58:
                status = TWDR;
                break;

            /* bus failure detected */
            case 0x38:
                status = TRANSMISSION_ERROR;
                break;

            default:
                status = TRANSMISSION_ERROR;
                break;
        }
    } else {
        status = TRANSMISSION_ERROR;
    }

    return status;
}

void i2c_tx_stop(void)
{
    /* clear interrupt flag, issue stop command (cleared automatically) */
    TWCR |= (1 << TWINT) | (1 << TWSTO);

    while (!(TWCR & (1 << TWSTO))); // wait until stop transmitted
}
