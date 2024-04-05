/* 
 * File:   mcal_external_interrupt.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:26 PM
 */

#include "mcal_external_interrupt.h"
/* pointer to function to hold the callbacks for INTx */
static INTERRUPT_HANDLER INT0_INTERRUPT_HANDLER;
static INTERRUPT_HANDLER INT1_INTERRUPT_HANDLER;
static INTERRUPT_HANDLER INT2_INTERRUPT_HANDLER;
/* pointer to function to hold the callbacks for RBx */
static INTERRUPT_HANDLER RB4_INTERRUPT_HANDLER_HIGH;
static INTERRUPT_HANDLER RB4_INTERRUPT_HANDLER_LOW;
static INTERRUPT_HANDLER RB5_INTERRUPT_HANDLER_HIGH;
static INTERRUPT_HANDLER RB5_INTERRUPT_HANDLER_LOW;
static INTERRUPT_HANDLER RB6_INTERRUPT_HANDLER_HIGH;
static INTERRUPT_HANDLER RB6_INTERRUPT_HANDLER_LOW;
static INTERRUPT_HANDLER RB7_INTERRUPT_HANDLER_HIGH;
static INTERRUPT_HANDLER RB7_INTERRUPT_HANDLER_LOW;

static STD_ReturnType INTERRUPT_INTx_enable(const Interrupt_INTx_t *int_obj);
static STD_ReturnType INTERRUPT_INTx_disable(const Interrupt_INTx_t *int_obj);
static STD_ReturnType INTERRUPT_INTx_priority_int(const Interrupt_INTx_t *int_obj);
static STD_ReturnType INTERRUPT_INTx_edge_int(const Interrupt_INTx_t *int_obj);
static STD_ReturnType INTERRUPT_INTx_pin_int(const Interrupt_INTx_t *int_obj);
static STD_ReturnType INTERRUPT_INTx_clear_flag(const Interrupt_INTx_t *int_obj);

static STD_ReturnType INT0_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static STD_ReturnType INT1_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static STD_ReturnType INT2_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static STD_ReturnType INTERRUPT_SET_INTERRUPT_HANDLER(const Interrupt_INTx_t *int_obj);

static STD_ReturnType INTERRUPT_RBx_enable(const Interrupt_RBx_t *RB_obj);
static STD_ReturnType INTERRUPT_RBx_disable(const Interrupt_RBx_t *RB_obj);
static STD_ReturnType INTERRUPT_RBx_priority_int(const Interrupt_RBx_t *RB_obj);
static STD_ReturnType INTERRUPT_RBx_pin_int(const Interrupt_RBx_t *RB_obj);

/*******************************************************************************/

/**
  * @brief : Initialize the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
STD_ReturnType Interrupt_INTx_Init(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* clear the external interrupt */
        ret = INTERRUPT_INTx_disable(int_obj);
        /* clear the interrupt flag */
        ret |= INTERRUPT_INTx_clear_flag(int_obj);
        /* configure external interrupt edge */
        ret |= INTERRUPT_INTx_edge_int(int_obj);
        #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* configure external interrupt priority */
        ret |= INTERRUPT_INTx_priority_int(int_obj);
        #endif
        /* configure external interrupt i/o pin */
        ret |= INTERRUPT_INTx_pin_int(int_obj);
        /* configure the interrupt call back */
        ret |= INTERRUPT_SET_INTERRUPT_HANDLER(int_obj);
        /* enable the external interrupt */
        ret |= INTERRUPT_INTx_enable(int_obj);
    }   
   
     return ret;     
}

/**
 * the INTERRUPR_SERVACE_ROUTINE for INT0
 */
void INT0_ISR(void){
    /* clear the interrupt flag(must be software) */
    EXT_INT0_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(INT0_INTERRUPT_HANDLER){INT0_INTERRUPT_HANDLER();}  
}

/**
 * the INTERRUPR_SERVACE_ROUTINE for INT1
 */
void INT1_ISR(void){
    /* clear the interrupt flag(must be software) */
    EXT_INT1_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(INT1_INTERRUPT_HANDLER){INT1_INTERRUPT_HANDLER();}  
}

/**
 * the INTERRUPR_SERVACE_ROUTINE for INT2
 */
void INT2_ISR(void){
    /* clear the interrupt flag(must be software) */
    EXT_INT2_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(INT2_INTERRUPT_HANDLER){INT2_INTERRUPT_HANDLER();}  
}

/**
 * @brief the INTERRUPR_SERVACE_ROUTINE for RB4
 * @param RB4_source
 */
void RB4_ISR(uint8 RB4_source){
    /* clear the interrupt flag(must be software) */
    EXT_RBx_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(1 == RB4_source){
        if(RB4_INTERRUPT_HANDLER_HIGH){RB4_INTERRUPT_HANDLER_HIGH();   
        }
        else{/* nothing */}
    }
    else if(0 == RB4_source){
        if(RB4_INTERRUPT_HANDLER_LOW){RB4_INTERRUPT_HANDLER_LOW();   
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

/**
 * @brief the INTERRUPR_SERVACE_ROUTINE for RB5
 * @param RB4_source
 */
void RB5_ISR(uint8 RB5_source){
    /* clear the interrupt flag(must be software) */
    EXT_RBx_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(1 == RB5_source){
        if(RB5_INTERRUPT_HANDLER_HIGH){RB5_INTERRUPT_HANDLER_HIGH();   
        }
        else{/* nothing */}
    }
    else if(0 == RB5_source){
        if(RB5_INTERRUPT_HANDLER_LOW){RB5_INTERRUPT_HANDLER_LOW();   
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

/**
 * @brief the INTERRUPR_SERVACE_ROUTINE for RB6
 * @param RB4_source
 */
void RB6_ISR(uint8 RB6_source){
    /* clear the interrupt flag(must be software) */
    EXT_RBx_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(1 == RB6_source){
        if(RB6_INTERRUPT_HANDLER_HIGH){RB6_INTERRUPT_HANDLER_HIGH();   
        }
        else{/* nothing */}
    }
    else if(0 == RB6_source){
        if(RB6_INTERRUPT_HANDLER_LOW){RB6_INTERRUPT_HANDLER_LOW();   
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

/**
 * @brief the INTERRUPR_SERVACE_ROUTINE for RB7
 * @param RB4_source
 */
void RB7_ISR(uint8 RB7_source){
    /* clear the interrupt flag(must be software) */
    EXT_RBx_INTERRUPT_CLEAR_FLAG();
    /* code */
    
    /* callback function */
    if(1 == RB7_source){
        if(RB7_INTERRUPT_HANDLER_HIGH){RB7_INTERRUPT_HANDLER_HIGH();   
        }
        else{/* nothing */}
    }
    else if(0 == RB7_source){
        if(RB7_INTERRUPT_HANDLER_LOW){RB7_INTERRUPT_HANDLER_LOW();   
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

/**
  * @brief : De_initialize the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
STD_ReturnType Interrupt_INTx_DeInit(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = INTERRUPT_INTx_disable(int_obj);
    }   
   
     return ret;        
    
}

/**
  * @brief : Initialize the IRBx_INTERRUPT module
  * @param RB_obj :configuration of RBx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
STD_ReturnType Interrupt_RBx_Init(const Interrupt_RBx_t *RB_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* clear the external interrupt */
        ret = INTERRUPT_RBx_disable(RB_obj);
        /* clear the interrupt flag */
        ret = EXT_RBx_INTERRUPT_CLEAR_FLAG();
            /* configure external interrupt priority */
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE 
                ret = INTERRUPT_RBx_priority_int(RB_obj)
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable();
            #endif
                /* configure external interrupt i/o pin */
                ret = INTERRUPT_RBx_pin_int(RB_obj);
                /* configure the callback function */
                switch(RB_obj->mcu_pin.pin){
                    case PIN4 :
                    RB4_INTERRUPT_HANDLER_HIGH = RB_obj->EXT_Interrupr_Handler_HIGH; 
                    RB4_INTERRUPT_HANDLER_LOW = RB_obj->EXT_Interrupr_Handler_LOW; 
                        break;
                    case PIN5 :
                    RB5_INTERRUPT_HANDLER_HIGH = RB_obj->EXT_Interrupr_Handler_HIGH; 
                    RB5_INTERRUPT_HANDLER_LOW = RB_obj->EXT_Interrupr_Handler_LOW;      
                        break;    
                    case PIN6 :
                    RB6_INTERRUPT_HANDLER_HIGH = RB_obj->EXT_Interrupr_Handler_HIGH; 
                    RB6_INTERRUPT_HANDLER_LOW = RB_obj->EXT_Interrupr_Handler_LOW; 
                        break;
                    case PIN7 :
                    RB7_INTERRUPT_HANDLER_HIGH = RB_obj->EXT_Interrupr_Handler_HIGH; 
                    RB7_INTERRUPT_HANDLER_LOW = RB_obj->EXT_Interrupr_Handler_LOW;      
                        break;     
                }
                
        /* enable the external interrupt */
        ret = INTERRUPT_RBx_enable(RB_obj);
    }   
   
     return ret;     
    
}
/**
  * @brief : De_Initialize the IRBx_INTERRUPT module
  * @param RB_obj :configuration of RBx_INTERRUPT module
  * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
STD_ReturnType Interrupt_RBx_DeInit(const Interrupt_RBx_t *RB_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXT_RBx_INTERRUPT_DISABLE();  
        EXT_RBx_INTERRUPT_CLEAR_FLAG() ;
    }   
   
     return ret;        
    
}

/*******************************************************************************/
/**
  * @brief : enable the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_enable(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
            switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE     
                INTERRUPT_GlobalIterruptHighEnable();
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable();
            #endif                

                EXT_INT0_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE   
                INTERRUPT_PriorityLevelEnable();
                if(int_obj->priority == Interrupt_HIGH_PRIORITY){
                    INTERRUPT_GlobalIterruptHighEnable();
                }
                else if(int_obj->priority == Interrupt_LOW_PRIORITY){
                    INTERRUPT_GlobalIterruptLowEnable();
                }
                else{
                    /* nothing */
                } 
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable();
            #endif                

                EXT_INT1_INTERRUPT_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PriorityLevelEnable();
                if(int_obj->priority == Interrupt_HIGH_PRIORITY){
                    INTERRUPT_GlobalIterruptHighEnable();
                }
                else if(int_obj->priority == Interrupt_LOW_PRIORITY){
                    INTERRUPT_GlobalIterruptLowEnable();
                }
                else{
                    /* nothing */
                } 
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable();
            #endif                

                EXT_INT2_INTERRUPT_ENABLE();
                break;
            default : ret = E_NOT_OK;
        }
    }   
   
     return ret;     
}

/**
  * @brief : disable the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_disable(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
            switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_INTERRUPT_DISABLE();  break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_INTERRUPT_DISABLE();  break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_INTERRUPT_DISABLE();  break;
            default : ret = E_NOT_OK;
        }
    }   
   
     return ret;      
    
}

#if INTERRUPT_OnChange_FEAUTRE_ENABLE==INTERRUPT_FEATURE_ENABLE

/**
  * @brief : configure the priority of the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_priority_int(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
            switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT1 : 
                if(int_obj->priority == Interrupt_HIGH_PRIORITY){
                 EXT_INT1_HighPrioritySet();
                }
                else if(int_obj->priority == Interrupt_LOW_PRIORITY){
                 EXT_INT1_LowPrioritySet() ;   
                }
                else{
                    /* nothing */
                } 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(int_obj->priority == Interrupt_HIGH_PRIORITY){
                 EXT_INT2_HighPrioritySet();
                }
                else if(int_obj->priority == Interrupt_LOW_PRIORITY){
                 EXT_INT2_LowPrioritySet() ;   
                }
                else{
                    /* nothing */
                } 
                break;
            default : ret = E_NOT_OK;
            }
    }
   
     return ret;       
    
}
#endif
/**
  * @brief : configure the edge feature of the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_edge_int(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
            switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
               if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                 EXT_INT0_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                 EXT_INT0_RisingEdgeSet();   
                }
                else{
                    /* nothing */
                } 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                EXT_INT1_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                 EXT_INT1_RisingEdgeSet();   
                }
                else{
                    /* nothing */
                } 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(int_obj->edge == INTERRUPT_FALLING_EDGE){
                 EXT_INT2_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE){
                 EXT_INT2_RisingEdgeSet();   
                }
                else{
                    /* nothing */
                } 
                break;
            default : ret = E_NOT_OK;
            }
    }
     return ret;      
    
}

/**
  * @brief : configure the pin of the INTx_INTERRUPT module
  * @param int_obj :configuration of INTx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_pin_int(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }   
   
     return ret;     
    
}
/**
  * @brief : clear the flag of the IRBx_INTERRUPT module
  * @param int_obj :configuration of RBx_INTERRUPT module
  * @return   * @return status of the function
  *         (E_OK): The function done successfully 
  *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_INTx_clear_flag(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_INTERRUPT_CLEAR_FLAG();  break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_INTERRUPT_CLEAR_FLAG();  break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_INTERRUPT_CLEAR_FLAG();  break;
            default : ret = E_NOT_OK;
       }   
    }
   
     return ret;     
    
}

/**
 * @brief : store the ISR routine of INT0 in rhe INTERRUPT_HANDLER(pointer to function)
 * @param INTERRUPT_HANDLER
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INT0_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
 STD_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER)
    {
        ret = E_NOT_OK;
    }
    else
    {
       INT0_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    }
   
     return ret;     
}

/**
 * @brief : store the ISR routine of INT1 in rhe INTERRUPT_HANDLER(pointer to function)
 * @param INTERRUPT_HANDLER
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INT1_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
 STD_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER)
    {
        ret = E_NOT_OK;
    }
    else
    {
       INT1_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    }
   
     return ret;     
}

/**
 * @brief : store the ISR routine of INT2 in rhe INTERRUPT_HANDLER(pointer to function)
 * @param INTERRUPT_HANDLER
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INT2_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
 STD_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER)
    {
        ret = E_NOT_OK;
    }
    else
    {
       INT2_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    }
   
     return ret;     
}

/**
 * @brief : send the ISR routine to the suitable HELPER_FUNCTION 
 * @param INTERRUPT_HANDLER
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_SET_INTERRUPT_HANDLER(const Interrupt_INTx_t *int_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : INT0_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupr_Handler);  break;
            case INTERRUPT_EXTERNAL_INT1 : INT1_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupr_Handler);  break;
            case INTERRUPT_EXTERNAL_INT2 : INT2_SET_INTERRUPT_HANDLER(int_obj->EXT_Interrupr_Handler);  break;
            default : ret = E_NOT_OK;
       }   
    }
   
     return ret;     
}

/**
 * @brief : enable the RBx_INTERRUPT module
 * @param RB_obj:configuration of RBx_INTERRUPT module
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_RBx_enable(const Interrupt_RBx_t *RB_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* enable the external interrupt */
        ret = EXT_RBx_INTERRUPT_ENABLE();    
    }
   
     return ret;     
    
}

/**
 * @brief : disable the RBx_INTERRUPT module
 * @param RB_obj:configuration of RBx_INTERRUPT module
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_RBx_disable(const Interrupt_RBx_t *RB_obj){
     STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* clear the external interrupt */
        ret = EXT_RBx_INTERRUPT_DISABLE();    
    }
   
     return ret;    
   
}

/**
 * @brief : configure the priority of the RBx_INTERRUPT module
 * @param RB_obj:configuration of RBx_INTERRUPT module
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_RBx_priority_int(const Interrupt_RBx_t *RB_obj){
     STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {

                INTERRUPT_PriorityLevelEnable();
                if(RB_obj->priority == Interrupt_HIGH_PRIORITY){
                    INTERRUPT_GlobalIterruptHighEnable();
                    EXT_RBx_HighPrioritySet();
                }
                else if(RB_obj->priority == Interrupt_LOW_PRIORITY){
                    INTERRUPT_GlobalIterruptLowEnable();
                    EXT_RBx_LowPrioritySet();
                }
                else{
                    /* nothing */
                } 

    }
   
     return ret;    
    
}

/**
 * @brief : configure the pin of the RBx_INTERRUPT module
 * @param RB_obj:configuration of RBx_INTERRUPT module
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed */
static STD_ReturnType INTERRUPT_RBx_pin_int(const Interrupt_RBx_t *RB_obj){
     STD_ReturnType ret = E_OK;
    if(NULL == RB_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
       /* configure external interrupt i/o pin */
       ret = gpio_pin_direction_initialize(&(RB_obj->mcu_pin));    
    }
   
     return ret;    
        
    
}
