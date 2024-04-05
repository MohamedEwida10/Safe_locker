/* 
 * File:   ecu_layer_init.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 9:11 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H



/******************* Section : Includes *******************/
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_motor/ecu_DC_motor.h"
#include "7_segment/ecu_seven_segment.h"
#include "Keypad/ecu_keypad.h"
#include "chr_LCD/ecu_chr_LCD.h"
#include "../MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "../MCAL_layer/EEPROM/hal_eeprom.h"
/******************* Section : Macro Declarations *******************/
extern led_t green_led;
extern led_t red_led;
extern dc_motor_t motor1;
extern pin_config_t buzzer;
extern button_t btn1;
extern Interrupt_INTx_t INT_obj ;
extern chr_lcd_4bit_t lcd1;
/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/


/******************* Section : Functions Declarations *******************/
void ecu_layer_Initialization(void);


#endif	/* ECU_LAYER_INIT_H */

