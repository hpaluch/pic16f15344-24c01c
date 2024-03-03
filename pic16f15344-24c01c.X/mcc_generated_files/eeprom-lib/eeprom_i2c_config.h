/**
 * EEPROM generated driver configuration header file.
 *
 * @file eeprom_i2c_config.h
 * 
 * @ingroup eeprom
 * 
 * @brief This file contains device-specific constants for the EEPROM driver.
 *
 * @version EEPROM Driver Version 1.0.1
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef EEPROM_I2C_CONFIG_H
#define EEPROM_I2C_CONFIG_H
 
#ifdef __cplusplus
extern "C" {
#endif

/**  
 * @ingroup eeprom
 * @name EEPROM device macros
 * EEPROM device size specification.
 */
///@{
#define EEPROM_I2C_DEVICE_ADDR   (0x50U)
#define EEPROM_I2C_WORD_ADDR_LEN_BYTES    (1U)
#define EEPROM_I2C_WORD_ADDR_LEN_BITS      (7U) // word address length in bits
#define EEPROM_I2C_SIZE          (128U) // internally organized value
#define EEPROM_I2C_PAGESIZE      (8U) // page size
#define EEPROM_I2C_PAGES         EEPROM_I2C_SIZE / EEPROM_I2C_PAGESIZE
///@}

#ifdef __cplusplus
}
#endif
 
#endif /* EEPROM_I2C_CONFIG_H */
