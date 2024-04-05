/* 
 * File:   7_segment.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 10, 2023, 6:46 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/******************* Section : Includes *******************/
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/******************* Section : Macro Declarations *******************/
#define segment_pin0 0
#define segment_pin1 1
#define segment_pin2 2
#define segment_pin3 3

/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,        
}segment_type_t;

typedef struct{
pin_config_t SegmentPins[4];
segment_type_t Segment_type;
}segment_t;

/******************* Section : Functions Declarations *******************/
STD_ReturnType ecu_seven_segment_initialize(const segment_t *seg);
STD_ReturnType ecu_seven_segment_write_number(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

