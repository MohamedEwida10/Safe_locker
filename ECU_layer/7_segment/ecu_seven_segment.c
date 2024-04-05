/* 
 * File:   7_segment.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 10, 2023, 6:46 AM
 */

#include "ecu_seven_segment.h"
/**
 * @brief initialize 4pins of the seven_segment as output and write high or low
 * @param seg pointer to seven_segment configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_seven_segment_initialize(const segment_t *seg){
  STD_ReturnType ret = E_OK;
    if(NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_initialize(&(seg->SegmentPins[segment_pin0]));
        gpio_pin_initialize(&(seg->SegmentPins[segment_pin1]));
        gpio_pin_initialize(&(seg->SegmentPins[segment_pin2]));
        gpio_pin_initialize(&(seg->SegmentPins[segment_pin3]));
    }
    
     return ret;       
}
/**
 * @brief write a number on seven_segment 
 * @param seg pointer to seven_segment configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ecu_seven_segment_write_number(const segment_t *seg, uint8 number){
   STD_ReturnType ret = E_OK;
    if(NULL == seg || number > 9)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(seg->SegmentPins[segment_pin0]) , number & 0x01 );
        gpio_pin_write_logic(&(seg->SegmentPins[segment_pin1]) , (number >> 1)& 0x01 );
        gpio_pin_write_logic(&(seg->SegmentPins[segment_pin2]) , (number >> 2)& 0x01 );
        gpio_pin_write_logic(&(seg->SegmentPins[segment_pin3]) , (number >> 3)& 0x01 );
        
    }
    
     return ret;          
}


