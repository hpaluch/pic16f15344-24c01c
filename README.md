# PIC16F15344 and I2C EEPROM 24C01C

Goal: Test I2C communication of PIC16F15344 and I2C EEPROM 24C01C.

Status:
- UNSTABLE: Using I2C and EEPROM components, but EEPROM components is incompatible
  with current I2C component - I created monkey patch header
  - `pic16f15344-24c01c.X/mcc_generated_files/i2c_host/i2c.h`
  and also patched Interface variable name in
  - `pic16f15344-24c01c.X/mcc_generated_files/eeprom-lib/src/eeprom_i2c.c`
- blinking LED on PIN10 RB7 using polling in `main()` loop.
- blinking LED on PIN9 RC7 using TMR0 Interrupt

# Hardware

Development board:
- [PICDEM DM163045][DM163045] development board (you can use any PIC board that
  supports 20 pin [PIC16F15344][PIC16F15344]). I have one that is now 10 years old
  and I still like it - there is everything I need to work with 8-bit PIC MCUs.

Additional parts (not included with PICDEM):
- Power supply 9V (or 9V battery) to power PICDEM board and its LM317 Voltage
  regulator.
  - ensure that output from LM317 regulator is exactly 5V.
- [PIC16F15344][PIC16F15344] PDIP20 package
[ [24C01C][24C01C] I2C EEPROM 1Kbit (128 bytes) 5V (!!!), PDIP8 package
- LED and 470 Ohm resistor connected to PIN10 RB7
- LED and 470 Ohm resistor connected to PIN9 RB6

EEPROM Wiring:

| PIC pin | EEPROM pin | Description |
| --- | --- | --- |
| 16 | 6 | I2C SCL, RC0 |
| 15 | 5 | I2C SDA, RC1 |

- EEPROM pull-ups: 4k7 on pin 6 (SCL) and pin 5 (SDA)
- EEPROM GND: pin 1 (A0), pin 2 (A1), pin3 (A2), pin4 (Vss)
- EEPROM +5V: pin 8


# Software Requirements

* [XC8 compiler][XC compilers] - tested version v2.46 (Mar 2024)
* [MPLAB X IDE][MPLAB X IDE] - tested version v6.20 (Mar 2024)
* Device Family Pack `PIC12-16F1xxx_DFP` v1.24.387
* MCC Melody Tool 

Please see [pic16f15344-24c01c.X/mcc-manifest-generated-success.yml](https://github.com/hpaluch/pic16f15344-24c01c/blob/master/pic16f15344-24c01c.X/mcc-manifest-generated-success.yml)
for Software details.

[XC compilers]: https://www.microchip.com/mplab/compilers
[MPLAB X IDE]: https://www.microchip.com/mplab/mplab-x-ide
[DM163045]: https://www.microchip.com/en-us/development-tool/dm163045 
[PIC16F15344]: https://www.microchip.com/en-us/product/PIC16F15344
[24C01C]: https://www.microchip.com/en-us/product/24c01c
