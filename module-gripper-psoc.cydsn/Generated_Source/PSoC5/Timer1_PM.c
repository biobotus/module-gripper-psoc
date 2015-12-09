/*******************************************************************************
* File Name: Timer1_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer1.h"

static Timer1_backupStruct Timer1_backup;


/*******************************************************************************
* Function Name: Timer1_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer1_SaveConfig(void) 
{
    #if (!Timer1_UsingFixedFunction)
        Timer1_backup.TimerUdb = Timer1_ReadCounter();
        Timer1_backup.InterruptMaskValue = Timer1_STATUS_MASK;
        #if (Timer1_UsingHWCaptureCounter)
            Timer1_backup.TimerCaptureCounter = Timer1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer1_UDB_CONTROL_REG_REMOVED)
            Timer1_backup.TimerControlRegister = Timer1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer1_RestoreConfig(void) 
{   
    #if (!Timer1_UsingFixedFunction)

        Timer1_WriteCounter(Timer1_backup.TimerUdb);
        Timer1_STATUS_MASK =Timer1_backup.InterruptMaskValue;
        #if (Timer1_UsingHWCaptureCounter)
            Timer1_SetCaptureCount(Timer1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer1_UDB_CONTROL_REG_REMOVED)
            Timer1_WriteControlRegister(Timer1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer1_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer1_Sleep(void) 
{
    #if(!Timer1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer1_CTRL_ENABLE == (Timer1_CONTROL & Timer1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer1_Stop();
    Timer1_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer1_Wakeup(void) 
{
    Timer1_RestoreConfig();
    #if(!Timer1_UDB_CONTROL_REG_REMOVED)
        if(Timer1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
