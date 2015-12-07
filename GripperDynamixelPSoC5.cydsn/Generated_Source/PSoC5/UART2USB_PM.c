/*******************************************************************************
* File Name: UART2USB_PM.c
* Version 2.40
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART2USB.h"


/***************************************
* Local data allocation
***************************************/

static UART2USB_BACKUP_STRUCT  UART2USB_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART2USB_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and nonretention registers.
*  It also saves the current component parameter values, as defined in the
*  Configure dialog or as modified by appropriate APIs. This function is called
*  by the UART2USB_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2USB_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO are saved to RAM
*
*******************************************************************************/
void UART2USB_SaveConfig(void)
{
    #if(UART2USB_CONTROL_REG_REMOVED == 0u)
        UART2USB_backup.cr UART2USB_CONTROL_REG;
    #endif /* End UART2USB_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2USB_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2USB_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Side Effects:
*  All nonretention registers except FIFO loaded from RAM. This function should
*  be called only after UART2USB_SaveConfig() is called, otherwise
*  incorrect data will be loaded into the registers.
*
*******************************************************************************/
void UART2USB_RestoreConfig(void)
{
    #if(UART2USB_CONTROL_REG_REMOVED == 0u)
        UART2USB_CONTROL_REG UART2USB_backup.cr;
    #endif /* End UART2USB_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2USB_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART2USB_Sleep() API saves the current component state. Then it
*  calls the UART2USB_Stop() function and calls 
*  UART2USB_SaveConfig() to save the hardware configuration.
*  Call the UART2USB_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2USB_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2USB_Sleep(void)
{
    #if(UART2USB_RX_ENABLED || UART2USB_HD_ENABLED)
        if((UART2USB_RXSTATUS_ACTL_REG  & UART2USB_INT_ENABLE) != 0u)
        {
            UART2USB_backup.enableState 1u;
        }
        else
        {
            UART2USB_backup.enableState 0u;
        }
    #else
        if((UART2USB_TXSTATUS_ACTL_REG  & UART2USB_INT_ENABLE) !=0u)
        {
            UART2USB_backup.enableState 1u;
        }
        else
        {
            UART2USB_backup.enableState 0u;
        }
    #endif /* End UART2USB_RX_ENABLED || UART2USB_HD_ENABLED*/

    UART2USB_Stop();
    UART2USB_SaveConfig();
}


/*******************************************************************************
* Function Name: UART2USB_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART2USB_Sleep() was called. The UART2USB_Wakeup() function
*  calls the UART2USB_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART2USB_Sleep() function was called, the UART2USB_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2USB_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2USB_Wakeup(void)
{
    UART2USB_RestoreConfig();
    #if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )
        UART2USB_ClearRxBuffer();
    #endif /* End (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */
    #if(UART2USB_TX_ENABLED || UART2USB_HD_ENABLED)
        UART2USB_ClearTxBuffer();
    #endif /* End UART2USB_TX_ENABLED || UART2USB_HD_ENABLED */

    if(UART2USB_backup.enableState != 0u)
    {
        UART2USB_Enable();
    }
}


/* [] END OF FILE */
