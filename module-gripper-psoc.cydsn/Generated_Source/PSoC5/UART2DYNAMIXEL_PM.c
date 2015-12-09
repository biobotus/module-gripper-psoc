/*******************************************************************************
* File Name: UART2DYNAMIXEL_PM.c
* Version 2.50
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

#include "UART2DYNAMIXEL.h"


/***************************************
* Local data allocation
***************************************/

static UART2DYNAMIXEL_BACKUP_STRUCT  UART2DYNAMIXEL_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART2DYNAMIXEL_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the UART2DYNAMIXEL_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2DYNAMIXEL_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2DYNAMIXEL_SaveConfig(void)
{
    #if(UART2DYNAMIXEL_CONTROL_REG_REMOVED == 0u)
        UART2DYNAMIXEL_backup.cr = UART2DYNAMIXEL_CONTROL_REG;
    #endif /* End UART2DYNAMIXEL_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2DYNAMIXEL_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2DYNAMIXEL_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling UART2DYNAMIXEL_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void UART2DYNAMIXEL_RestoreConfig(void)
{
    #if(UART2DYNAMIXEL_CONTROL_REG_REMOVED == 0u)
        UART2DYNAMIXEL_CONTROL_REG = UART2DYNAMIXEL_backup.cr;
    #endif /* End UART2DYNAMIXEL_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2DYNAMIXEL_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART2DYNAMIXEL_Sleep() API saves the current component state. Then it
*  calls the UART2DYNAMIXEL_Stop() function and calls 
*  UART2DYNAMIXEL_SaveConfig() to save the hardware configuration.
*  Call the UART2DYNAMIXEL_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2DYNAMIXEL_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2DYNAMIXEL_Sleep(void)
{
    #if(UART2DYNAMIXEL_RX_ENABLED || UART2DYNAMIXEL_HD_ENABLED)
        if((UART2DYNAMIXEL_RXSTATUS_ACTL_REG  & UART2DYNAMIXEL_INT_ENABLE) != 0u)
        {
            UART2DYNAMIXEL_backup.enableState = 1u;
        }
        else
        {
            UART2DYNAMIXEL_backup.enableState = 0u;
        }
    #else
        if((UART2DYNAMIXEL_TXSTATUS_ACTL_REG  & UART2DYNAMIXEL_INT_ENABLE) !=0u)
        {
            UART2DYNAMIXEL_backup.enableState = 1u;
        }
        else
        {
            UART2DYNAMIXEL_backup.enableState = 0u;
        }
    #endif /* End UART2DYNAMIXEL_RX_ENABLED || UART2DYNAMIXEL_HD_ENABLED*/

    UART2DYNAMIXEL_Stop();
    UART2DYNAMIXEL_SaveConfig();
}


/*******************************************************************************
* Function Name: UART2DYNAMIXEL_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART2DYNAMIXEL_Sleep() was called. The UART2DYNAMIXEL_Wakeup() function
*  calls the UART2DYNAMIXEL_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART2DYNAMIXEL_Sleep() function was called, the UART2DYNAMIXEL_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2DYNAMIXEL_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2DYNAMIXEL_Wakeup(void)
{
    UART2DYNAMIXEL_RestoreConfig();
    #if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
        UART2DYNAMIXEL_ClearRxBuffer();
    #endif /* End (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */
    #if(UART2DYNAMIXEL_TX_ENABLED || UART2DYNAMIXEL_HD_ENABLED)
        UART2DYNAMIXEL_ClearTxBuffer();
    #endif /* End UART2DYNAMIXEL_TX_ENABLED || UART2DYNAMIXEL_HD_ENABLED */

    if(UART2DYNAMIXEL_backup.enableState != 0u)
    {
        UART2DYNAMIXEL_Enable();
    }
}


/* [] END OF FILE */
