/* 
 * File:   hal_gpio.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 21, 2023, 9:11 PM
 */

#include "hal_gpio.h"
/* Reference to the data direction control register */ 
volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/* Reference to the data latch register(read & write to data latch) */ 
volatile uint8 *lat_registers[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};
/* Reference to the port status register */
volatile uint8 *port_registers[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * @brief Initialize the direction of specific pin @ref direction_t
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_direction_initialize(const pin_config_t* _pin_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (_pin_config->direction)
        {
        case DICRECTION_OUTOUT :
            CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break;
        case DICRECTION_INPUT :
            SIT_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
            break;  
        default : ret = E_NOT_OK;    
        }
    }
    
     return ret;       
}
#endif

/**
 * @brief Read the direction status of specific pin @ref direction_t
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @param direction_status
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed 
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t* _pin_config,direction_t *direction_status )
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }   
   
     return ret; 
}
#endif

/**
 * @brief Write a logic on specific pin @ref logic_t
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_write_logic(const pin_config_t* _pin_config, logic_t logic)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
        case LOW :
            CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
            break;
        case HIGH :
            SIT_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
            break;  
        default : ret = E_NOT_OK;    
        }
    }   
   
     return ret; 
}
#endif

/**
 * @brief Read a logic of specific pin @ref logic_t
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_read_logic(const pin_config_t* _pin_config, logic_t *logic)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
         *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }   
   
     return ret;  
}
#endif

/**
 * @brief Toggle a logic of specific pin @ref logic_t 
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t* _pin_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }   
   
     return ret;  
}
#endif
/**
 * @brief Initialize a pin direction and write a logic low on the pin
 * @param _pin_config pointer to configuration  @ref pin_config_t 
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_PIN_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_pin_initialize(const pin_config_t* _pin_config)
{
    STD_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }   
   
     return ret;  
    
}
#endif
/******************************************************************************/

/**
 * @brief Initialize the direction of specific port @ref direction_t
 * @param port
 * @param direction
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_port_direction_initialize( port_index_t port, uint8 direction)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

/**
 * @brief Read the direction status of specific port @ref direction_t
 * @param port
 * @param direction_status
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_port_get_direction_status( port_index_t port, uint8 *direction_status)
{
    STD_ReturnType ret = E_OK;
    if((NULL == direction_status) || (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    
    return ret;
}
#endif

/**
 * @brief Write a logic on specific port @ref logic_t
 * @param port
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_port_write_logic( port_index_t port, uint8 logic)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }

    
    return ret; 
}
#endif

/**
 * @brief Read a logic from a specific port @ref logic_t
 * @param port
 * @param logic
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_port_read_logic( port_index_t port, uint8 *logic)
{
    STD_ReturnType ret = E_OK;
    if((NULL == logic) || (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = *lat_registers[port];
    }
    
    return ret;
}
#endif

/**
 * @brief Toggle a logic from a specific port @ref logic_t
 * @param port
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
STD_ReturnType gpio_port_toggle_logic( port_index_t port)
{
    STD_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORT_TOGGLE_MASK ;
    }

    
    return ret; 
}
#endif
