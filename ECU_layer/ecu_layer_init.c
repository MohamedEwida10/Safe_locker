/* 
 * File:   ecu_layer_init.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 9:11 PM
 */


#include "ecu_layer_init.h"

led_t red_led = {.led_status = LED_OFF,.port_name = PORTC_INDEX,.pin = PIN6,};
led_t green_led = {.led_status = LED_OFF,.port_name = PORTC_INDEX,.pin = PIN7};

void INT0_app_ISR(void){
    for(int i = 0;i <= 7;i++){
        Data_EEPROM_WriteByte(0x03f8 + i,0xFF);
    }
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);
    lcd_4bit_send_string_pos(&lcd1,2,1,"system will close in ");
    lcd_4bit_send_string_pos(&lcd1,3,1,"3");
    __delay_ms(500);
    lcd_4bit_send_string_pos(&lcd1,3,1," ");
    __delay_ms(500);
    lcd_4bit_send_string_pos(&lcd1,3,1,"2");
    __delay_ms(500);
    lcd_4bit_send_string_pos(&lcd1,3,1," ");
    __delay_ms(500);
    lcd_4bit_send_string_pos(&lcd1,3,1,"1");
    __delay_ms(500);
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    __delay_ms(20);

}

Interrupt_INTx_t INT_obj ={ .EXT_Interrupr_Handler = INT0_app_ISR,
                            .edge = INTERRUPT_RISING_EDGE,
                            .source = INTERRUPT_EXTERNAL_INT0,
                            .priority = Interrupt_HIGH_PRIORITY,
                            .mcu_pin.direction = DICRECTION_INPUT,
                            .mcu_pin.port = PORTB_INDEX,
                            .mcu_pin.pin = PIN0   };

dc_motor_t motor1 = {.dc_motor_pin[0].direction = DICRECTION_OUTOUT,
                     .dc_motor_pin[0].port = PORTA_INDEX,
                     .dc_motor_pin[0].pin = PIN1,
                     .dc_motor_pin[0].logic = LOW,
                     .dc_motor_pin[1].direction = DICRECTION_OUTOUT,
                     .dc_motor_pin[1].port = PORTA_INDEX,
                     .dc_motor_pin[1].pin = PIN2,
                     .dc_motor_pin[1].logic = LOW };

pin_config_t buzzer = {.port = PORTA_INDEX,.pin = PIN3,.direction = DICRECTION_OUTOUT,.logic = LOW};

button_t btn1 = {.button_pin.port = PORTA_INDEX,.button_pin.direction = DICRECTION_INPUT,
                 .button_pin.logic = LOW,.button_pin.pin = PIN0,
                    .button_state = BUTTON_RELEASED, .button_connection = BUTTON_ACTIVE_HIGH};
        
chr_lcd_4bit_t lcd1 ={
.rs.port = PORTC_INDEX,
.rs.direction = DICRECTION_OUTOUT,
.rs.pin = PIN0,
.rs.logic = LOW,

.en.port = PORTC_INDEX,
.en.direction = DICRECTION_OUTOUT,
.en.pin = PIN1,
.en.logic = LOW,

.data[0].port = PORTC_INDEX,
.data[0].direction = DICRECTION_OUTOUT,
.data[0].pin = PIN2,
.data[0].logic = LOW,

.data[1].port = PORTC_INDEX,
.data[1].direction = DICRECTION_OUTOUT,
.data[1].pin = PIN3,
.data[1].logic = LOW,

.data[2].port = PORTC_INDEX,
.data[2].direction = DICRECTION_OUTOUT,
.data[2].pin = PIN4,
.data[2].logic = LOW,

.data[3].port = PORTC_INDEX,
.data[3].direction = DICRECTION_OUTOUT,
.data[3].pin = PIN5,
.data[3].logic = LOW,

};

keypad_t keypad = {
.keypad_rows_pins[0].port = PORTD_INDEX,
.keypad_rows_pins[0].pin = PIN0,
.keypad_rows_pins[0].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[0].logic = LOW,
.keypad_rows_pins[1].port = PORTD_INDEX,
.keypad_rows_pins[1].pin = PIN1,
.keypad_rows_pins[1].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[1].logic = LOW,
.keypad_rows_pins[2].port = PORTD_INDEX,
.keypad_rows_pins[2].pin = PIN2,
.keypad_rows_pins[2].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[2].logic = LOW,
.keypad_rows_pins[3].port = PORTD_INDEX,
.keypad_rows_pins[3].pin = PIN3,
.keypad_rows_pins[3].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[3].logic = LOW,

.keypad_columns_pins[0].port = PORTD_INDEX,
.keypad_columns_pins[0].pin = PIN4,
.keypad_columns_pins[0].direction = DICRECTION_INPUT,
.keypad_columns_pins[0].logic = LOW,
.keypad_columns_pins[1].port = PORTD_INDEX,
.keypad_columns_pins[1].pin = PIN5,
.keypad_columns_pins[1].direction = DICRECTION_INPUT,
.keypad_columns_pins[1].logic = LOW,
.keypad_columns_pins[2].port = PORTD_INDEX,
.keypad_columns_pins[2].pin = PIN6,
.keypad_columns_pins[2].direction = DICRECTION_INPUT,
.keypad_columns_pins[2].logic = LOW,
.keypad_columns_pins[3].port = PORTD_INDEX,
.keypad_columns_pins[3].pin = PIN7,
.keypad_columns_pins[3].direction = DICRECTION_INPUT,
.keypad_columns_pins[3].logic = LOW,
};

void ecu_layer_Initialization(void)
{
    lcd_4bit_initialize(&lcd1);
    ecu_keypad_initialize(&keypad);
    ecu_led_initialize(&red_led);
    ecu_led_initialize(&green_led);
    ecu_dc_motor_initialize(&motor1);
    gpio_pin_initialize(&buzzer);
    Interrupt_INTx_Init(&INT_obj);
}