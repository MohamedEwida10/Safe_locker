/* 
 * File:   mcal_external_interrupt.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:26 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/******************* Section : Includes *******************/

#include "mcal_interrupt_cfg.h"
#include "../GPIO/hal_gpio.h"
/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/
#if INTERRUPT_INTX_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for external interrupt, INT0 */
#define EXT_INT0_INTERRUPT_ENABLE()            (INTCONbits.INT0IE = 1)
/* this macro clear the interrupt enable for external interrupt, INT0 */
#define EXT_INT0_INTERRUPT_DISABLE()           (INTCONbits.INT0IE = 0)
/* this macro clear the interrupt flag for external interrupt, INT0*/
#define EXT_INT0_INTERRUPT_CLEAR_FLAG()        (INTCONbits.INT0IF = 0)
/* this macro detect the rising edge for external interrupt, INT0*/
#define EXT_INT0_RisingEdgeSet()               (INTCON2bits.INTEDG0 = 1)
/* this macro detect the Falling edge for external interrupt, INT0*/
#define EXT_INT0_FallingEdgeSet()              (INTCON2bits.INTEDG0 = 0)

/* this macro set the interrupt enable for external interrupt, INT1 */
#define EXT_INT1_INTERRUPT_ENABLE()            (INTCON3bits.INT1IE = 1)
/* this macro clear the interrupt enable for external interrupt, INT1 */
#define EXT_INT1_INTERRUPT_DISABLE()           (INTCON3bits.INT1IE = 0)
/* this macro clear the interrupt flag for external interrupt, INT1*/
#define EXT_INT1_INTERRUPT_CLEAR_FLAG()        (INTCON3bits.INT1IF = 0)
/* this macro detect the rising edge for external interrupt, INT1*/
#define EXT_INT1_RisingEdgeSet()               (INTCON2bits.INTEDG1 = 1)
/* this macro detect the Falling edge for external interrupt, INT1*/
#define EXT_INT1_FallingEdgeSet()              (INTCON2bits.INTEDG1 = 0)

/* this macro set the interrupt enable for external interrupt, INT2 */
#define EXT_INT2_INTERRUPT_ENABLE()            (INTCON3bits.INT2IE = 1)
/* this macro clear the interrupt enable for external interrupt, INT2 */
#define EXT_INT2_INTERRUPT_DISABLE()           (INTCON3bits.INT2IE = 0)
/* this macro clear the interrupt flag for external interrupt, INT2*/
#define EXT_INT2_INTERRUPT_CLEAR_FLAG()        (INTCON3bits.INT2IF = 0)
/* this macro detect the rising edge for external interrupt, INT2*/
#define EXT_INT2_RisingEdgeSet()               (INTCON2bits.INTEDG2 = 1)
/* this macro detect the Falling edge for external interrupt, INT2*/
#define EXT_INT2_FallingEdgeSet()              (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the INT1 external interrupt priority to be HIGH PRIORTY  */
#define EXT_INT1_HighPrioritySet()            (INTCON3bits.INT1IP= 1)
/* this macro set the INT1 external interrupt priority to be LOW PRIORTY  */
#define EXT_INT1_LowPrioritySet()            (INTCON3bits.INT1IP= 0)
/* this macro set the INT2 external interrupt priority to be HIGH PRIORTY  */
#define EXT_INT2_HighPrioritySet()            (INTCON3bits.INT2IP= 1)
/* this macro set the INT2 external interrupt priority to be LOW PRIORTY  */
#define EXT_INT2_LowPrioritySet()            (INTCON3bits.INT2IP= 0)

#endif

#endif

#if INTERRUPT_OnChange_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the interrupt enable for external interrupt, RBx  */
#define EXT_RBx_INTERRUPT_ENABLE()             (INTCONbits.RBIE = 1)
/* this macro clear the interrupt enable for external interrupt, RBx  */
#define EXT_RBx_INTERRUPT_DISABLE()            (INTCONbits.RBIE = 0)
/* this macro clear the interrupt flag for external interrupt, RBx */
#define EXT_RBx_INTERRUPT_CLEAR_FLAG()         (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the RBx external interrupt priority to be HIGH PRIORTY  */
#define EXT_RBx_HighPrioritySet()            (INTCON2bits.RBIP= 1)
/* this macro set the RBx external interrupt priority to be LOW PRIORTY  */
#define EXT_RBx_LowPrioritySet()            (INTCON2bits.RBIP= 0)

#endif

#endif



/******************* Section : MacroData Type Declarations *******************/
typedef void (*INTERRUPT_HANDLER)(void);
typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2         
}INTERRUPT_INTx_src_t;

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE ,        
}INTERRUPT_INTx_edge_t;

typedef struct{
    void (* EXT_Interrupr_Handler)(void);
    pin_config_t mcu_pin;
    INTERRUPT_INTx_edge_t edge;
    INTERRUPT_INTx_src_t  source; 
    Interrupt_PRIORITY_cfg priority;
}Interrupt_INTx_t;

typedef struct{
    void (* EXT_Interrupr_Handler_HIGH)(void);
    void (* EXT_Interrupr_Handler_LOW)(void);    
    pin_config_t mcu_pin;
    Interrupt_PRIORITY_cfg priority;
}Interrupt_RBx_t;

/******************* Section : Functions Declarations *******************/
STD_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t *int_obj);
STD_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t *int_obj);
STD_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_t *RB_obj);
STD_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t *RB_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

