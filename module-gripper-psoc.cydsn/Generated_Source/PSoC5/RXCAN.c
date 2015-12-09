/*******************************************************************************
* File Name: RXCAN.c  
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
#include "RXCAN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 RXCAN__PORT == 15 && ((RXCAN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: RXCAN_Write
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
void RXCAN_Write(uint8 value) 
{
    uint8 staticBits = (RXCAN_DR & (uint8)(~RXCAN_MASK));
    RXCAN_DR = staticBits | ((uint8)(value << RXCAN_SHIFT) & RXCAN_MASK);
}


/*******************************************************************************
* Function Name: RXCAN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RXCAN_DM_STRONG     Strong Drive 
*  RXCAN_DM_OD_HI      Open Drain, Drives High 
*  RXCAN_DM_OD_LO      Open Drain, Drives Low 
*  RXCAN_DM_RES_UP     Resistive Pull Up 
*  RXCAN_DM_RES_DWN    Resistive Pull Down 
*  RXCAN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RXCAN_DM_DIG_HIZ    High Impedance Digital 
*  RXCAN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RXCAN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RXCAN_0, mode);
}


/*******************************************************************************
* Function Name: RXCAN_Read
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
*  Macro RXCAN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RXCAN_Read(void) 
{
    return (RXCAN_PS & RXCAN_MASK) >> RXCAN_SHIFT;
}


/*******************************************************************************
* Function Name: RXCAN_ReadDataReg
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
uint8 RXCAN_ReadDataReg(void) 
{
    return (RXCAN_DR & RXCAN_MASK) >> RXCAN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RXCAN_INTSTAT) 

    /*******************************************************************************
    * Function Name: RXCAN_ClearInterrupt
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
    uint8 RXCAN_ClearInterrupt(void) 
    {
        return (RXCAN_INTSTAT & RXCAN_MASK) >> RXCAN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
