/* 
 * File:   ecu_chr_LCD.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on January 30, 2024, 1:33 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/******************* Section : Includes *******************/
#include "ecu_chr_LCD_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/******************* Section : Macro Declarations *******************/
#define _LCD_CLEAR                     0x01
#define _LCD_RETURN_HOME               0x02
#define _LCD_ENTRY_MODE                0x06
#define _LCD_CURSER_OFF_DEPLAY_ON      0x0C
#define _LCD_CURSER_OFF_DEPLAY_OFF     0x08
#define _LCD_CURSER_ON_BLINK_ON        0x0F
#define _LCD_CURSER_ON_BLINK_OFF       0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT       0x1C
#define _LCD_DISPLAY_SHIFT_LEFT        0x18
#define _LCD_8BIT_MODE_2_LINE          0x38
#define _LCD_4BIT_MODE_2_LINE          0x28
#define _LCD_CGRAM_START               0x40
#define _LCD_DDRAM_START               0x80


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
typedef struct{
pin_config_t rs;
pin_config_t en;
pin_config_t data[4];
}chr_lcd_4bit_t;

typedef struct{
pin_config_t rs;
pin_config_t en;
pin_config_t data[8];
}chr_lcd_8bit_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);
STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command);
STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data);
STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data);
STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str);
STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str);
STD_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos);

STD_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command);
STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data);
STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data);
STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str);
STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str);
STD_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,
                                          const uint8 _chr[],uint8 mem_pos);

STD_ReturnType convert_byte_to_string(uint8 value,uint8 *str);
STD_ReturnType convert_short_to_string(uint16 value,uint8 *str);
STD_ReturnType convert_int_to_string(uint32 value,uint8 *str);

#endif	/* ECU_CHR_LCD_H */

