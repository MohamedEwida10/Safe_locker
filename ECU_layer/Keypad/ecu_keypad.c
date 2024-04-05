/* 
 * File:   ecu_keypad.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 5:41 PM
 */

#include "ecu_keypad.h"
#define _XTAL_FREQ 8000000ul

uint8 keypad_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] ={
                     {'7','8','9','/'},
                     {'4','5','6','*'},
                     {'1','2','3','-'},
                     {'#','0','=','+'}
};

/**
 * @brief Initialize the assigned 4 pins to be output and 4 pins to be input 
 * @param keypad : pointer to keypad module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_keypad_initialize(const keypad_t *keypad){
STD_ReturnType ret = E_OK;
uint8 rows,columns; 
    if(NULL == keypad)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows = 0;rows < ECU_KEYPAD_ROWS ;rows++)
        {
            gpio_pin_initialize(&(keypad->keypad_rows_pins[rows]));
            
        }
        for(columns = 0;columns < ECU_KEYPAD_COLUMNS ;columns++){
                gpio_pin_direction_initialize(&(keypad->keypad_columns_pins[columns]));
            }
        
    }
    
     return ret;   
}

/**
 * @brief get the value of the pressed button
 * @param keypad : pointer to keypad module configuration
 * @param value : pointer to value that i pressed
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_keypad_get_value(const keypad_t *keypad, uint8 *value){
STD_ReturnType ret = E_OK;
uint8 rows = 0,columns = 0,clear_rows_counter = 0; 
uint8 column_val = 0;
*value = 0;
    if(NULL == keypad || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows = 0;rows < ECU_KEYPAD_ROWS ;rows++)
        {
            for(clear_rows_counter = 0;clear_rows_counter < ECU_KEYPAD_ROWS ;clear_rows_counter++)
            {
                gpio_pin_write_logic(&(keypad->keypad_rows_pins[clear_rows_counter]),LOW);
            }
            gpio_pin_write_logic(&(keypad->keypad_rows_pins[rows]),HIGH);
            __delay_ms(10);
            for(columns = 0;columns < ECU_KEYPAD_COLUMNS ;columns++)
            {
                gpio_pin_read_logic(&(keypad->keypad_columns_pins[columns]),&column_val);
                if(HIGH == column_val)
                {
                *value = keypad_values[rows][columns];
                }
            }

        }
        
    }
    
     return ret;  
}




