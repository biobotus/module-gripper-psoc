/*******************************************************************************
* File Name: RXCAN.h  
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

#if !defined(CY_PINS_RXCAN_H) /* Pins RXCAN_H */
#define CY_PINS_RXCAN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RXCAN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RXCAN__PORT == 15 && ((RXCAN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RXCAN_Write(uint8 value) ;
void    RXCAN_SetDriveMode(uint8 mode) ;
uint8   RXCAN_ReadDataReg(void) ;
uint8   RXCAN_Read(void) ;
uint8   RXCAN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RXCAN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RXCAN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RXCAN_DM_RES_UP          PIN_DM_RES_UP
#define RXCAN_DM_RES_DWN         PIN_DM_RES_DWN
#define RXCAN_DM_OD_LO           PIN_DM_OD_LO
#define RXCAN_DM_OD_HI           PIN_DM_OD_HI
#define RXCAN_DM_STRONG          PIN_DM_STRONG
#define RXCAN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RXCAN_MASK               RXCAN__MASK
#define RXCAN_SHIFT              RXCAN__SHIFT
#define RXCAN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RXCAN_PS                     (* (reg8 *) RXCAN__PS)
/* Data Register */
#define RXCAN_DR                     (* (reg8 *) RXCAN__DR)
/* Port Number */
#define RXCAN_PRT_NUM                (* (reg8 *) RXCAN__PRT) 
/* Connect to Analog Globals */                                                  
#define RXCAN_AG                     (* (reg8 *) RXCAN__AG)                       
/* Analog MUX bux enable */
#define RXCAN_AMUX                   (* (reg8 *) RXCAN__AMUX) 
/* Bidirectional Enable */                                                        
#define RXCAN_BIE                    (* (reg8 *) RXCAN__BIE)
/* Bit-mask for Aliased Register Access */
#define RXCAN_BIT_MASK               (* (reg8 *) RXCAN__BIT_MASK)
/* Bypass Enable */
#define RXCAN_BYP                    (* (reg8 *) RXCAN__BYP)
/* Port wide control signals */                                                   
#define RXCAN_CTL                    (* (reg8 *) RXCAN__CTL)
/* Drive Modes */
#define RXCAN_DM0                    (* (reg8 *) RXCAN__DM0) 
#define RXCAN_DM1                    (* (reg8 *) RXCAN__DM1)
#define RXCAN_DM2                    (* (reg8 *) RXCAN__DM2) 
/* Input Buffer Disable Override */
#define RXCAN_INP_DIS                (* (reg8 *) RXCAN__INP_DIS)
/* LCD Common or Segment Drive */
#define RXCAN_LCD_COM_SEG            (* (reg8 *) RXCAN__LCD_COM_SEG)
/* Enable Segment LCD */
#define RXCAN_LCD_EN                 (* (reg8 *) RXCAN__LCD_EN)
/* Slew Rate Control */
#define RXCAN_SLW                    (* (reg8 *) RXCAN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RXCAN_PRTDSI__CAPS_SEL       (* (reg8 *) RXCAN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RXCAN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RXCAN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RXCAN_PRTDSI__OE_SEL0        (* (reg8 *) RXCAN__PRTDSI__OE_SEL0) 
#define RXCAN_PRTDSI__OE_SEL1        (* (reg8 *) RXCAN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RXCAN_PRTDSI__OUT_SEL0       (* (reg8 *) RXCAN__PRTDSI__OUT_SEL0) 
#define RXCAN_PRTDSI__OUT_SEL1       (* (reg8 *) RXCAN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RXCAN_PRTDSI__SYNC_OUT       (* (reg8 *) RXCAN__PRTDSI__SYNC_OUT) 


#if defined(RXCAN__INTSTAT)  /* Interrupt Registers */

    #define RXCAN_INTSTAT                (* (reg8 *) RXCAN__INTSTAT)
    #define RXCAN_SNAP                   (* (reg8 *) RXCAN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RXCAN_H */


/* [] END OF FILE */
