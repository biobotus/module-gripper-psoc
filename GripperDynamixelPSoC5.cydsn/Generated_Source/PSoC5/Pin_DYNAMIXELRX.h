/*******************************************************************************
* File Name: Pin_DYNAMIXELRX.h  
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

#if !defined(CY_PINS_Pin_DYNAMIXELRX_H) /* Pins Pin_DYNAMIXELRX_H */
#define CY_PINS_Pin_DYNAMIXELRX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_DYNAMIXELRX_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_DYNAMIXELRX__PORT == 15 && ((Pin_DYNAMIXELRX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_DYNAMIXELRX_Write(uint8 value) ;
void    Pin_DYNAMIXELRX_SetDriveMode(uint8 mode) ;
uint8   Pin_DYNAMIXELRX_ReadDataReg(void) ;
uint8   Pin_DYNAMIXELRX_Read(void) ;
uint8   Pin_DYNAMIXELRX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_DYNAMIXELRX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_DYNAMIXELRX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_DYNAMIXELRX_DM_RES_UP          PIN_DM_RES_UP
#define Pin_DYNAMIXELRX_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_DYNAMIXELRX_DM_OD_LO           PIN_DM_OD_LO
#define Pin_DYNAMIXELRX_DM_OD_HI           PIN_DM_OD_HI
#define Pin_DYNAMIXELRX_DM_STRONG          PIN_DM_STRONG
#define Pin_DYNAMIXELRX_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_DYNAMIXELRX_MASK               Pin_DYNAMIXELRX__MASK
#define Pin_DYNAMIXELRX_SHIFT              Pin_DYNAMIXELRX__SHIFT
#define Pin_DYNAMIXELRX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_DYNAMIXELRX_PS                     (* (reg8 *) Pin_DYNAMIXELRX__PS)
/* Data Register */
#define Pin_DYNAMIXELRX_DR                     (* (reg8 *) Pin_DYNAMIXELRX__DR)
/* Port Number */
#define Pin_DYNAMIXELRX_PRT_NUM                (* (reg8 *) Pin_DYNAMIXELRX__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_DYNAMIXELRX_AG                     (* (reg8 *) Pin_DYNAMIXELRX__AG)                       
/* Analog MUX bux enable */
#define Pin_DYNAMIXELRX_AMUX                   (* (reg8 *) Pin_DYNAMIXELRX__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_DYNAMIXELRX_BIE                    (* (reg8 *) Pin_DYNAMIXELRX__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_DYNAMIXELRX_BIT_MASK               (* (reg8 *) Pin_DYNAMIXELRX__BIT_MASK)
/* Bypass Enable */
#define Pin_DYNAMIXELRX_BYP                    (* (reg8 *) Pin_DYNAMIXELRX__BYP)
/* Port wide control signals */                                                   
#define Pin_DYNAMIXELRX_CTL                    (* (reg8 *) Pin_DYNAMIXELRX__CTL)
/* Drive Modes */
#define Pin_DYNAMIXELRX_DM0                    (* (reg8 *) Pin_DYNAMIXELRX__DM0) 
#define Pin_DYNAMIXELRX_DM1                    (* (reg8 *) Pin_DYNAMIXELRX__DM1)
#define Pin_DYNAMIXELRX_DM2                    (* (reg8 *) Pin_DYNAMIXELRX__DM2) 
/* Input Buffer Disable Override */
#define Pin_DYNAMIXELRX_INP_DIS                (* (reg8 *) Pin_DYNAMIXELRX__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_DYNAMIXELRX_LCD_COM_SEG            (* (reg8 *) Pin_DYNAMIXELRX__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_DYNAMIXELRX_LCD_EN                 (* (reg8 *) Pin_DYNAMIXELRX__LCD_EN)
/* Slew Rate Control */
#define Pin_DYNAMIXELRX_SLW                    (* (reg8 *) Pin_DYNAMIXELRX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_DYNAMIXELRX_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_DYNAMIXELRX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_DYNAMIXELRX_PRTDSI__OE_SEL0        (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__OE_SEL0) 
#define Pin_DYNAMIXELRX_PRTDSI__OE_SEL1        (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_DYNAMIXELRX_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__OUT_SEL0) 
#define Pin_DYNAMIXELRX_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_DYNAMIXELRX_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_DYNAMIXELRX__PRTDSI__SYNC_OUT) 


#if defined(Pin_DYNAMIXELRX__INTSTAT)  /* Interrupt Registers */

    #define Pin_DYNAMIXELRX_INTSTAT                (* (reg8 *) Pin_DYNAMIXELRX__INTSTAT)
    #define Pin_DYNAMIXELRX_SNAP                   (* (reg8 *) Pin_DYNAMIXELRX__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_DYNAMIXELRX_H */


/* [] END OF FILE */
