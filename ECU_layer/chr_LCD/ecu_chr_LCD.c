/* 
 * File:   ecu_chr_LCD.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on January 30, 2024, 1:33 PM
 */

#include "ecu_chr_LCD.h"
/***********************************************************************************************/
static STD_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd,uint8 command_data);
static STD_ReturnType lcd_4bit_send_enable_enable(const chr_lcd_4bit_t *lcd);
static STD_ReturnType lcd_4bit_set_curser(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column );

static STD_ReturnType lcd_8bit_send_enable_enable(const chr_lcd_8bit_t *lcd);
static STD_ReturnType lcd_8bit_set_curser(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column );
/***********************************************************************************************/

/**
 * @brief Initialize the 4Bit LCD
 * @param lcd : pointer to the LCD module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
STD_ReturnType ret = E_OK; 
uint8 counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd->rs));
        ret = gpio_pin_initialize(&(lcd->en));
        for(counter=0 ;counter < 4 ;counter++)
        {
            ret = gpio_pin_initialize(&(lcd->data[counter]));
        }
         __delay_ms(20);
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd,_LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd,_LCD_CURSER_OFF_DEPLAY_ON);
        ret = lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd,_LCD_DDRAM_START);

    }
    
     return ret;   
}
/**
 * @brief send command to the 4Bit LCD
 * @param lcd : pointer to the LCD module configuration
 * @param command that i want to send
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command){
STD_ReturnType ret = E_OK; 

    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        ret = gpio_pin_write_logic(&(lcd->rs),LOW);
        ret = lcd_send_4bit(lcd,command >>4);
        ret = lcd_4bit_send_enable_enable(lcd);
        ret = lcd_send_4bit(lcd,command);
        ret = lcd_4bit_send_enable_enable(lcd);

        
    }
    
     return ret;
};
/**
 * @brief send char to the 4Bit LCD
 * @param lcd : pointer to the LCD module configuration
 * @param the char that i want to send
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data){
STD_ReturnType ret = E_OK; 

    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        ret = gpio_pin_write_logic(&(lcd->rs),HIGH);
        ret = lcd_send_4bit(lcd,data >>4);
        ret = lcd_4bit_send_enable_enable(lcd);
        ret = lcd_send_4bit(lcd,data);
        ret = lcd_4bit_send_enable_enable(lcd);

        
    }
    
     return ret;
}
/**
 * @brief send char to the 4Bit LCD at specific position
 * @param lcd : pointer to the LCD module configuration
 * @param the char that i want to send  
 * @param the row that i want to send the character to
 * @param the column that i want to send the character to
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_curser(lcd,row,column);
        ret = lcd_4bit_send_char_data(lcd,data);
    }
     return ret;
}
/**
 * @brief send string to the 4Bit LCD 
 * @param lcd : pointer to the LCD module configuration
 * @param the string that i want to send  
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    
     return ret;
}
/**
 * @brief send string to the 4Bit LCD at specific position
 * @param lcd : pointer to the LCD module configuration
 * @param the string that i want to send  
 * @param the row that i want to send the string to
 * @param the column that i want to send the string to
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_curser(lcd,row,column);
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    
     return ret;
}
/**
 * @brief send send custome char to the 4Bit LCD 
 * @param lcd : pointer to the LCD module configuration
 * @param the row that i want to send the character to
 * @param the column that i want to send the character to
 * @param _chr the generated custom character 
 * @param mem_pos : the position of the  custom character at cgram
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos){
STD_ReturnType ret = E_OK;
uint8 counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(counter = 0;counter <= 7;counter++){
        ret = lcd_4bit_send_char_data(lcd,_chr[counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    
     return ret;
}
/****************************************************************************************/
/**
 * @brief Initialize the 8Bit LCD
 * @param pointer to the LCD module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
STD_ReturnType ret = E_OK; 
uint8 counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(lcd->rs));
        ret = gpio_pin_initialize(&(lcd->en));
        for(counter=0 ;counter < 8 ;counter++)
        {
            ret = gpio_pin_initialize(&(lcd->data[counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd,_LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd,_LCD_CURSER_OFF_DEPLAY_ON);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd,_LCD_DDRAM_START);

    }
    
     return ret;   
}
/**
 * @brief send command to the 8Bit LCD
 * @param lcd : pointer to the LCD module configuration
 * @param command that i want to send
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command){
STD_ReturnType ret = E_OK;
uint8 counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->rs),LOW);
        for(counter = 0;counter < 8 ; counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->data[counter]),(command >> counter) & 0x01);
        }
        ret = lcd_8bit_send_enable_enable(lcd);
    }
    
     return ret;
}

/**
 * @brief send command to the 8Bit LCD
 * @param lcd : pointer to the LCD module configuration
 * @param the char that i want to send
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data){
STD_ReturnType ret = E_OK;
uint8 counter = 0 ;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->rs),HIGH);
        for(counter = 0;counter < 8 ; counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->data[counter]),(data >> counter) & 0x01);
        }
        ret = lcd_8bit_send_enable_enable(lcd);
    }
    
     return ret;
}
/**
 * @brief send char to the 8Bit LCD at specific position
 * @param lcd : pointer to the LCD module configuration
 * @param the char that i want to send  
 * @param the row that i want to send the character to
 * @param the column that i want to send the character to
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_curser(lcd,row,column);
        ret = lcd_8bit_send_char_data(lcd,data);
    }
     return ret;
}
/**
 * @brief send string to the 8Bit LCD 
 * @param lcd : pointer to the LCD module configuration
 * @param the string that i want to send  
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd,*str++);
        }
    }
    
     return ret;
}
/**
 * @brief send string to the 8Bit LCD at specific position
 * @param lcd : pointer to the LCD module configuration
 * @param the string that i want to send  
 * @param the row that i want to send the string to
 * @param the column that i want to send the string to
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_curser(lcd,row,column);
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd,*str++);
        }
    }
    
     return ret;
}
/**
 * @brief send send custome char to the 4Bit LCD 
 * @param lcd : pointer to the LCD module configuration
 * @param the row that i want to send the character to
 * @param the column that i want to send the character to
 * @param _chr the generated custom character 
 * @param mem_pos : the position of the  custom character at cgram
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos){
STD_ReturnType ret = E_OK;
uint8 counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(counter = 0;counter <= 7;counter++){
        ret = lcd_8bit_send_char_data(lcd,_chr[counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    
     return ret;
}
/******************************************************************************************/
/**
 * @brief convert byte to string to send to the lcd
 * @param value that i want to send
 * @param str : the string that i will send to the lcd
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType convert_byte_to_string(uint8 value,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'/0',4);
        sprintf(str,"%i",value);
    }
     return ret;
}
/**
 * @brief convert byte to string to send to the lcd
 * @param value that i want to send
 * @param str : the string that i will send to the lcd
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType convert_short_to_string(uint16 value,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'/0',6);
        sprintf(str,"%i",value);
    }
     return ret;
}
/**
 * @brief convert byte to string to send to the lcd
 * @param value that i want to send
 * @param str : the string that i will send to the lcd
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType convert_int_to_string(uint32 value,uint8 *str){
STD_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str,'/0',20);
        sprintf(str,"%i",value);
    }
     return ret;
}


/***************************************************************/
/**
 * @brief send 4Bits
 * @param lcd : pointer to the LCD module configuration
 * @param the data that i want to send
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
static STD_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd,uint8 command_data){
STD_ReturnType ret = E_OK;    
ret = gpio_pin_write_logic(&(lcd->data[0]),(command_data >> 0) & 0x01);
ret = gpio_pin_write_logic(&(lcd->data[1]),(command_data >> 1) & 0x01);
ret = gpio_pin_write_logic(&(lcd->data[2]),(command_data >> 2) & 0x01);
ret = gpio_pin_write_logic(&(lcd->data[3]),(command_data >> 3) & 0x01);

return ret;     
}
/**
 * @brief send enable signal
 * @param lcd : pointer to the LCD module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
static STD_ReturnType lcd_4bit_send_enable_enable(const chr_lcd_4bit_t *lcd){
STD_ReturnType ret = E_OK;    
ret = gpio_pin_write_logic(&(lcd->en),HIGH);
__delay_us(5);
ret = gpio_pin_write_logic(&(lcd->en),LOW);

return ret;     
}
/**
 * @brief send enable signal
 * @param lcd : pointer to the LCD module configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
static STD_ReturnType lcd_8bit_send_enable_enable(const chr_lcd_8bit_t *lcd){
STD_ReturnType ret = E_OK;    
ret = gpio_pin_write_logic(&(lcd->en),HIGH);
__delay_us(5);
ret = gpio_pin_write_logic(&(lcd->en),LOW);

return ret;       
}
/**
 * @brief set cursor at specific position at 8bir_lcd
 * @param lcd : pointer to the LCD module configuration
 * @param the row that i want to set the cursor
 * @param the column that i want to set the cursor
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
static STD_ReturnType lcd_8bit_set_curser(const chr_lcd_8bit_t *lcd,uint8 row ,uint8 column ){
STD_ReturnType ret = E_OK; 
column--;
switch(row){
    case 1 : ret =  lcd_8bit_send_command(lcd, (0x80+column)); break;
        
    case 2 : ret =  lcd_8bit_send_command(lcd, (0xc0+column)); break;
            
    case 3 : ret =  lcd_8bit_send_command(lcd, (0x94+column)); break;
          
    case 4 : ret =  lcd_8bit_send_command(lcd, (0xd4+column)); break;
       
    default: ;
}
        
return ret;  

}
/**
 * @brief set cursor at specific position at 4bir_lcd
 * @param lcd : pointer to the LCD module configuration
 * @param the row that i want to set the cursor
 * @param the column that i want to set the cursor
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
static STD_ReturnType lcd_4bit_set_curser(const chr_lcd_4bit_t *lcd,uint8 row ,uint8 column ){
STD_ReturnType ret = E_OK; 
column--;
switch(row){
    case 1 : ret =  lcd_4bit_send_command(lcd, (0x80+column)); break;
        
    case 2 : ret =  lcd_4bit_send_command(lcd, (0xc0+column)); break;
            
    case 3 : ret =  lcd_4bit_send_command(lcd, (0x94+column)); break;
          
    case 4 : ret =  lcd_4bit_send_command(lcd, (0xd4+column)); break;
       
    default: ;
}
        
return ret;  

}
