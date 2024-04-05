/* 
 * File:   helper_fn.c
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on March 8, 2024, 2:59 PM
 */


#include"helper_fn.h"

static void save_password(uint8 *pass);
static void comparing_password(uint8 *pass,uint8 *pass_digits,uint8 *pass_confirm,uint8 *pass_confirm_digits,uint8 *result);
static void check_entered_password(uint8 *entered_pass,uint8 *entered_pass_digits,uint8 *stored_pass,uint8 *stored_pass_digits,uint8 *result);

void welcome_msg(void){
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    lcd_4bit_send_string_pos(&lcd1,2,7,"welcome");
    __delay_ms(1000);
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
}

void initialize_var(void){
    keypad_value  = 0;
    
}

void get_password(uint8 *pass,uint8 *pass_didits){
   keypad_value  = 0;
   uint8 counter = 0;
   uint8 lcd_counter = 2;   

    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    
    while(1){
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"The password ");
        lcd_4bit_send_string_pos(&lcd1,3,1,":");
        
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(125);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && pass[0] == '\0'){
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(500);  
        }
        else if(keypad_value == '#' && counter != -1){
                counter--;
                pass[counter] = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500); 
                }
                else{
                    *pass_didits = counter;
                   lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                    __delay_ms(20);            
                    return; 
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                     __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);     
                }
        else{
            if(counter < 8){
                        pass[counter] = keypad_value;
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(500); 
            }
                    
        }
            
    }
    
}

void password_confirmation(uint8 *pass,uint8 *pass_didits,uint8 *pass_confirm,uint8 *pass_confirm_didits){
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
        __delay_ms(125);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && pass_confirm[0] == '\0'){
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(500);  
        }
        else if(keypad_value == '#' && counter != -1){
                counter--;
                pass_confirm[counter] = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500); 
                }
                else{
                     *pass_confirm_didits = counter;
                   comparing_password(pass,pass_didits,pass_confirm,pass_confirm_didits,&comparing_result);
                    if(comparing_result == 1){
                        save_password(pass);
                        lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                        __delay_ms(20);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"password saved");
                        __delay_ms(500);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                        __delay_ms(500);
                        break;
                    }else{
                         lcd_4bit_send_string_pos(&lcd1,4,1,"wrong password ");
                         __delay_ms(500);
                        lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                        __delay_ms(500);
                    }
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                     __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);     
                }
        else{
            if(counter < 8){
                        pass_confirm[counter] = keypad_value;
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(500); 
            }
                    
        }
            
    }
    
  
}

void entering_password(uint8 *pass_entered,uint8 *pass_entered_didits,uint8 *stored_password,
                       uint8 *stored_password_digits,uint8 *user_statue){
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
        __delay_ms(125);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && pass_entered[0] == '\0'){
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(500);  
        }
        else if(keypad_value == '#' && counter != -1){
                counter--;
                pass_entered[counter] = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500); 
                }
                else{
                     *pass_entered_didits = counter;
                   check_entered_password(pass_entered,pass_entered_didits,stored_password,stored_password_digits,&comparing_result);
                    if(comparing_result == 1){
                        
                        lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                        __delay_ms(20);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"password correct");
                        __delay_ms(500);
                        lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                        __delay_ms(500);
                        
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
                            wrong_counter++;
                            lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
                            __delay_ms(40);
                            lcd_4bit_send_string_pos(&lcd1,2,4,"wrong password ");
                            convert_byte_to_string(wrong_counter,str);
                            lcd_4bit_send_string_pos(&lcd1,4,1,str);
                            lcd_4bit_send_string_pos(&lcd1,4,2,"/3");
                            __delay_ms(500);
                            lcd_4bit_send_string_pos(&lcd1,2,4,"                     ");
                            lcd_4bit_send_string_pos(&lcd1,4,1,"   ");
                            __delay_ms(500);
                            
                            lcd_4bit_send_command(&lcd1,_LCD_CURSER_OFF_DEPLAY_OFF);
                            __delay_ms(300);
 
                          while(counter){
                              counter--;
                              pass_entered[counter] = '\0';
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
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                     __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);     
                }
        else{
            if(counter < 8){
                        pass_entered[counter] = keypad_value;
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(500); 
            }          
        }      
    }
}

void change_password(uint8 *old_pass,uint8 *old_pass_didits,uint8 *stored_password,
                       uint8 *stored_password_digits,uint8 *new_pass,uint8 *new_pass_Digits,
                            uint8 *new_pass_confirm,uint8 *new_pass_confirm_Digits){
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
        __delay_ms(125);
        }while(keypad_value == 0 );
        
        if(keypad_value == '#' && old_pass[0] == '\0'){
            lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                __delay_ms(500);  
        }
        else if(keypad_value == '#' && counter != -1){
                counter--;
                old_pass[counter] = '\0';
                lcd_counter--;
                lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,' ');               
            }
        else if(keypad_value == '='){
                if(counter <= 3){
                     lcd_4bit_send_string_pos(&lcd1,4,1,"min 4 digits ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500); 
                }
                else{
                     *old_pass_didits = counter;
                   check_entered_password(old_pass,old_pass_didits,stored_password,stored_password_digits,&comparing_result);
                    if(comparing_result == 1){
                        get_password(new_pass,new_pass_Digits);
                        password_confirmation(new_pass,new_pass_Digits,new_pass_confirm,new_pass_confirm_Digits);
                        break;
                    }else{
                         lcd_4bit_send_string_pos(&lcd1,4,1,"wrong password ");
                         __delay_ms(500);
                        lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                        __delay_ms(500);
                    }
                }
        }           
        else if(keypad_value == '/' || keypad_value == '*' || keypad_value == '+' || keypad_value == '-'){
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                     __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);     
                }
        else{
            if(counter < 8){
                        old_pass[counter] = keypad_value;
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,keypad_value);
                        __delay_ms(200);
                        lcd_4bit_send_char_data_pos(&lcd1,3,lcd_counter,'*');
                        counter++;
                        lcd_counter++;
            }
            else{
                lcd_4bit_send_string_pos(&lcd1,4,1,"max 8 digits ");
                 __delay_ms(500);
                lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                 __delay_ms(500); 
            }
                    
        }
            
    }
       
}

static void save_password(uint8 *pass){
    uint8 counter = 0;
    counter = 0;
    while(pass[counter]){
        Data_EEPROM_WriteByte(0x03f8 + counter,pass[counter]);
        counter++;
    }
}

static void comparing_password(uint8 *pass,uint8 *pass_digits,uint8 *pass_confirm,uint8 *pass_confirm_digits,uint8 *result){
uint8 comparing_counter = 0;
*result = 1;
    if(*pass_digits == *pass_confirm_digits){
        while((*pass_digits)--){
            if(pass[comparing_counter] == pass_confirm[comparing_counter]){
                comparing_counter++;
            }
            else{
                *result = 0;
                break;
            }
        } 
    }
    else{
        *result = 0;
    }
   
}

static void check_entered_password(uint8 *entered_pass,uint8 *entered_pass_digits,uint8 *stored_pass,uint8 *stored_pass_digits,uint8 *result){
uint8 comparing_counter = 0;
uint8 helper_counter = 0;

*result = 1;

while(1){
    Data_EEPROM_ReadByte((0x03f8 + helper_counter),&stored_pass[helper_counter]);
    if(0xFF == stored_pass[helper_counter]){
        stored_pass[helper_counter] = '\0';
        break;
    }else{/* nothing */}
    helper_counter++;
}


*stored_pass_digits = helper_counter;

    if(*stored_pass_digits == *entered_pass_digits){
        while((*stored_pass_digits)--){
            if(stored_pass[comparing_counter] == entered_pass[comparing_counter]){
                comparing_counter++;
            }
            else{
                *result = 0;
                break;
            }
        } 
    }
    else{
        *result = 0;
    }


}