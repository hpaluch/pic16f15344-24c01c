# PIC16F15344 and I2C EEPROM 24C01C

Goal: Test I2C communication of PIC16F15344 and I2C EEPROM 24C01C.


Status:
- just blinking LED on RB7 using polling.

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
- LED and 470 Ohm resistor connected to PIN10 RB7

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

