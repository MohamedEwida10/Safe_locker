/* 
 * File:   ecu_button.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 30, 2023, 7:03 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/******************* Section : Includes *******************/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"
/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
typedef enum{
    BUTTON_PRESSED = 0 ,
    BUTTON_RELEASED         
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH = 0 ,
    BUTTON_ACTIVE_LOW         
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/******************* Section : Functions Declarations *******************/
STD_ReturnType ecu_button_initialize(const button_t *btn);
STD_ReturnType ecu_button_read_state(const button_t *btn, button_state_t *state);

#endif	/* ECU_BUTTON_H */

