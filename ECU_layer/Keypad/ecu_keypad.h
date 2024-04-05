/* 
 * File:   ecu_keypad.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 5:41 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/******************* Section : Includes *******************/
#include "ecu_ketpad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/******************* Section : Macro Declarations *******************/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4
/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
typedef struct{
    pin_config_t keypad_rows_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType ecu_keypad_initialize(const keypad_t *keypad);
STD_ReturnType ecu_keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

