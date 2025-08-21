# I2C Library for PIC16F877A (Master Mode)



## Overview
This is a lightweight **I²C Master Mode library** for the PIC16F877A microcontroller, written in C for MPLAB XC8.  
It provides clean APIs for initializing and using the MSSP module in I²C Master mode.  

The library is **generic**, and additional higher-level drivers (like PCF8574, LCD-I2C, EEPROM) can be built on top of it.  
An included example demonstrates controlling a **16x2 LCD** with a **PCF8574 backpack** in Proteus.



## Features

- Configurable clock frequency (default: 100 kHz).
- Supports Start, Stop, and Repeated Start conditions.
- Supports Write and Read with ACK/NACK handling.
- Clean reusable API with a single header (`i2c.h`).
- Example project included (LCD “Hello I2C LCD”).



## File Structure

i2c_lib_pic16f877a/

│── src/

│ ├── i2c.c #I²C implementation

│ └── i2c.h #I²C header / API

│── examples/

│ └── example.c #Test project using I²C LCD

│── README.md

│── LICENSE





## Integration into MPLAB X

To use this library in **MPLAB X IDE**:

1. Create a new MPLAB X project for **PIC16F877A**.
2. Copy `src/i2c.h` into the **Header Files** folder of your project.
3. Copy `src/i2c.c` into the **Source Files** folder of your project.
4. In your main application (`main.c`), include the header:
   ```c
   #include "i2c.h"
5. (Optional) To quickly test the library, copy examples/example.c into your project and rename it to main.c.

## Usage
### 2. Initialize I²C
Before using I²C functions, call:
I2C_Init();

### 3. Use I²C API
I2C_Start();
I2C_Write(0x4E);   // Example: slave address
I2C_Write(0x55);   // Example: data
I2C_Stop();


Example: LCD via PCF8574
The included example.c demonstrates driving a 16x2 LCD with a PCF8574 I²C backpack.

Connection (PIC16F877A):
RC3 → SCL
RC4 → SDA
LCD + PCF8574 powered with +5V and GND

Proteus Test Result:
Line 1 → Hello
Line 2 → I2C LCD

Example Snippet:
I2C_Init();
lcd_init();

lcd_cmd(0x80);   // Line 1
lcd_data('H'); lcd_data('e'); lcd_data('l'); lcd_data('l'); lcd_data('o');

lcd_cmd(0xC0);   // Line 2
lcd_data('I'); lcd_data('2'); lcd_data('C'); lcd_data(' '); 
lcd_data('L'); lcd_data('C'); lcd_data('D');


Test Plan / Checklist
✅ Compile with MPLAB XC8 (no errors/warnings).
✅ Simulate in Proteus with PIC16F877A + PCF8574 + LCD.
✅ LCD shows Hello (line 1) and I2C LCD (line 2).
✅ SDA/SCL waveforms observed in Proteus Logic Analyzer.
✅ Can adapt to other I²C devices (EEPROM, sensors, RTC).


## Author
Nkoloogi Blasius

## Contributors
Allan Ahumuza