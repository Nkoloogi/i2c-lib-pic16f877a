/**
* @file i2c.c
 * @brief Implementation of I2C Master Mode functions for PIC16F877A
 * Author: Nkoloogi Blasius
 */

#include "i2c.h"

void I2C_Init(void) {
    SSPCON = 0b00101000;   // I2C Master mode
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ / (4 * I2C_SPEED)) - 1; // Baud rate formula
    SSPSTAT = 0x00;        // Standard speed mode
}

void I2C_Start(void) {
    SEN = 1;               // Initiate start condition
    while(SEN);            // Wait for completion
}

void I2C_RepeatedStart(void) {
    RSEN = 1;              // Initiate repeated start condition
    while(RSEN);           // Wait for completion
}

void I2C_Stop(void) {
    PEN = 1;               // Initiate stop condition
    while(PEN);            // Wait for completion
}

void I2C_Write(uint8_t data) {
    SSPBUF = data;         // Write data to buffer
    while(BF);             // Wait until data is shifted out
    while(SSPSTATbits.BF); // Wait for complete transmission
    while(SSPCON2 & 0x1F); // Wait for ACK/NACK
}

uint8_t I2C_Read(uint8_t ack) {
    uint8_t data;
    RCEN = 1;              // Enable receive mode
    while(!BF);            // Wait until buffer full
    data = SSPBUF;         // Read data

    ACKDT = (ack) ? 0 : 1; // 0=ACK, 1=NACK
    ACKEN = 1;             // Send ACK/NACK
    while(ACKEN);          // Wait for completion

    return data;
}
