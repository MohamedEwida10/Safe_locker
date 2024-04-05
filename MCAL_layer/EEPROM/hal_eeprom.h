/* 
 * File:   hal_eeprom.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 23, 2024, 12:05 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/******************* Section : Includes *******************/
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"

/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/

/******************* Section : Functions Declarations *******************/
STD_ReturnType Data_EEPROM_WriteByte(uint16 badd,uint8 bData);
STD_ReturnType Data_EEPROM_ReadByte(uint16 badd,uint8 *bData);

#endif	/* HAL_EEPROM_H */

