/*******************************************************************************
* File Name: CanReaderISR.h
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
#if !defined(CY_ISR_CanReaderISR_H)
#define CY_ISR_CanReaderISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CanReaderISR_Start(void);
void CanReaderISR_StartEx(cyisraddress address);
void CanReaderISR_Stop(void);

CY_ISR_PROTO(CanReaderISR_Interrupt);

void CanReaderISR_SetVector(cyisraddress address);
cyisraddress CanReaderISR_GetVector(void);

void CanReaderISR_SetPriority(uint8 priority);
uint8 CanReaderISR_GetPriority(void);

void CanReaderISR_Enable(void);
uint8 CanReaderISR_GetState(void);
void CanReaderISR_Disable(void);

void CanReaderISR_SetPending(void);
void CanReaderISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CanReaderISR ISR. */
#define CanReaderISR_INTC_VECTOR            ((reg32 *) CanReaderISR__INTC_VECT)

/* Address of the CanReaderISR ISR priority. */
#define CanReaderISR_INTC_PRIOR             ((reg8 *) CanReaderISR__INTC_PRIOR_REG)

/* Priority of the CanReaderISR interrupt. */
#define CanReaderISR_INTC_PRIOR_NUMBER      CanReaderISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CanReaderISR interrupt. */
#define CanReaderISR_INTC_SET_EN            ((reg32 *) CanReaderISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CanReaderISR interrupt. */
#define CanReaderISR_INTC_CLR_EN            ((reg32 *) CanReaderISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CanReaderISR interrupt state to pending. */
#define CanReaderISR_INTC_SET_PD            ((reg32 *) CanReaderISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CanReaderISR interrupt. */
#define CanReaderISR_INTC_CLR_PD            ((reg32 *) CanReaderISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_CanReaderISR_H */


/* [] END OF FILE */
