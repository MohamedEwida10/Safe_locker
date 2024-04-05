/* 
 * File:   ecu_DC_motor.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 3, 2023, 6:49 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/******************* Section : Includes ***************************************/
#include "ecu_DC_motor_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
/******************* Section : Macro Declarations *****************************/
#define DC_MOTOR_ON_STATUS     0x01U
#define DC_MOTOR_OFF_STATUS    0x00U

/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations ********************/

typedef struct{
  pin_config_t dc_motor_pin[2];
}dc_motor_t;

/******************* Section : Functions Declarations *************************/
STD_ReturnType ecu_dc_motor_initialize(const dc_motor_t *dc_motor);
STD_ReturnType ecu_dc_motor_move_right(const dc_motor_t *dc_motor);
STD_ReturnType ecu_dc_motor_move_left(const dc_motor_t *dc_motor);
STD_ReturnType ecu_dc_motor_stop(const dc_motor_t *dc_motor);

#endif	/* DC_MOTOR_H */

