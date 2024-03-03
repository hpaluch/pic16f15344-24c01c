/**
 * EEPROM generated driver I2C interface source file.
 *
 * @file eeprom_i2c.c
 * 
 * @ingroup eeprom_i2c
 * 
 * @brief This file contains API definitions for the EEPROM interface. This file can be modified to support other I2C drivers.
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

#include "../../eeprom-lib/eeprom_i2c_types.h"
#include "../../eeprom-lib/eeprom_i2c_config.h"
#include "../../eeprom-lib/eeprom_i2c.h"
#include "../../i2c_host/i2c.h"

#define EEPROM_I2C_ERROR (1U)
#define EEPROM_I2C_NO_ERROR (0U)

/**
 * @ingroup eeprom_i2c
 * @var *EEPROM_I2C
 * @brief An instance of the I2C Host driver interface for the EEPROM device.
 */
static const i2c_host_interface_t *EEPROM_I2C = &I2C1_Host;

uint8_t EEPROM_I2C_Write(uint8_t deviceAddress, uint8_t *data, size_t writeLength)
{
    uint8_t status = EEPROM_I2C_ERROR;
    if(EEPROM_I2C->Write( deviceAddress,
                          data,
                          writeLength)){
        while(EEPROM_I2C->IsBusy()){
            EEPROM_I2C->Tasks();
        }
        status = EEPROM_I2C_NO_ERROR;
    }
    return status;
}

uint8_t EEPROM_I2C_Read(uint8_t deviceAddress, uint8_t *eepromAddress, size_t addressLength, uint8_t *readData, size_t readLength)
{
    uint8_t status = EEPROM_I2C_ERROR;
    if(EEPROM_I2C->WriteRead( deviceAddress,
                              eepromAddress,
                              addressLength,
                              readData,
                              readLength )){
        while(EEPROM_I2C->IsBusy()){
            EEPROM_I2C->Tasks();
        }
        status = EEPROM_I2C_NO_ERROR;
    }
    return status;
}

bool EEPROM_AckPoll(uint8_t deviceAddress)
{
    if(EEPROM_I2C->Write(deviceAddress, NULL, 0) ||
       !(EEPROM_I2C->ErrorGet() != I2C_ERROR_ADDR_NACK))
    {
        while (EEPROM_I2C->IsBusy()){
            EEPROM_I2C->Tasks();
        }
    }
    return EEPROM_I2C->ErrorGet() != I2C_ERROR_ADDR_NACK;
}
