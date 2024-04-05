/* 
 * File:   application.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 21, 2023, 9:11 PM
 */

#include "application.h"



int main() { 
    STD_ReturnType ret = E_NOT_OK;
    Application_Initialization();

    while(1){
        initialize_var();
        welcome_msg();
        Data_EEPROM_ReadByte(0x03f8,&pass_check);
        if(pass_check == 0xff){
            lcd_4bit_send_string_pos(&lcd1,2,1,"1-Set new password.");
                      
            while(1){
                do{
                ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
                __delay_ms(100);
                }while(keypad_value == 0 );
                
                if(keypad_value == '1'){
                    __delay_ms(100);
                    break;
                }
                else{
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);
                }
            }
            
            get_password(password,&pass_num_digits);

            password_confirmation(password,&pass_num_digits,password_confirm,&pass_confirm_num_digits);
            
   
        }
        else{ /* nothing */ }
        
        
        lcd_4bit_send_string_pos(&lcd1,2,1,"1-Enter password.");
        lcd_4bit_send_string_pos(&lcd1,3,1,"2-Change password.");
        
        
         while(1){
                do{
                ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
                __delay_ms(100);
                }while(keypad_value == 0 );
                
                if(keypad_value == '1'){
                    selected_mode = 1 ;
                    __delay_ms(100);
                    break;
                }
                else if(keypad_value == '2'){
                    selected_mode = 2 ;
                    __delay_ms(100);
                    break;
                }
                else{
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process ");
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);
                }
        }
        
        if(selected_mode == 1){
            entering_password(entered_password,&enterd_pass_num_digits,stored_password,&stored_pass_num_digits,&user_statue);
            if(user_statue == 1){
                ecu_led_turn_on(&green_led);
                __delay_ms(1000);
                ecu_led_turn_off(&green_led);
                ecu_dc_motor_move_left(&motor1);
                __delay_ms(3000);
                ecu_dc_motor_stop(&motor1);

            }
            else{
                gpio_pin_write_logic(&buzzer,HIGH);
                ecu_led_turn_on(&red_led);
                __delay_ms(3000);
                gpio_pin_write_logic(&buzzer,LOW);
                ecu_led_turn_off(&red_led);
                
               
                
            }
            
            
        }
        else{
            change_password(entered_password,enterd_pass_num_digits,stored_password,stored_pass_num_digits,      
                            password,pass_num_digits,password_confirm,pass_confirm_num_digits);
                            
            
        }
       
        
        
        

   }

    
    return (EXIT_SUCCESS);
}
void Application_Initialization(void){

ecu_layer_Initialization();
}

