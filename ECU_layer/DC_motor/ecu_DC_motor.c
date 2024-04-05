/* 
 * File:   ecu_DC_motor.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 3, 2023, 6:49 AM
 */

#include "ecu_DC_motor.h"



 /**
  * @brief initialize two pins of the motor to be output and write a logic high or low on them
  * @param dc_motor pointer to dc_motor module configuration
  * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed
  */
STD_ReturnType ecu_dc_motor_initialize(const dc_motor_t *dc_motor){
STD_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
       
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[0]));
        gpio_pin_initialize(&(dc_motor->dc_motor_pin[1]));    
    }
     return ret;       
}

/**
 * @brief move the motor right
 * @param dc_motor pointer to dc_motor module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_dc_motor_move_right(const dc_motor_t *dc_motor){
STD_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),LOW);
        
    }
    
     return ret;        
}

/**
 * @brief move the motor left
 * @param dc_motor pointer to dc_motor module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_dc_motor_move_left(const dc_motor_t *dc_motor){
STD_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),HIGH);
        
    }
    
     return ret;        
}

/**
 * @brief stop the motor off
 * @param dc_motor pointer to dc_motor module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_dc_motor_stop(const dc_motor_t *dc_motor){
STD_ReturnType ret = E_OK;
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]),LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]),LOW);
        
    }
    
     return ret;        
}


