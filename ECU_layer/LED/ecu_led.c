/* 
 * File:   ecu_led.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 21, 2023, 9:43 PM
 */

#include "ecu_led.h"
/**
 * @brief Initialize the assigned pin to be output and turn a led off or on
 * @param led : pointer to led module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_led_initialize(const led_t *led){
  STD_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin = {.port =led->port_name , .pin = led->pin ,
                                .direction = DICRECTION_OUTOUT , .logic = led->led_status};
        gpio_pin_initialize(&led_pin);
        
    }
    
     return ret;   
}

/**
 * @brief turn a specific led on
 * @param led : pointer to led module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_led_turn_on(const led_t *led){
 STD_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin = {.port =led->port_name , .pin = led->pin ,
                                .direction = DICRECTION_OUTOUT , .logic = led->led_status};
        gpio_pin_write_logic(&led_pin,HIGH);
        
        
    }
    
     return ret;      
}
/**
 * @brief turn a specific led off
 * @param led : pointer to led module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_led_turn_off(const led_t *led){
  STD_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin = {.port =led->port_name , .pin = led->pin ,
                                .direction = DICRECTION_OUTOUT , .logic = led->led_status};
        gpio_pin_write_logic(&led_pin,LOW);
        
    }
    
     return ret;     
}

/**
 * @brief toggle a led
 * @param led : pointer to led module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_led_turn_toggle(const led_t *led){
  STD_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t led_pin = {.port =led->port_name , .pin = led->pin ,
                                .direction = DICRECTION_OUTOUT , .logic = led->led_status};
        gpio_pin_toggle_logic(&led_pin);
        
    }
    
     return ret;     
}