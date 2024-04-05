/* 
 * File:   helper_fn.h
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on March 8, 2024, 2:59 PM
 */

#ifndef HELPER_FN_H
#define	HELPER_FN_H


/******************* Section : Includes *******************/
#include "../ECU_layer/ecu_layer_init.h"
#include "../MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "../MCAL_layer/EEPROM/hal_eeprom.h"
/******************* Section : Macro Declarations *******************/
    uint8 keypad_value  = 0;
    uint8 pass_check = 0;
    uint8 selected_mode = 0;
    uint8 user_statue = 0 ;
            
    uint8 pass_num_digits = 0 ;
    uint8 pass_confirm_num_digits = 0 ;
    uint8 enterd_pass_num_digits = 0 ;
    uint8 stored_pass_num_digits = 0 ;
    
    uint8 password[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
    uint8 password_confirm[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
    uint8 entered_password[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
    uint8 stored_password[8] = {'\0','\0','\0','\0','\0','\0','\0','\0'};
    
    extern chr_lcd_4bit_t lcd1;
    extern keypad_t keypad;
/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/

/******************* Section : Functions Declarations *******************/
void welcome_msg(void);
void initialize_var(void);
void get_password(uint8 *pass,uint8 *pass_didits);
void password_confirmation(uint8 *pass,uint8 *pass_didits,uint8 *pass_confirm,uint8 *pass_confirm_didits);
void entering_password(uint8 *pass_entered,uint8 *pass_entered_didits,uint8 *stored_password,
                       uint8 *stored_password_digits,uint8 *user_statue);
void change_password(uint8 *old_pass,uint8 *old_pass_didits,uint8 *stored_password,
                     uint8 *stored_password_digits,uint8 *new_pass,uint8 *new_pass_Digits,
                     uint8 *new_pass_confirm,uint8 *new_pass_confirm_Digits);

#endif	/* HELPER_FN_H */

