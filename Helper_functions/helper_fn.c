/* 
 * File:   helper_fn.c
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on March 8, 2024, 2:59 PM
 */


#include"helper_fn.h"

/**
 * @brief : save the user password in the EEPROM
 * @param pass_obj : pointer to the password struct 
 */
static void save_password(pass_t *pass_obj);
/**
 * @brief : compare the password and the confirmed password
 * @param pass_obj : pointer to the password struct 
 * @param confirm_pass_obj : pointer to the confirmed password struct 
 * @param result : pointer to the comparing result
 */
static void comparing_password(pass_t *pass_obj,pass_t *confirm_pass_obj,uint8 *result);
/**
 * @brief : compare the entered password and the stored password
 * @param enterd_pass_obj : pointer to the entered password struct 
 * @param stored_pass_obj : pointer to the stored password struct 
 * @param result : pointer to the comparing result
 */
static void check_entered_password(pass_t *enterd_pass_obj,pass_t *stored_pass_obj,uint8 *result);

/***********************************************************************************************************/

/**
 * @brief : welcome message
 */
void welcome_msg(void){
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    lcd_4bit_send_string_pos(&lcd1,2,7,"welcome");
    __delay_ms(1000);
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
}

/**
 * @brief get the password from the user for the first time 
 * @param pass_obj : pointer to the password struct 
 */
void get_password(pass_t *pass_obj){
   keypad_value  = 0; // variable stored the keypad value
   uint8 counter = 0; // variable indicate the current position in the password array
   uint8 lcd_counter = 2; // variable indicate the current position on the screen

    lcd_4bit_send_command(&lcd1,_LCD_CLEAR); //clear screen
    __delay_ms(20);
    
    while(1){
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"The password ");
        lcd_4bit_send_string_pos(&lcd1,3,1,":");
        
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(110);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && (pass_obj->password[0]) == '\0'){ // error message
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(300);  
        }
        else if(keypad_value == '#' && counter > 0){ // to delete one number
                counter--;
                (pass_obj->password[counter])= '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits "); // error message
                    __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300); 
                }
                else{
                   (pass_obj->pass_arr_num_digits) = counter; 
                   lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                    __delay_ms(20);            
                    return; // return from the function 
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process "); // error message
                     __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300);     
                }
        else{
            if(counter < 8){
                        (pass_obj->password[counter]) = keypad_value; // store the number in the password array
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits "); // error message
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(300); 
                 
            }
                    
        }
            
    }
    
}

/**
 * @brief cofirm the password from the user to be saved
 * @param pass_obj : pointer to the password struct 
 * @param confirm_pass_obj : pointer to the confirmed password struct 
 */
void password_confirmation(pass_t *pass_obj,pass_t *confirm_pass_obj){
   keypad_value  = 0;
   uint8 counter = 0;
   uint8 comparing_result = 1;
   uint8 lcd_counter = 2;   

    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    
    while(1){
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"confirm The password ");
        lcd_4bit_send_string_pos(&lcd1,3,1,":");
        
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(110);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && (confirm_pass_obj->password[0]) == '\0'){ //error message
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(300);  
        }
        else if(keypad_value == '#' && counter > 0){ //delete one number
                counter--;
                (confirm_pass_obj->password[counter]) = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits "); //error message
                    __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300); 
                }
                else{
                     (confirm_pass_obj->pass_arr_num_digits) = counter;
                   comparing_password(pass_obj,confirm_pass_obj,&comparing_result); //comparing step
                    if(comparing_result == 1){
                        save_password(pass_obj); //saving step
                        lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                        __delay_ms(20);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"password saved");
                        __delay_ms(300);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                        __delay_ms(300);
                        break;
                    }else{
                         lcd_4bit_send_string_pos(&lcd1,4,1,"wrong password "); //error message
                         __delay_ms(300);
                        lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                        __delay_ms(300);
                    }
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process "); //error message
                     __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300);     
                }
        else{
            if(counter < 8){
                        (confirm_pass_obj->password[counter]) = keypad_value; // store the number in the password array
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits "); //error message
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(300);
                 
            }
                    
        }
            
    }
    
  
}

/**
 * @brief entering the password before check if it correct or not
 * @param enterd_pass_obj : pointer to the entered password struct 
 * @param stored_pass_obj : pointer to the stored password struct 
 * @param user_statue : pointer indicates if the entered password is true or not   
 */
void entering_password(pass_t *enterd_pass_obj,pass_t *stored_pass_obj,uint8 *user_statue){
   keypad_value  = 0;
   uint8 counter = 0;
   uint8 comparing_result = 1;
   uint8 lcd_counter = 2;   
   uint8 wrong_counter = 0;
   uint8 str[4];
   
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    
    while(1){
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"enter your password ");
        lcd_4bit_send_string_pos(&lcd1,3,1,":");
        
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(110);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && (enterd_pass_obj->password[0]) == '\0'){ //error message 
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(300);  
        }
        else if(keypad_value == '#' && counter > 0){ //delete one number
                counter--;
                (enterd_pass_obj->password[counter]) = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){ //error message
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits "); 
                    __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300); 
                }
                else{
                    enterd_pass_obj->pass_arr_num_digits = counter;
                    check_entered_password(enterd_pass_obj,stored_pass_obj,&comparing_result); //checking step
                    if(comparing_result == 1){ //in case of the password is true
                        
                        lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                        __delay_ms(20);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"password correct"); //correct message
                        __delay_ms(300);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                        __delay_ms(300);
                        
                        *user_statue = 1 ;
                        
                        break;
                    }else{
                        if(wrong_counter == 2){
                            *user_statue = 0 ;
                            lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                            __delay_ms(40);
                            break;
                        }
                        else{
                            wrong_counter++; //in case of the password is false
                            lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                            __delay_ms(40);
                            lcd_4bit_send_string_pos(&lcd1,2,4,"wrong password "); //error message
                            convert_byte_to_string(wrong_counter,str);
                            lcd_4bit_send_string_pos(&lcd1,4,1,str);
                            lcd_4bit_send_string_pos(&lcd1,4,2,"/3");
                            __delay_ms(300);
                            lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                            lcd_4bit_send_string_pos(&lcd1,4,1,"   ");
                            __delay_ms(300);
                            
                            lcd_4bit_send_command(&lcd1,_LCD_CURSER_OFF_DEPLAY_OFF);
                            __delay_ms(300);
 
                          while(counter){
                              counter--;
                              (enterd_pass_obj->password[counter]) = '\0';
                              lcd_counter--;
                              lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');
                          }

                          lcd_4bit_send_command(&lcd1,_LCD_CURSER_OFF_DEPLAY_ON);
                          __delay_ms(20);  
                        }
                        
                    }
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process "); //error message
                     __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300);     
                }
        else{
            if(counter < 8){
                        (enterd_pass_obj->password[counter]) = keypad_value; // store the number in the password array
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits "); //error message
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(300); 
                
            }          
        }      
    }
}

/**
 * 
 * @param pass_obj : pointer to the old password struct 
 * @param stored_pass_obj : pointer to the stored password struct
 * @param enterd_pass_obj : pointer to the new password struct 
 * @param confirm_pass_obj : pointer to the confirmed new password struct
 */
void change_password(pass_t *pass_obj,pass_t *stored_pass_obj,
                     pass_t *enterd_pass_obj,pass_t *confirm_pass_obj){
   keypad_value  = 0;
   uint8 counter = 0;
   uint8 comparing_result = 1;
   uint8 lcd_counter = 2;   

    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    
    while(1){
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"the old password");
        lcd_4bit_send_string_pos(&lcd1,3,1,":");
        
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(110);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && pass_obj->password[0] == '\0'){
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");  //error message
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(300);  
        }
        else if(keypad_value == '#' && counter > 0){ //delete one number
                counter--;
                pass_obj->password[counter] = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits ");  //error message
                    __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300); 
                }
                else{
                     pass_obj->pass_arr_num_digits = counter;
                   check_entered_password(pass_obj,stored_pass_obj,&comparing_result); //checking step
                    if(comparing_result == 1){ // in case of the old password is true
                        get_password(enterd_pass_obj);
                        password_confirmation(enterd_pass_obj,confirm_pass_obj);
                        break;
                    }else{
                         lcd_4bit_send_string_pos(&lcd1,4,1,"wrong password ");  //error message
                         __delay_ms(300);
                        lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                        __delay_ms(300);
                    }
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");  //error message
                     __delay_ms(300);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(300);     
                }
        else{
            if(counter < 8){
                        pass_obj->password[counter] = keypad_value; // store the number in the password array
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits ");  //error message
                 __delay_ms(300);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(300); 
            }
                    
        }
            
    }
       
}
/********************************************************************************************************/

/**
 * @brief : save the user password in the EEPROM
 * @param pass_obj : pointer to the password struct 
 */
static void save_password(pass_t *pass_obj){
    uint8 counter = 0; // counter for looping
    while(pass_obj->password[counter]){
        Data_EEPROM_WriteByte(0x03f8 + counter,(pass_obj->password[counter])); // saving step
        counter++;
    }
}

/**
 * @brief : compare the password and the confirmed password
 * @param pass_obj : pointer to the password struct 
 * @param confirm_pass_obj : pointer to the confirmed password struct 
 * @param result : pointer to the comparing result
 */
static void comparing_password(pass_t *pass_obj,pass_t *confirm_pass_obj,uint8 *result){
uint8 comparing_counter = 0; // counter to loop on the password array
uint8 looping_counter = (pass_obj->pass_arr_num_digits); // counter for looping process

*result = 1; // the function return . if the result still 1 ----> the comparing process successes

    if(pass_obj->pass_arr_num_digits == confirm_pass_obj->pass_arr_num_digits){
        while(looping_counter--){
            if(pass_obj->password[comparing_counter] == confirm_pass_obj->password[comparing_counter]){
                comparing_counter++;
            }
            else{
                *result = 0; // one number is wrong
                break; 
            }
        } 
    }
    else{
        *result = 0; // the password is totally wrong
    }
   
}

/**
 * @brief : compare the entered password and the stored password
 * @param enterd_pass_obj : pointer to the entered password struct 
 * @param stored_pass_obj : pointer to the stored password struct 
 * @param result : pointer to the comparing result
 */
static void check_entered_password(pass_t *enterd_pass_obj,pass_t *stored_pass_obj,uint8 *result){
uint8 comparing_counter = 0;
uint8 helper_counter = 0;

*result = 1;

while(1){ // restore the saved password step
    Data_EEPROM_ReadByte((0x03f8 + helper_counter),&(stored_pass_obj->password[helper_counter]));
    if(0xFF == stored_pass_obj->password[helper_counter]){
        stored_pass_obj->password[helper_counter] = '\0';
        break;
    }else{/* nothing */}
    helper_counter++;
}


stored_pass_obj->pass_arr_num_digits = helper_counter; 

    //comparing step
    if((stored_pass_obj->pass_arr_num_digits) == enterd_pass_obj->pass_arr_num_digits){ 
        while((stored_pass_obj->pass_arr_num_digits)--){
            if(stored_pass_obj->password[comparing_counter] == enterd_pass_obj->password[comparing_counter]){
                comparing_counter++;
            }
            else{
                *result = 0; // one number is wrong
                break;
            }
        } 
    }
    else{
        *result = 0; // the password is totally wrong
    }


}