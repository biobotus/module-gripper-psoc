/*******************************************************************************
* File Name: TXCAN.h  
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

#if !defined(CY_PINS_TXCAN_H) /* Pins TXCAN_H */
#define CY_PINS_TXCAN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TXCAN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TXCAN__PORT == 15 && ((TXCAN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TXCAN_Write(uint8 value) ;
void    TXCAN_SetDriveMode(uint8 mode) ;
uint8   TXCAN_ReadDataReg(void) ;
uint8   TXCAN_Read(void) ;
uint8   TXCAN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TXCAN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TXCAN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TXCAN_DM_RES_UP          PIN_DM_RES_UP
#define TXCAN_DM_RES_DWN         PIN_DM_RES_DWN
#define TXCAN_DM_OD_LO           PIN_DM_OD_LO
#define TXCAN_DM_OD_HI           PIN_DM_OD_HI
#define TXCAN_DM_STRONG          PIN_DM_STRONG
#define TXCAN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TXCAN_MASK               TXCAN__MASK
#define TXCAN_SHIFT              TXCAN__SHIFT
#define TXCAN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TXCAN_PS                     (* (reg8 *) TXCAN__PS)
/* Data Register */
#define TXCAN_DR                     (* (reg8 *) TXCAN__DR)
/* Port Number */
#define TXCAN_PRT_NUM                (* (reg8 *) TXCAN__PRT) 
/* Connect to Analog Globals */                                                  
#define TXCAN_AG                     (* (reg8 *) TXCAN__AG)                       
/* Analog MUX bux enable */
#define TXCAN_AMUX                   (* (reg8 *) TXCAN__AMUX) 
/* Bidirectional Enable */                                                        
#define TXCAN_BIE                    (* (reg8 *) TXCAN__BIE)
/* Bit-mask for Aliased Register Access */
#define TXCAN_BIT_MASK               (* (reg8 *) TXCAN__BIT_MASK)
/* Bypass Enable */
#define TXCAN_BYP                    (* (reg8 *) TXCAN__BYP)
/* Port wide control signals */                                                   
#define TXCAN_CTL                    (* (reg8 *) TXCAN__CTL)
/* Drive Modes */
#define TXCAN_DM0                    (* (reg8 *) TXCAN__DM0) 
#define TXCAN_DM1                    (* (reg8 *) TXCAN__DM1)
#define TXCAN_DM2                    (* (reg8 *) TXCAN__DM2) 
/* Input Buffer Disable Override */
#define TXCAN_INP_DIS                (* (reg8 *) TXCAN__INP_DIS)
/* LCD Common or Segment Drive */
#define TXCAN_LCD_COM_SEG            (* (reg8 *) TXCAN__LCD_COM_SEG)
/* Enable Segment LCD */
#define TXCAN_LCD_EN                 (* (reg8 *) TXCAN__LCD_EN)
/* Slew Rate Control */
#define TXCAN_SLW                    (* (reg8 *) TXCAN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TXCAN_PRTDSI__CAPS_SEL       (* (reg8 *) TXCAN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TXCAN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TXCAN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TXCAN_PRTDSI__OE_SEL0        (* (reg8 *) TXCAN__PRTDSI__OE_SEL0) 
#define TXCAN_PRTDSI__OE_SEL1        (* (reg8 *) TXCAN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TXCAN_PRTDSI__OUT_SEL0       (* (reg8 *) TXCAN__PRTDSI__OUT_SEL0) 
#define TXCAN_PRTDSI__OUT_SEL1       (* (reg8 *) TXCAN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TXCAN_PRTDSI__SYNC_OUT       (* (reg8 *) TXCAN__PRTDSI__SYNC_OUT) 


#if defined(TXCAN__INTSTAT)  /* Interrupt Registers */

    #define TXCAN_INTSTAT                (* (reg8 *) TXCAN__INTSTAT)
    #define TXCAN_SNAP                   (* (reg8 *) TXCAN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TXCAN_H */


/* [] END OF FILE */
