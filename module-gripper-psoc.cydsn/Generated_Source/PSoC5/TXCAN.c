/*******************************************************************************
* File Name: TXCAN.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "TXCAN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TXCAN__PORT == 15 && ((TXCAN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TXCAN_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void TXCAN_Write(uint8 value) 
{
    uint8 staticBits = (TXCAN_DR & (uint8)(~TXCAN_MASK));
    TXCAN_DR = staticBits | ((uint8)(value << TXCAN_SHIFT) & TXCAN_MASK);
}


/*******************************************************************************
* Function Name: TXCAN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TXCAN_DM_STRONG     Strong Drive 
*  TXCAN_DM_OD_HI      Open Drain, Drives High 
*  TXCAN_DM_OD_LO      Open Drain, Drives Low 
*  TXCAN_DM_RES_UP     Resistive Pull Up 
*  TXCAN_DM_RES_DWN    Resistive Pull Down 
*  TXCAN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TXCAN_DM_DIG_HIZ    High Impedance Digital 
*  TXCAN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TXCAN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TXCAN_0, mode);
}


/*******************************************************************************
* Function Name: TXCAN_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro TXCAN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TXCAN_Read(void) 
{
    return (TXCAN_PS & TXCAN_MASK) >> TXCAN_SHIFT;
}


/*******************************************************************************
* Function Name: TXCAN_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 TXCAN_ReadDataReg(void) 
{
    return (TXCAN_DR & TXCAN_MASK) >> TXCAN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TXCAN_INTSTAT) 

    /*******************************************************************************
    * Function Name: TXCAN_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 TXCAN_ClearInterrupt(void) 
    {
        return (TXCAN_INTSTAT & TXCAN_MASK) >> TXCAN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
