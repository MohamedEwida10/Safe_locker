/* 
 * File:   hal_eeprom.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 23, 2024, 12:05 AM
 */

#include "hal_eeprom.h"

STD_ReturnType Data_EEPROM_WriteByte(uint16 badd,uint8 bData){
STD_ReturnType ret = E_OK;

    /* read the interrupt status */
    uint8 GLOBAL_INTERRUPT_STATUS = INTCONbits.GIE;
    /* update the address register */
    EEADRH = (uint8)((badd >> 8) & 0x03) ;
    EEADR =  (uint8)(badd & 0xFF) ;
    /* update the data register */
    EEDATA = bData;
    /* select access data EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    /* allows write cycle to flash program/data EEPROM */
    EECON1bits.WREN = 1;
    /* disable all interrupts "global interrupts"  */
    INTERRUPT_GlobalIterruptDisable();
    /* write the required sequence "0x55 -> 0xAA " */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* initiates a data EEPROM erase/write circuit */
    EECON1bits.WR = 1;
    /* wait for the write complete */
    while(EECON1bits.WR){
    /* nothing */    
    }
    /* inhibits write cycle to flash program/flash EEPROM */
    EECON1bits.WREN = 0;
    /* restore the interrupt status */
    INTCONbits.GIE = GLOBAL_INTERRUPT_STATUS;
    
    return ret;      
    
}

STD_ReturnType Data_EEPROM_ReadByte(uint16 badd,uint8 *bData){
STD_ReturnType ret = E_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* update the address register */
        EEADRH = (uint8)((badd >> 8) & 0x03) ;
        EEADR =  (uint8)(badd & 0xFF) ;
        /* select access data EEPROM memory */
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        /* initiates a data EEPROM read */
         EECON1bits.RD = 1;
         NOP();
         NOP();
        /* get data  */
         *bData = EEDATA;
    }
    
     return ret;      
    
}