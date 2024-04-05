/* 
 * File:   mcal_interrupt_manager.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:27 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/******************* Section : Includes *******************/
#include "mcal_interrupt_cfg.h"
/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/


/******************* Section : Functions Declarations *******************/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

