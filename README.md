# PIC16F15344 and I2C EEPROM 24C01C

Goal: Test I2C communication of PIC16F15344 and I2C EEPROM 24C01C.

WARNING! This circuit does not do anything useful on its own. It is designed
to use Debugger and Scope/Analyzer to see I2C communication in various stages.

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
- [24C01C][24C01C] I2C EEPROM 1Kbit (128 bytes) 5V (!!!), PDIP8 package
- LED and 470 Ohm resistor connected to PIN10 RB7
- LED and 470 Ohm resistor connected to PIN9 RB6

Scope and/or analyzer:
- [Digilent Analog Discovery 2][Digilent Analog Discovery 2]
- but see important note at the end of this README, regarding Digital Inputs(!)

Please see schematics below for details:

![PICDEM with 24C01C](ExpressPCB/pic16f-24c01c.png)

All schema files are in [ExpressPCB/](ExpressPCB/) folder.  Made
in [ExpressPCB Classic][ExpressPCB Classic].


# Software Requirements

* [XC8 compiler][XC compilers] - tested version v2.46 (Mar 2024)
* [MPLAB X IDE][MPLAB X IDE] - tested version v6.20 (Mar 2024)
* Device Family Pack `PIC12-16F1xxx_DFP` v1.24.387
* MCC Melody Tool

Please see [pic16f15344-24c01c.X/mcc-manifest-generated-success.yml](https://github.com/hpaluch/pic16f15344-24c01c/blob/master/pic16f15344-24c01c.X/mcc-manifest-generated-success.yml)
for Software details.

# Notes

> This section below is in progress - probably not needed:
> 
> MCC Melody is too simple to properly setup I2C Pins:
> 
> - has to manually set "Open Drain"
> - has to disable "slew control" (there are various HW bugs in PIC when slow rate control
>   is enabled)

According to datasheet, 24C01C requires for logical 1 value `0.7 * Vcc` which is `3.5V` for
Vcc=5V. One must be careful to avoid clamping of I2C signals to 3.3V logic (see below).

Important Digilent Analog Discovery 2 note:
- Do NOT connect I2C pins to Digilent Digital pins (D0 to D15)! 
- they will clamp I2C levels to `LVCMOS (3.3V max)` and will basically kill proper
  I2C communication (EEPROM will never ACK communication on I2C bus)

[XC compilers]: https://www.microchip.com/mplab/compilers
[MPLAB X IDE]: https://www.microchip.com/mplab/mplab-x-ide
[DM163045]: https://www.microchip.com/en-us/development-tool/dm163045 
[PIC16F15344]: https://www.microchip.com/en-us/product/PIC16F15344
[24C01C]: https://www.microchip.com/en-us/product/24c01c
[Digilent Analog Discovery 2]: https://store.digilentinc.com/analog-discovery-2-100msps-usb-oscilloscope-logic-analyzer-and-variable-power-supply/
[ExpressPCB Classic]: https://www.expresspcb.com/expresspcb-classic-pcb-layout-software/

