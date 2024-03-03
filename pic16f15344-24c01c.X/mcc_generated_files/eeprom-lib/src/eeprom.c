/**
 * EEPROM generated driver source file.
 *
 * @file eeprom.c
 * 
 * @ingroup eeprom
 * 
 * @brief Contains API definitions for the EEPROM driver.
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

#include "../../eeprom-lib/eeprom.h"
#include "../../eeprom-lib/eeprom_interface.h"
#include "../../eeprom-lib/eeprom_i2c_config.h"
#include "../../eeprom-lib/eeprom_i2c_types.h"
#include "../../eeprom-lib/eeprom_i2c.h"
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b)) /*!< Computes the minimum of \a a and \a b. */

/**
 @ingroup eeprom
 @brief Updates the write operation parameters.
 @param size_t dataLength - Length of the data written to the EEPROM in bytes.
 @param uint16_t pageCounter - Counts the pages that is written on.
 @return None.
 */
static void EEPROM_UpdateWriteData(uint16_t dataLength, uint16_t pageCounter);

/**
 @ingroup eeprom
 @brief Gets the lower byte of the word address from the target memory address.
 @param uint32_t address - The target memory address where the low byte of the memory address is taken from.
 @return The lower byte of the word address.
 */
static uint8_t EEPROM_WordAddressLowGet(uint32_t address);

/**
 @ingroup eeprom
 @brief Gets the upper byte of the word address from the target memory address.
 @param uint32_t address - The target memory address where the upper byte of the memory address is taken from.
 @return The upper byte of the word address.
 */
static uint8_t EEPROM_WordAddressHighGet(uint32_t address);

/**
 @ingroup eeprom
 @brief Gets the device address of the EEPROM.
 @param uint32_t address - The I2C address frame where the device address is taken from.
 @return The 8-bit device address.
 */
static uint8_t EEPROM_DeviceAddressGet(uint32_t address);

/**
 @ingroup eeprom
 @brief Performs the read and write operations of the driver.
 @param None.
 @return None.
 */
static void EEPROM_Tasks(void);

/**
 @ingroup eeprom
 @brief Resets the EEPROM status.
 @param None.
 @return None.
 */
static void EEPROM_Close(void);
static size_t null = 0;
static uint8_t *eepromStatusReadPtr;

const EEPROM_INTERFACE_t eeprom_interface = {
    .SequentialWrite = EEPROM_SequentialWrite,
    .SequentialRead = EEPROM_SequentialRead,
    .PageWrite = EEPROM_PageWrite,
    .PageRead = EEPROM_PageRead,
    .ByteWrite = EEPROM_ByteWrite,
    .ByteRead = EEPROM_ByteRead,
    .IsBusy = EEPROM_IsBusy
};

static EEPROM_DEVICE_CONTEXT_t eepromStatus = {0};

bool EEPROM_SequentialWrite(uint32_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (address > EEPROM_I2C_SIZE || dataLength == null)
    {
        eepromStatus.errorState = EEPROM_INVALID_PARAMETER;
    }
    else if (!EEPROM_IsBusy())
    {
        eepromStatus.busy = true;
        eepromStatus.startAddress = address;
        eepromStatus.deviceAddress = EEPROM_DeviceAddressGet(eepromStatus.startAddress);
        eepromStatus.writePtr = data;
        uint16_t minSize = (uint16_t) MIN(EEPROM_I2C_PAGESIZE, dataLength);
        for (uint16_t i = 0; i < minSize; i++)
        {
            eepromStatus.dataBuffer[i] = *(eepromStatus.writePtr + i);
        }
        eepromStatus.writeLength = dataLength;
        if(EEPROM_I2C_WORD_ADDR_LEN_BYTES == 2U){
        eepromStatus.wordAddress[0] = EEPROM_WordAddressHighGet(eepromStatus.startAddress);
        eepromStatus.wordAddress[1] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
        }
        else{
            eepromStatus.wordAddress[0] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
        }
        eepromStatus.firstWrite = true;
        eepromStatus.readPtr = NULL;
        eepromStatus.readLength = 0;
        eepromStatus.switchToRead = false;
        eepromStatus.errorState = EEPROM_NO_ERROR;
        retStatus = true;
    }
    else {
        eepromStatus.errorState = EEPROM_COM_ERROR;
    }
    while (EEPROM_IsBusy())
    {
        EEPROM_Tasks();
    }
    return retStatus;
}

bool EEPROM_SequentialRead(uint32_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (address > EEPROM_I2C_SIZE || dataLength == null)
    {
        eepromStatus.errorState = EEPROM_INVALID_PARAMETER;
    }

    else if (!EEPROM_IsBusy())
    {
        eepromStatus.busy = true;
        eepromStatus.startAddress = address;
        eepromStatus.deviceAddress = EEPROM_DeviceAddressGet(eepromStatus.startAddress);
        eepromStatus.writePtr = NULL;
        eepromStatus.writeLength = 0;
        if(EEPROM_I2C_WORD_ADDR_LEN_BYTES == 2U){
        eepromStatus.wordAddress[0] = EEPROM_WordAddressHighGet(eepromStatus.startAddress);
        eepromStatus.wordAddress[1] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
        }
        else{
            eepromStatus.wordAddress[0] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
        }
        eepromStatus.firstWrite = false;
        eepromStatus.readPtr = data;
        eepromStatus.readLength = dataLength;
        eepromStatus.switchToRead = true;
        eepromStatus.errorState = EEPROM_NO_ERROR;
        eepromStatusReadPtr = data;
        retStatus = true;
    }
    else {
        eepromStatus.errorState = EEPROM_COM_ERROR;
    }
    while (EEPROM_IsBusy())
    {
        EEPROM_Tasks();
    }
    return retStatus;
}

bool EEPROM_PageWrite(uint32_t address, uint8_t *data)
{
    return EEPROM_SequentialWrite(address, data, EEPROM_I2C_PAGESIZE);
}

bool EEPROM_PageRead(uint32_t address, uint8_t *data)
{
    bool retStatus = false;
    retStatus = EEPROM_SequentialRead(address, data, EEPROM_I2C_PAGESIZE);
    return retStatus;
}

bool EEPROM_ByteWrite(uint32_t address, uint8_t *data)
{
    bool retStatus = false;
    retStatus = EEPROM_SequentialWrite(address, data, 1);
    return retStatus;
}

bool EEPROM_ByteRead(uint32_t address, uint8_t *data)
{
    bool retStatus = false;
    retStatus = EEPROM_SequentialRead(address, data, 1);
    return retStatus;
}

EEPROM_STATUS_t EEPROM_ErrorGet(void)
{
    EEPROM_STATUS_t retErrorState = eepromStatus.errorState;
    return retErrorState;
}

bool EEPROM_IsBusy(void)
{
    return eepromStatus.busy;
}

static void EEPROM_Tasks(void)
{
    if (eepromStatus.switchToRead)
    {
        eepromStatus.switchToRead = false;
        while (!EEPROM_AckPoll(eepromStatus.deviceAddress)){};
        if (EEPROM_I2C_Read(eepromStatus.deviceAddress,
                                 eepromStatus.wordAddress,
                                 EEPROM_I2C_WORD_ADDR_LEN_BYTES,
                                 eepromStatusReadPtr,
                                 eepromStatus.readLength) == true)
        {
            eepromStatus.readLength = null;
            eepromStatus.switchToRead = false;
        }
        eepromStatus.busy = false;
    }

    else if (eepromStatus.writeLength > null)
    {
        uint16_t pageCounter = (uint16_t) (eepromStatus.startAddress / EEPROM_I2C_PAGESIZE);
        uint16_t dataLength;
        uint8_t *dataPtr = eepromStatus.wordAddress;
        if (eepromStatus.firstWrite)
        {
            dataLength = (uint16_t) EEPROM_I2C_PAGESIZE - (eepromStatus.startAddress % EEPROM_I2C_PAGESIZE);
            dataLength = (uint16_t) MIN(dataLength, eepromStatus.writeLength);
            eepromStatus.firstWrite = false;
        }
        else
        {
            dataLength = (uint16_t) MIN(EEPROM_I2C_PAGESIZE, eepromStatus.writeLength);
        }

        while (!EEPROM_AckPoll(eepromStatus.deviceAddress)){};
        if (!EEPROM_I2C_Write(eepromStatus.deviceAddress,
                              dataPtr,
                              dataLength + EEPROM_I2C_WORD_ADDR_LEN_BYTES))
        {
            EEPROM_UpdateWriteData(dataLength, pageCounter);
        }
        eepromStatus.busy = false;
    }
    else if (eepromStatus.writeLength == null && eepromStatus.readLength == null)
    {
        EEPROM_Close();
    }
    else 
    {
        eepromStatus.firstWrite = false;
        eepromStatus.switchToRead = false;
    }
}

static void EEPROM_Close(void)
{
    eepromStatus.busy = false;
    eepromStatus.writePtr = NULL;
    eepromStatus.writeLength = 0;
    eepromStatus.readPtr = NULL;
    eepromStatus.readLength = 0;
}

static void EEPROM_UpdateWriteData(uint16_t dataLength, uint16_t pageCounter)
{
    uint16_t eepromPage = EEPROM_I2C_PAGES;
    --eepromPage;
    if (pageCounter >= eepromPage)
    {
        eepromStatus.startAddress = null;
    }
    else
    {
        eepromStatus.startAddress += dataLength;
    }

    eepromStatus.writePtr += dataLength;
    eepromStatus.writeLength -= dataLength;
    uint16_t minSize = (uint16_t) MIN(EEPROM_I2C_PAGESIZE, eepromStatus.writeLength);
    --minSize;
    if (eepromStatus.writeLength > null)
    {
        for (uint16_t i = 0; i < minSize; i++)
        {
            eepromStatus.dataBuffer[i] = *(eepromStatus.writePtr + i);
        }
    }
    eepromStatus.deviceAddress = EEPROM_DeviceAddressGet(eepromStatus.startAddress);
    if(EEPROM_I2C_WORD_ADDR_LEN_BYTES == 2U)
    {
        eepromStatus.wordAddress[0] = EEPROM_WordAddressHighGet(eepromStatus.startAddress);
        eepromStatus.wordAddress[1] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
    }
    else
    {
        eepromStatus.wordAddress[0] = EEPROM_WordAddressLowGet(eepromStatus.startAddress);
    }
}

static uint8_t EEPROM_WordAddressLowGet(uint32_t address)
{
    return (uint8_t) (address & (uint32_t)0xFF);
}

static uint8_t EEPROM_WordAddressHighGet(uint32_t address)
{
    return (uint8_t) ((address >> 8) & (uint32_t)0xFF);
}

static uint8_t EEPROM_DeviceAddressGet(uint32_t address)
{
    uint8_t MSBAddress = 0;
#if EEPROM_I2C_WORD_ADDR_LEN_BITS == 10
    MSBAddress = (uint8_t) ((address & (uint32_t)0x300) >> 8);
#elif EEPROM_I2C_WORD_ADDR_LEN_BITS == 11
    MSBAddress = (uint8_t) ((address & (uint32_t)0x700) >> 8);
#elif EEPROM_I2C_WORD_ADDR_LEN_BITS == 17
    MSBAddress = (uint8_t) ((address & (uint32_t)0x10000) >> 16);
#elif EEPROM_I2C_WORD_ADDR_LEN_BITS == 18
    MSBAddress = (uint8_t) ((address & (uint32_t)0x30000) >> 16);
#endif
    return EEPROM_I2C_DEVICE_ADDR | MSBAddress;
}
