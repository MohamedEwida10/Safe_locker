/* 
 * File:   ecu_relay.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 2, 2023, 6:47 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/******************* Section : Includes ***************************************/
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/******************* Section : Macro Declarations *****************************/
#define RELAY_ON_STATUS     0x01U
#define RELAY_OFF_STATUS    0x00U

/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations ********************/
typedef struct{
    uint8 relay_port   :4 ;
    uint8 relay_pin    :3 ;
    uint8 relay_status :1 ;
}relay_t;

/******************* Section : Functions Declarations *************************/
STD_ReturnType ecu_relay_initialize(const relay_t *relay);
STD_ReturnType ecu_relay_on(const relay_t *relay);
STD_ReturnType ecu_relay_off(const relay_t *relay);


#endif	/* ECU_RELAY_H */

