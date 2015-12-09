/*******************************************************************************
* File Name: interrupt_timer.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_interrupt_timer_H)
#define CY_ISR_interrupt_timer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void interrupt_timer_Start(void);
void interrupt_timer_StartEx(cyisraddress address);
void interrupt_timer_Stop(void);

CY_ISR_PROTO(interrupt_timer_Interrupt);

void interrupt_timer_SetVector(cyisraddress address);
cyisraddress interrupt_timer_GetVector(void);

void interrupt_timer_SetPriority(uint8 priority);
uint8 interrupt_timer_GetPriority(void);

void interrupt_timer_Enable(void);
uint8 interrupt_timer_GetState(void);
void interrupt_timer_Disable(void);

void interrupt_timer_SetPending(void);
void interrupt_timer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the interrupt_timer ISR. */
#define interrupt_timer_INTC_VECTOR            ((reg32 *) interrupt_timer__INTC_VECT)

/* Address of the interrupt_timer ISR priority. */
#define interrupt_timer_INTC_PRIOR             ((reg8 *) interrupt_timer__INTC_PRIOR_REG)

/* Priority of the interrupt_timer interrupt. */
#define interrupt_timer_INTC_PRIOR_NUMBER      interrupt_timer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable interrupt_timer interrupt. */
#define interrupt_timer_INTC_SET_EN            ((reg32 *) interrupt_timer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the interrupt_timer interrupt. */
#define interrupt_timer_INTC_CLR_EN            ((reg32 *) interrupt_timer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the interrupt_timer interrupt state to pending. */
#define interrupt_timer_INTC_SET_PD            ((reg32 *) interrupt_timer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the interrupt_timer interrupt. */
#define interrupt_timer_INTC_CLR_PD            ((reg32 *) interrupt_timer__INTC_CLR_PD_REG)


#endif /* CY_ISR_interrupt_timer_H */


/* [] END OF FILE */
