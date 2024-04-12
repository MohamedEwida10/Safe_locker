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
        welcome_msg();
        Data_EEPROM_ReadByte(0x03f8,&pass_check); // check if there is a password has saved in the EEPROM
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
                    lcd_4bit_send_string_pos(&lcd1,4,1,"Unavailable process "); // error message
                    __delay_ms(500);
                    lcd_4bit_send_string_pos(&lcd1,4,1,"                     ");
                    __delay_ms(500);
                }
            }
            
            get_password(&pass_obj); // get the password from user

            password_confirmation(&pass_obj,&confirm_pass_obj); // confirm the password 
            
   
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
            entering_password(&enterd_pass_obj,&stored_pass_obj,&user_statue); // the user enter the password and check if it is true or not
            if(user_statue == 1){ //in case of the password is true
                ecu_led_turn_on(&green_led);
                __delay_ms(1000);
                ecu_led_turn_off(&green_led);
                ecu_dc_motor_move_left(&motor1);
                __delay_ms(3000);
                ecu_dc_motor_stop(&motor1);

            }
            else{ //in case of the password is false
                gpio_pin_write_logic(&buzzer,HIGH);
                ecu_led_turn_on(&red_led);
                __delay_ms(3000);
                gpio_pin_write_logic(&buzzer,LOW);
                ecu_led_turn_off(&red_led);
                
               
                
            }
            
            
        }
        else{
            change_password(&enterd_pass_obj,&stored_pass_obj,&pass_obj,&confirm_pass_obj); // to change the password            
        }

   }

    
    return (EXIT_SUCCESS);
}
void Application_Initialization(void){

ecu_layer_Initialization();
}

