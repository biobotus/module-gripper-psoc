/*******************************************************************************
* File Name: CAN_Enable.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CAN_Enable_H) /* Pins CAN_Enable_H */
#define CY_PINS_CAN_Enable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CAN_Enable_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CAN_Enable__PORT == 15 && ((CAN_Enable__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CAN_Enable_Write(uint8 value) ;
void    CAN_Enable_SetDriveMode(uint8 mode) ;
uint8   CAN_Enable_ReadDataReg(void) ;
uint8   CAN_Enable_Read(void) ;
uint8   CAN_Enable_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CAN_Enable_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CAN_Enable_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CAN_Enable_DM_RES_UP          PIN_DM_RES_UP
#define CAN_Enable_DM_RES_DWN         PIN_DM_RES_DWN
#define CAN_Enable_DM_OD_LO           PIN_DM_OD_LO
#define CAN_Enable_DM_OD_HI           PIN_DM_OD_HI
#define CAN_Enable_DM_STRONG          PIN_DM_STRONG
#define CAN_Enable_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CAN_Enable_MASK               CAN_Enable__MASK
#define CAN_Enable_SHIFT              CAN_Enable__SHIFT
#define CAN_Enable_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CAN_Enable_PS                     (* (reg8 *) CAN_Enable__PS)
/* Data Register */
#define CAN_Enable_DR                     (* (reg8 *) CAN_Enable__DR)
/* Port Number */
#define CAN_Enable_PRT_NUM                (* (reg8 *) CAN_Enable__PRT) 
/* Connect to Analog Globals */                                                  
#define CAN_Enable_AG                     (* (reg8 *) CAN_Enable__AG)                       
/* Analog MUX bux enable */
#define CAN_Enable_AMUX                   (* (reg8 *) CAN_Enable__AMUX) 
/* Bidirectional Enable */                                                        
#define CAN_Enable_BIE                    (* (reg8 *) CAN_Enable__BIE)
/* Bit-mask for Aliased Register Access */
#define CAN_Enable_BIT_MASK               (* (reg8 *) CAN_Enable__BIT_MASK)
/* Bypass Enable */
#define CAN_Enable_BYP                    (* (reg8 *) CAN_Enable__BYP)
/* Port wide control signals */                                                   
#define CAN_Enable_CTL                    (* (reg8 *) CAN_Enable__CTL)
/* Drive Modes */
#define CAN_Enable_DM0                    (* (reg8 *) CAN_Enable__DM0) 
#define CAN_Enable_DM1                    (* (reg8 *) CAN_Enable__DM1)
#define CAN_Enable_DM2                    (* (reg8 *) CAN_Enable__DM2) 
/* Input Buffer Disable Override */
#define CAN_Enable_INP_DIS                (* (reg8 *) CAN_Enable__INP_DIS)
/* LCD Common or Segment Drive */
#define CAN_Enable_LCD_COM_SEG            (* (reg8 *) CAN_Enable__LCD_COM_SEG)
/* Enable Segment LCD */
#define CAN_Enable_LCD_EN                 (* (reg8 *) CAN_Enable__LCD_EN)
/* Slew Rate Control */
#define CAN_Enable_SLW                    (* (reg8 *) CAN_Enable__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CAN_Enable_PRTDSI__CAPS_SEL       (* (reg8 *) CAN_Enable__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CAN_Enable_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CAN_Enable__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CAN_Enable_PRTDSI__OE_SEL0        (* (reg8 *) CAN_Enable__PRTDSI__OE_SEL0) 
#define CAN_Enable_PRTDSI__OE_SEL1        (* (reg8 *) CAN_Enable__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CAN_Enable_PRTDSI__OUT_SEL0       (* (reg8 *) CAN_Enable__PRTDSI__OUT_SEL0) 
#define CAN_Enable_PRTDSI__OUT_SEL1       (* (reg8 *) CAN_Enable__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CAN_Enable_PRTDSI__SYNC_OUT       (* (reg8 *) CAN_Enable__PRTDSI__SYNC_OUT) 


#if defined(CAN_Enable__INTSTAT)  /* Interrupt Registers */

    #define CAN_Enable_INTSTAT                (* (reg8 *) CAN_Enable__INTSTAT)
    #define CAN_Enable_SNAP                   (* (reg8 *) CAN_Enable__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CAN_Enable_H */


/* [] END OF FILE */
