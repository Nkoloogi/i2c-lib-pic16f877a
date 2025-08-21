/**
* @file i2c.h
 * @brief I2C Master Mode library for PIC16F877A
 * Author: Nkoloogi Blasius
 * This library provides functions to initialize and use the MSSP (Master Synchronous
 * Serial Port) module of PIC16F877A in I2C Master mode. It supports basic read/write
 * operations to communicate with I2C slave devices.
 *
 * Note: This library is written for MASTER MODE ONLY.
 */

#ifndef I2C_H
#define I2C_H

#include <xc.h>
#include <stdint.h>

/* ---------------- CONFIGURABLE PARAMETERS ---------------- */
#define _XTAL_FREQ 4000000   // System oscillator frequency (4 MHz)
#define I2C_SPEED 100000      // Desired I2C medium speed in Hz (100kHz)

/* ---------------- API FUNCTION DECLARATIONS ---------------- */
void I2C_Init(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read(uint8_t ack);

#endif // I2C_H
