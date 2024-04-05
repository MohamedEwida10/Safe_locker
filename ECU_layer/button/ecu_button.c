/* 
 * File:   ecu_button.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 30, 2023, 7:03 AM
 */

#include "ecu_button.h"

/**
 * @brief initialize the assigned pin to be input
 * @param btn pointer to button configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_button_initialize(const button_t *btn){
   STD_ReturnType ret = E_OK;
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn->button_pin));    
    }
    
     return ret;    
}

/**
 * @brief read the state of the button
 * @param btn pointer to button configuration
 * @param btn_state pointer to button state @ref button_state_t
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_button_read_state(const button_t *btn, button_state_t *btn_state){
    STD_ReturnType ret = E_OK;
    logic_t btn_logic = LOW;
    
    if((NULL == btn) || (NULL == btn_state))
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(btn->button_pin), &btn_logic);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(btn_logic == HIGH)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(btn_logic == HIGH)
            {
               *btn_state = BUTTON_RELEASED; 
            }
            else
            {
                *btn_state = BUTTON_PRESSED;
            }
        }
    }
    
     return ret;     
}
