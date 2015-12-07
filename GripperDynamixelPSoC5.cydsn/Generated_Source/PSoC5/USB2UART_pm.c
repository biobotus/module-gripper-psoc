/*******************************************************************************
* File Name: USB2UART_pm.c
* Version 2.80
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "project.h"
#include "USB2UART.h"
#include "USB2UART_pvt.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static USB2UART_BACKUP_STRUCT  USB2UART_backup;


#if(USB2UART_DP_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB2UART_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB2UART_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(USB2UART_DP_INTSTAT_PTR);
    }

#endif /* (USB2UART_DP_ISR_REMOVE == 0u) */


/*******************************************************************************
* Function Name: USB2UART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: USB2UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_RestoreConfig(void) 
{
    if(USB2UART_configuration != 0u)
    {
        USB2UART_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: USB2UART_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power down mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  USB2UART_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_Suspend(void) 
{
    uint8 enableInterrupts;
    enableInterrupts CyEnterCriticalSection();

    if((CY_GET_REG8(USB2UART_CR0_PTR) & USB2UART_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        USB2UART_backup.enableState 1u;

        #if(USB2UART_EP_MM != USB2UART__EP_MANUAL)
            USB2UART_Stop_DMA(USB2UART_MAX_EP);     /* Stop all DMAs */
        #endif   /*  USB2UART_EP_MM != USB2UART__EP_MANUAL */

        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        USB2UART_USBIO_CR0_REG &= (uint8)~USB2UART_USBIO_CR0_TEN;
        CyDelayUs(0u);  /*~50ns delay */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        USB2UART_PM_USB_CR0_REG &=
                                (uint8)~(USB2UART_PM_USB_CR0_PD_N | USB2UART_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE */
        USB2UART_CR0_REG &= (uint8)~USB2UART_CR0_ENABLE;

        CyDelayUs(0u);  /* ~50ns delay */
        /* Store mode and Disable VRegulator*/
        USB2UART_backup.mode USB2UART_CR1_REG & USB2UART_CR1_REG_ENABLE;
        USB2UART_CR1_REG &= (uint8)~USB2UART_CR1_REG_ENABLE;

        CyDelayUs(1u);  /* 0.5 us min delay */
        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USB2UART_PM_USB_CR0_REG &= (uint8)~USB2UART_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
        USB2UART_USBIO_CR1_REG |= USB2UART_USBIO_CR1_IOMODE;

        /* Disable USB in ACT PM */
        USB2UART_PM_ACT_CFG_REG &= (uint8)~USB2UART_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        USB2UART_PM_STBY_CFG_REG &= (uint8)~USB2UART_PM_STBY_EN_FSUSB;
        CyDelayUs(1u); /* min  0.5us delay required */

    }
    else
    {
        USB2UART_backup.enableState 0u;
    }

    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if(USB2UART_DP_ISR_REMOVE == 0u)
        (void) CyIntSetVector(USB2UART_DP_INTC_VECT_NUM, &USB2UART_DP_ISR);
        CyIntSetPriority(USB2UART_DP_INTC_VECT_NUM, USB2UART_DP_INTC_PRIOR);
        CyIntClearPending(USB2UART_DP_INTC_VECT_NUM);
        CyIntEnable(USB2UART_DP_INTC_VECT_NUM);
    #endif /* (USB2UART_DP_ISR_REMOVE == 0u) */
}


/*******************************************************************************
* Function Name: USB2UART_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_Resume(void) 
{
    uint8 enableInterrupts;
    enableInterrupts CyEnterCriticalSection();

    if(USB2UART_backup.enableState != 0u)
    {
        #if(USB2UART_DP_ISR_REMOVE == 0u)
            CyIntDisable(USB2UART_DP_INTC_VECT_NUM);
        #endif /*  USB2UART_DP_ISR_REMOVE */

        /* Enable USB block */
        USB2UART_PM_ACT_CFG_REG |= USB2UART_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        USB2UART_PM_STBY_CFG_REG |= USB2UART_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        USB2UART_USB_CLK_EN_REG |= USB2UART_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USB2UART_PM_USB_CR0_REG |= USB2UART_PM_USB_CR0_REF_EN;
        /* The reference will be available ~40us after power restored */
        CyDelayUs(40u);
        /* Return VRegulator*/
        USB2UART_CR1_REG |= USB2UART_backup.mode;
        CyDelayUs(0u);  /*~50ns delay */
        /* Enable USBIO */
        USB2UART_PM_USB_CR0_REG |= USB2UART_PM_USB_CR0_PD_N;
        CyDelayUs(2u);
        /* Set the USBIO pull-up enable */
        USB2UART_PM_USB_CR0_REG |= USB2UART_PM_USB_CR0_PD_PULLUP_N;

        /* Re-init Arbiter configuration for DMA transfers */
        #if(USB2UART_EP_MM != USB2UART__EP_MANUAL)
            /* Usb arb interrupt enable */
            USB2UART_ARB_INT_EN_REG USB2UART_ARB_INT_MASK;
            #if(USB2UART_EP_MM == USB2UART__EP_DMAMANUAL)
                USB2UART_ARB_CFG_REG USB2UART_ARB_CFG_MANUAL_DMA;
            #endif   /*  USB2UART_EP_MM == USB2UART__EP_DMAMANUAL */
            #if(USB2UART_EP_MM == USB2UART__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                USB2UART_ARB_CFG_REG USB2UART_ARB_CFG_AUTO_DMA | USB2UART_ARB_CFG_AUTO_MEM;
            #endif   /*  USB2UART_EP_MM == USB2UART__EP_DMAAUTO */
        #endif   /*  USB2UART_EP_MM != USB2UART__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(USB2UART_EP0_CR_PTR, USB2UART_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        USB2UART_CR0_REG |= USB2UART_CR0_ENABLE;
        CyDelayCycles(1u);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(USB2UART_USBIO_CR1_PTR, USB2UART_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        USB2UART_RestoreConfig();
    }

    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
