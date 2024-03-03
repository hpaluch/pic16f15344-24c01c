 /**
 * EEPROM generated driver header file.
 *
 * @file eeprom.h
 * 
 * @defgroup eeprom EEPROM
 * 
 * @brief This file contains API prototypes for the EEPROM driver.
 *
 * @version EEPROM Driver Version 1.0.1
*/
/*
� [2024] Microchip Technology Inc. and its subsidiaries.

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

#ifndef EEPROM_H
#define EEPROM_H

#include "eeprom_interface.h"
/**
 * @ingroup eeprom
 * @struct eeprom_interface
 * @brief Creates an instance of the EEPROM interface for the devices.
 */
extern const EEPROM_INTERFACE_t eeprom_interface;

/**
 @ingroup eeprom
 @brief Writes a byte of data to a specified address in the EEPROM device.
 @param uint32_t address - The data is written at this EEPROM address.
 @param uint8_t* data - Pointer to a byte of user-defined data that will be written to the EEPROM device.
 @retval True - Write operation is successful.
 @retval False - Write operation is unsuccessful.
 */
bool EEPROM_ByteWrite(uint32_t address, uint8_t *data);

/**
 @ingroup eeprom
 @brief Reads a byte of data from a specified address in the EEPROM device.
 @param uint32_t address - The data is read from this EEPROM address.
 @param uint8_t* data - Pointer to user-defined data buffer that holds the data read from the EEPROM device.
 @retval True - Read operation is successful.
 @retval False - Read operation is unsuccessful.
 */
bool EEPROM_ByteRead(uint32_t address, uint8_t *data);

/**
 @ingroup eeprom
 @brief Checks if the EEPROM device is busy.
 @param None.
 @retval True - The device is busy.
 @retval False - The device is not busy.
 */
bool EEPROM_IsBusy(void);

/**
 @ingroup eeprom
 @brief Writes n-bytes of data to a specified start address in the EEPROM device.
 @param uint32_t address - The data is written at this target memory address.
 @param uint8_t* data - Pointer to user-defined data that will be written to the EEPROM device.
 @param size_t dataLength - Length of the data written to the EEPROM in bytes.
 @retval True - Write operation is successful.
 @retval False - Write operation is unsuccessful.
 */
bool EEPROM_SequentialWrite(uint32_t address, uint8_t *data, size_t dataLength);

/**
 @ingroup eeprom
 @brief Reads n-bytes of data from a specified start address in the EEPROM device.
 @param uint32_t address - The data is read from this EEPROM address.
 @param uint8_t* data - Pointer to user-defined data buffer that holds the data read from the EEPROM device.
 @param size_t dataLength - Length of the data read from the EEPROM in bytes.
 @retval True - Read operation is successful.
 @retval False - Read operation is unsuccessful.
 */
bool EEPROM_SequentialRead(uint32_t address, uint8_t *data, size_t dataLength);

/**
 @ingroup eeprom
 @brief Writes the data to an entire page of the EEPROM device.
 @param uint32_t address - The data is written at this EEPROM address.
 @param uint8_t* data - Pointer to user-defined data that will be written to the EEPROM device.
 @retval True - Write operation is successful.
 @retval False - Write operation is unsuccessful.
 */
bool EEPROM_PageWrite(uint32_t address, uint8_t *data);

/**
 @ingroup eeprom
 @brief Reads the data of an entire page of the EEPROM device.
 @param uint32_t address - The data is read from this EEPROM address.
 @param uint8_t* data - Pointer to user-defined data buffer that holds the data read from the EEPROM device.
 @retval True - Read operation is successful.
 @retval False - Read operation is unsuccessful.
 */
bool EEPROM_PageRead(uint32_t address, uint8_t *data);

/**
 @ingroup eeprom
 @brief Checks the type of the error encountered in the EEPROM operation.
 @param None.
 @return EEPROM status code.
 */
EEPROM_STATUS_t EEPROM_ErrorGet(void);

#endif //EEPROM_H
