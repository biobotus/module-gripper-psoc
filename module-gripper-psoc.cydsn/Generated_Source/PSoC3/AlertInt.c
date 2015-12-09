/*******************************************************************************
* File Name: AlertInt.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include <CyLib.h>
#include <AlertInt.h>

#if !defined(AlertInt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START AlertInt_intc` */
#include "FanController.h"
extern uint16   stallStatus;
extern uint16   speedStatus;
/* `#END` */


/*******************************************************************************
* Function Name: AlertInt_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_Start(void) 
{
    /* For all we know the interrupt is active. */
    AlertInt_Disable();

    /* Set the ISR to point to the AlertInt Interrupt. */
    AlertInt_SetVector(&AlertInt_Interrupt);

    /* Set the priority. */
    AlertInt_SetPriority((uint8)AlertInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    AlertInt_Enable();
}


/*******************************************************************************
* Function Name: AlertInt_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    AlertInt_Disable();

    /* Set the ISR to point to the AlertInt Interrupt. */
    AlertInt_SetVector(address);

    /* Set the priority. */
    AlertInt_SetPriority((uint8)AlertInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    AlertInt_Enable();
}


/*******************************************************************************
* Function Name: AlertInt_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_Stop(void) 
{
    /* Disable this interrupt. */
    AlertInt_Disable();
}


/*******************************************************************************
* Function Name: AlertInt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for AlertInt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(AlertInt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START AlertInt_Interrupt` */

    uint8 alertStatus;
    
    /* Determine alert source: stall or speed regulation failure (could be both) */
    alertStatus FanController_GetAlertSource();
    
    /* If stall alert, determine which fan(s) */
    if (alertStatus & 0x01)
	{
		stallStatus FanController_GetFanStallStatus();
	}
		
    /* If speed regulation failure alert, determine which fan(s) */
    if (alertStatus & 0x02)
    {
		speedStatus FanController_GetFanSpeedStatus();
	}
	
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (AlertInt__ES2_PATCH ))      
            AlertInt_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: AlertInt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling AlertInt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use AlertInt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(AlertInt_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: AlertInt_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress AlertInt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(AlertInt_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: AlertInt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling AlertInt_Start
*   or AlertInt_StartEx will override any effect this method would 
*   have had. This method should only be called after AlertInt_Start or 
*   AlertInt_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_SetPriority(uint8 priority) 
{
    *AlertInt_INTC_PRIOR priority << 5;
}


/*******************************************************************************
* Function Name: AlertInt_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 AlertInt_GetPriority(void) 
{
    uint8 priority;


    priority *AlertInt_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: AlertInt_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_Enable(void) 
{
    /* Enable the general interrupt. */
    *AlertInt_INTC_SET_EN AlertInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: AlertInt_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 AlertInt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*AlertInt_INTC_SET_EN & (uint8)AlertInt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: AlertInt_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_Disable(void) 
{
    /* Disable the general interrupt. */
    *AlertInt_INTC_CLR_EN AlertInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: AlertInt_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_SetPending(void) 
{
    *AlertInt_INTC_SET_PD AlertInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: AlertInt_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AlertInt_ClearPending(void) 
{
    *AlertInt_INTC_CLR_PD AlertInt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
