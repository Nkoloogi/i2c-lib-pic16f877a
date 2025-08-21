/**
* @file example.c
* @brief Example program using the I2C library.
* Author: Nkoloogi Blasius
* Date: August 2025
* Connect PIC16F877A with an I2C slave device (like PCF8574 or EEPROM).
*/

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF
#define _XTAL_FREQ 4000000   // match the value in i2c.h
#include <xc.h>
#include "i2c.h"
//#define _XTAL_FREQ 20000000  // adjust to your clock

#define LCD_ADDR 0x4E  // PCF8574 default address for LCD backpack

void lcd_send(unsigned char data, unsigned char rs) {
    unsigned char high = data & 0xF0;     // higher nibble
    unsigned char low  = (data << 4) & 0xF0; // lower nibble

    // Send high nibble
    I2C_Start();
    I2C_Write(LCD_ADDR);
    I2C_Write(high | rs | 0x0C); // Enable=1, Backlight=On
    I2C_Write(high | rs | 0x08); // Enable=0
    I2C_Stop();

    // Send low nibble
    I2C_Start();
    I2C_Write(LCD_ADDR);
    I2C_Write(low | rs | 0x0C);
    I2C_Write(low | rs | 0x08);
    I2C_Stop();

    __delay_ms(2);
}

void lcd_cmd(unsigned char cmd) {
    lcd_send(cmd, 0x00);
}

void lcd_data(unsigned char data) {
    lcd_send(data, 0x01);
}

void lcd_init(void) {
    __delay_ms(20);
    lcd_cmd(0x02);  // Initialize
    lcd_cmd(0x28);  // 4-bit, 2 line, 5x8 font
    lcd_cmd(0x0C);  // Display on, cursor off
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x01);  // Clear
}

void main(void) {
    I2C_Init();
    lcd_init();

    lcd_cmd(0x80);  // Line 1
    lcd_data('H');
    lcd_data('a');
    lcd_data('l');
    lcd_data('l');
    lcd_data('o');

    lcd_cmd(0xC0);  // Line 2
    lcd_data('I');
    lcd_data('2');
    lcd_data('C');
    lcd_data(' ');
    lcd_data('L');
    lcd_data('C');
    lcd_data('D');

    while(1);
}
