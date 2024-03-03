 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/eeprom-lib/eeprom.h"


void TMR0_Callback(void)
{
    IO_RC7_Toggle();
}

// fatal error types
typedef enum {
    ERR_OK = 0,
    ERR_EEPROM_WRITE = 1,
    ERR_EEPROM_READ = 2,
    ERR_EEPROM_VERIFY_FAILED = 3,
} t_error;

// for debugger
t_error gErrorCode = ERR_OK;

void my_fatal_error(t_error err){
    gErrorCode = err;
    IO_RB7_SetLow(); // RED LED On
    while(1){
        NOP(); // put breakpoint here to catch fatal errors
    }
}

/*
    Main application
*/

int main(void)
{
    uint32_t WR_ADDRESS = 0;
    uint8_t  WR_DATA = 0x12, TEMP_DATA=0;
    uint32_t addr;
    bool res;
    
    SYSTEM_Initialize();
    IO_RB7_SetHigh();
    IO_RC7_SetHigh();
    
    
    TMR0_OverflowCallbackRegister(TMR0_Callback);

    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable();

    __delay_ms(1000);
#if 0    
    res = EEPROM_ByteWrite(WR_ADDRESS,&WR_DATA);
    NOP();
    if (!res){
        my_fatal_error(ERR_EEPROM_WRITE);
    }
#endif

    res = EEPROM_ByteRead(WR_ADDRESS,&TEMP_DATA);
    NOP();
    if (!res){
        my_fatal_error(ERR_EEPROM_READ);
    }
#if 0        
    if (TEMP_DATA != WR_DATA){
        my_fatal_error(ERR_EEPROM_VERIFY_FAILED);        
    }
#endif
    
    while(1)
    {
        for(addr=0;addr<EEPROM_I2C_SIZE;addr++)
        {
            res = EEPROM_ByteRead(addr,&TEMP_DATA);
            NOP();
            if (!res){
                my_fatal_error(ERR_EEPROM_READ);
            }            
            __delay_ms(500);
            IO_RB7_Toggle();            
        }
    }    
}