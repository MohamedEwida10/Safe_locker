/* 
 * File:   mcal_interrupt_cfg.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:17 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H


/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
/******************* Section : Macro Declarations *******************/
#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0

/******************* Section : Macro Functions Declarations *******************/

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro will enable the priority level on interrupt */
#define INTERRUPT_PriorityLevelEnable()   (RCONbits.IPEN = 1)
/* this macro will disable the priority level on interrupt */
#define INTERRUPT_PriorityLevelDisable()   (RCONbits.IPEN = 0)
/* this macro will enable all high priority global interrupt */
#define INTERRUPT_GlobalIterruptHighEnable()   (INTCONbits.GIEH = 1)
/* this macro will disable all high priority global interrupt */
#define INTERRUPT_GlobalIterruptHighDisable()  (INTCONbits.GIEH = 0)
/* this macro will enable all low priority global interrupt */
#define INTERRUPT_GlobalIterruptLowEnable()    (INTCONbits.GIEL = 1)
/* this macro will disable all low priority global interrupt */
#define INTERRUPT_GlobalIterruptLowDisable()   (INTCONbits.GIEL = 0)

#else

/* this macro will enable all global interrupt */
#define INTERRUPT_GlobalIterruptEnable()   (INTCONbits.GIE = 1)
/* this macro will disable all global interrupt */
#define INTERRUPT_GlobalIterruptDisable()  (INTCONbits.GIE = 0)
/* this macro will enable periphral interrupt */
#define INTERRUPT_PeriphralInterruptEnable()   (INTCONbits.PEIE = 1)
/* this macro will disable periphral interrupt */
#define INTERRUPT_PeriphralInterruptDisable()  (INTCONbits.PEIE = 0)

#endif
/******************* Section : MacroData Type Declarations *******************/


/******************* Section : Functions Declarations *******************/


#endif	/* MCAL_INTERRUPT_CFG_H */

