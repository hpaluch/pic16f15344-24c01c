 /**
 * EEPROM generated driver data types header file.
 *
 * @file eeprom_i2c_types.h
 * 
 * @ingroup eeprom
 * 
 * @brief This file contains type definitions for the EEPROM driver.
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

#ifndef EEPROM_I2C_TYPES_H
#define EEPROM_I2C_TYPES_H

#include "eeprom_i2c_config.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"

/**
 * @ingroup eeprom
 * @enum EEPROM_STATUS 
 * @brief Enumeration of the EEPROM driver status codes.
 */
typedef enum EEPROM_STATUS
{
    EEPROM_NO_ERROR = 0U,
    EEPROM_ERROR = 1U,
    EEPROM_I2C_TIMEOUT = 3U,
    EEPROM_INVALID_PARAMETER = 104U,
    EEPROM_NULL_ERROR = 105U,
    EEPROM_COM_ERROR = 106U
}EEPROM_STATUS_t;

/**
 * @ingroup eeprom
 * @struct EEPROM_DEVICE_CONTEXT 
 * @brief Contains the EEPROM driver context used in the API routines.
 */
typedef struct EEPROM_DEVICE_CONTEXT
{
    bool    busy;                                       /**< Sets the software busy flag.*/
    uint32_t startAddress;                              /**< Sets the starting word address of the device.*/
    uint8_t deviceAddress;                              /**< Sets the I2C address of the device.*/ 
    uint8_t wordAddress[EEPROM_I2C_WORD_ADDR_LEN_BYTES];     /**< Holds the word address buffer for the device operation.*/
    uint8_t dataBuffer[EEPROM_I2C_PAGESIZE];            /**< Holds the data address buffer for the read and write operation.*/
    uint8_t *writePtr;                                  /**< Pointer to write buffer for the write operation.*/
    size_t  writeLength;                                /**< Sets the write buffer length for the write operation.*/
    bool    firstWrite;                                 /**< Sets the write operation flag.*/
    uint8_t *readPtr;                                   /**< Pointer to read buffer for the read operation.*/
    size_t  readLength;                                 /**< Sets the read buffer length for the read operation.*/
    bool    switchToRead;                               /**< Sets the operation from Write to Read mode.*/
    EEPROM_STATUS_t errorState;                         /**< Sets the error state of the operation.*/
}EEPROM_DEVICE_CONTEXT_t;

#endif
