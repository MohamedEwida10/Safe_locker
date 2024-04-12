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
/******************* Section : MacroData Type Declarations *******************/
    typedef struct{
        uint8 pass_arr_num_digits;
        uint8 password[8];
    }pass_t;
/******************* Section : Macro Declarations *******************/
    uint8 keypad_value  = 0;
    uint8 pass_check = 0;
    uint8 selected_mode = 0;
    uint8 user_statue = 0 ;
    
    pass_t pass_obj= {
    .pass_arr_num_digits = 0,
    .password[0] = '\0',
    .password[1] = '\0',   
    .password[2] = '\0',   
    .password[3] = '\0',
    .password[4] = '\0',
    .password[5] = '\0',   
    .password[6] = '\0',   
    .password[7] = '\0',   
    };
    
    pass_t confirm_pass_obj= {
    .pass_arr_num_digits = 0,
    .password[0] = '\0',
    .password[1] = '\0',   
    .password[2] = '\0',   
    .password[3] = '\0',
    .password[4] = '\0',
    .password[5] = '\0',   
    .password[6] = '\0',   
    .password[7] = '\0',   
    };
    
    pass_t enterd_pass_obj= {
    .pass_arr_num_digits = 0,
    .password[0] = '\0',
    .password[1] = '\0',   
    .password[2] = '\0',   
    .password[3] = '\0',
    .password[4] = '\0',
    .password[5] = '\0',   
    .password[6] = '\0',   
    .password[7] = '\0',   
    };
    
    pass_t stored_pass_obj= {
    .pass_arr_num_digits = 0,
    .password[0] = '\0',
    .password[1] = '\0',   
    .password[2] = '\0',   
    .password[3] = '\0',
    .password[4] = '\0',
    .password[5] = '\0',   
    .password[6] = '\0',   
    .password[7] = '\0',   
    };
        

    extern chr_lcd_4bit_t lcd1;
    extern keypad_t keypad;
/******************* Section : Macro Functions Declarations *******************/

/******************* Section : Functions Declarations *******************/   
void welcome_msg(void);

/**
 * @brief get the password from the user for the first time 
 * @param pass_obj : pointer to the password struct 
 */
void get_password(pass_t *pass_obj);

/**
 * @brief cofirm the password from the user to be saved
 * @param pass_obj : pointer to the password struct 
 * @param confirm_pass_obj : pointer to the confirmed password struct 
 */
void password_confirmation(pass_t *pass_obj,pass_t *confirm_pass_obj);

/**
 * @brief entering the password before check if it correct or not
 * @param enterd_pass_obj : pointer to the entered password struct 
 * @param stored_pass_obj : pointer to the stored password struct 
 * @param user_statue : pointer indicates if the entered password is true or not   
 */
void entering_password(pass_t *enterd_pass_obj,pass_t *stored_pass_obj,uint8 *user_statue);

/**
 * 
 * @param pass_obj : pointer to the old password struct 
 * @param stored_pass_obj : pointer to the stored password struct
 * @param enterd_pass_obj : pointer to the new password struct 
 * @param confirm_pass_obj : pointer to the confirmed new password struct
 */
void change_password(pass_t *pass_obj,pass_t *stored_pass_obj,
                     pass_t *enterd_pass_obj,pass_t *confirm_pass_obj);

#endif	/* HELPER_FN_H */

