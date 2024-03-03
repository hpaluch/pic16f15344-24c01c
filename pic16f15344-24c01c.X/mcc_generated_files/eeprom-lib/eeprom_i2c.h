 /**
 * EEPROM generated driver I2C interface header file.
 *
 * @file eeprom_i2c.h
 * 
 * @defgroup eeprom_i2c EEPROM_I2C
 * 
 * @brief This file contains constants and API declarations for the EEPROM device.
 *
 * To ensure that the C driver runs properly, do not modify the I2C API prototypes. Refer to eeprom_i2c.c to configure the I2C interface implementation.
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

#ifndef  EEPROM_I2C_H
#define	 EEPROM_I2C_H

#include <stddef.h>

/** 
 * @ingroup eeprom_i2c 
 * @name EEPROM I2C Status Codes
 * I2C interface status codes.
 */
///@{
#define EEPROM_I2C_NO_ERROR (0U)
#define EEPROM_I2C_ERROR (1U)
///@}

/**
 @ingroup eeprom_i2c
 @brief Writes the data to the EEPROM via the I2C bus.
 @pre Initialize the I2C Host and the EEPROM device.
 @param uint8_t deviceAddress - The EEPROM device address.
 @param uint8_t* data - Pointer to the data buffer that holds the target memory address and data of the EEPROM.
 @param size_t writeLength - Length of the target memory address and data in bytes.
 @return EEPROM I2C status code.
 */
uint8_t EEPROM_I2C_Write(uint8_t deviceAddress, uint8_t *data, size_t writeLength);

/**
 @ingroup eeprom_i2c
 @brief Reads the data from the EEPROM via the I2C bus.
 @pre Initialize the I2C Host and the EEPROM device.
 @param uint8_t deviceAddress - The EEPROM device address.
 @param uint8_t* eepromAddress - Pointer to the data buffer that holds the target memory address of the EEPROM.
 @param size_t addressLength - Length of the target memory address in bytes.
 @param uint8_t *readData - Pointer to the data buffer that holds the data read from the EEPROM.
 @param size_t readLength - Length of the data read from the EEPROM in bytes.
 @return EEPROM I2C status code.
 */
uint8_t EEPROM_I2C_Read(uint8_t deviceAddress, uint8_t *eepromAddress, size_t addressLength, uint8_t *readData, size_t readLength);

/**
 @ingroup eeprom_i2c
 @brief Checks if the data sent was acknowledged by the EEPROM device.
 @pre Initialize the I2C Host and the EEPROM device.
 @param deviceAddress - The EEPROM device address.
 @retval True - Acknowledged by the EEPROM device.
 @retval False - Not acknowledged by the EEPROM device.
 */
bool EEPROM_AckPoll(uint8_t deviceAddress);

#endif	/*  EEPROM_I2C_H */
