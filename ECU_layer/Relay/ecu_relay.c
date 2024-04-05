/* 
 * File:   ecu_relay.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 2, 2023, 6:47 AM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be output and turn the relay off or on
 * @param relay pointer to relay module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_relay_initialize(const relay_t *relay){
 STD_ReturnType ret = E_OK;
    if(NULL == relay )
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t relay_pin ={.port = relay->relay_port, .pin = relay->relay_pin,
                             .direction = DICRECTION_OUTOUT, .logic = relay->relay_status};
       gpio_pin_initialize(&relay_pin);
    }
    
     return ret;    
}

/**
 * @brief turn the relay on
 * @param relay pointer to relay module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_relay_on(const relay_t *relay){
STD_ReturnType ret = E_OK;
    if(NULL == relay )
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t relay_pin ={.port = relay->relay_port, .pin = relay->relay_pin,
                             .direction = DICRECTION_OUTOUT, .logic = relay->relay_status};
       gpio_pin_write_logic(&relay_pin , HIGH);
    }
    
     return ret;        
}

/**
 * @brief turn the relay off
 * @param relay pointer to relay module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_relay_off(const relay_t *relay){
STD_ReturnType ret = E_OK;
    if(NULL == relay )
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t relay_pin ={.port = relay->relay_port, .pin = relay->relay_pin,
                             .direction = DICRECTION_OUTOUT, .logic = relay->relay_status};
       gpio_pin_write_logic(&relay_pin , LOW);
    }
    
     return ret;        
}


