/*******************************************************************************
* File Name: Counter_CanReader_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_CanReader.h"

static Counter_CanReader_backupStruct Counter_CanReader_backup;


/*******************************************************************************
* Function Name: Counter_CanReader_SaveConfig
********************************************************************************
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
*  Counter_CanReader_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_CanReader_SaveConfig(void) 
{
    #if (!Counter_CanReader_UsingFixedFunction)

        Counter_CanReader_backup.CounterUdb = Counter_CanReader_ReadCounter();

        #if(!Counter_CanReader_ControlRegRemoved)
            Counter_CanReader_backup.CounterControlRegister = Counter_CanReader_ReadControlRegister();
        #endif /* (!Counter_CanReader_ControlRegRemoved) */

    #endif /* (!Counter_CanReader_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_CanReader_RestoreConfig
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
*  Counter_CanReader_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_CanReader_RestoreConfig(void) 
{      
    #if (!Counter_CanReader_UsingFixedFunction)

       Counter_CanReader_WriteCounter(Counter_CanReader_backup.CounterUdb);

        #if(!Counter_CanReader_ControlRegRemoved)
            Counter_CanReader_WriteControlRegister(Counter_CanReader_backup.CounterControlRegister);
        #endif /* (!Counter_CanReader_ControlRegRemoved) */

    #endif /* (!Counter_CanReader_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_CanReader_Sleep
********************************************************************************
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
*  Counter_CanReader_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_CanReader_Sleep(void) 
{
    #if(!Counter_CanReader_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_CanReader_CTRL_ENABLE == (Counter_CanReader_CONTROL & Counter_CanReader_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_CanReader_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_CanReader_backup.CounterEnableState = 0u;
        }
    #else
        Counter_CanReader_backup.CounterEnableState = 1u;
        if(Counter_CanReader_backup.CounterEnableState != 0u)
        {
            Counter_CanReader_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_CanReader_ControlRegRemoved) */
    
    Counter_CanReader_Stop();
    Counter_CanReader_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_CanReader_Wakeup
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
*  Counter_CanReader_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_CanReader_Wakeup(void) 
{
    Counter_CanReader_RestoreConfig();
    #if(!Counter_CanReader_ControlRegRemoved)
        if(Counter_CanReader_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_CanReader_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_CanReader_ControlRegRemoved) */
    
}


/* [] END OF FILE */
