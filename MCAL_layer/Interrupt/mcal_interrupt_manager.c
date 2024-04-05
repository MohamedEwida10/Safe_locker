/* 
 * File:   mcal_interrupt_manager.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:27 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1;
static volatile uint8 RB5_flag = 1;
static volatile uint8 RB6_flag = 1;
static volatile uint8 RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() INTERRUPT_MANAGER_HIGH(void){
if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
    INT0_ISR();
}
else{/* nothing */}

if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
    INT2_ISR();
}
else{/* nothing */}
}


void __interrupt(low_priority) INTERRUPT_MANAGER_LOW(void){

if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
    INT1_ISR();
}
else{/* nothing */}

}

#else

void __interrupt() INTERRUPT_MANAGER_HIGH(void){
if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
    INT0_ISR();
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
    INT1_ISR();
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
    INT2_ISR();
}
else{/* nothing */}
/*********************************************************************************/
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
    (PORTBbits.RB4 == 1)&& (1 == RB4_flag)){
    RB4_flag = 0;
    RB4_ISR(1);
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
    && (PORTBbits.RB4 == 0) && (0 == RB4_flag)){
    RB4_flag = 1;
    RB4_ISR(0);
}
else{/* nothing */}

/*********************************************************************************/
/*********************************************************************************/
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB5 == 1)&& (1 == RB5_flag)){
    RB5_flag = 0;
    RB5_ISR(1);
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB5 == 0)&& (0 == RB5_flag)){
    RB5_flag = 1;
    RB5_ISR(0);
}
else{/* nothing */}

/*********************************************************************************/
/*********************************************************************************/
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB6 == 1)&& (1 == RB6_flag)){
    RB6_flag = 0;
    RB6_ISR(1);
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB6 == 0)&& (0 == RB6_flag)){
    RB6_flag = 1;
    RB6_ISR(0);
}
else{/* nothing */}

/*********************************************************************************/
/*********************************************************************************/
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB7 == 1)&& (1 == RB7_flag)){
    RB7_flag = 0;
    RB7_ISR(1);
}
else{/* nothing */}
if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)
   && (PORTBbits.RB7 == 0)&& (0 == RB7_flag)){
    RB7_flag = 1;
    RB7_ISR(0);
}
else{/* nothing */}

/*********************************************************************************/
}


#endif
