/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Blu-Ray
 *
 * Created on February 14, 2024, 5:03 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/******************* Section : Includes *******************/

#define INTERRUPT_FEATURE_ENABLE                        1
//#define INTERRUPT_PRIORITY_LEVEL_ENABLE       INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_INTX_FEAUTRE_ENABLE         INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_OnChange_FEAUTRE_ENABLE     INTERRUPT_FEATURE_ENABLE

/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
typedef enum{
Interrupt_LOW_PRIORITY = 0,
Interrupt_HIGH_PRIORITY        
}Interrupt_PRIORITY_cfg;

/******************* Section : Functions Declarations *******************/



#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

