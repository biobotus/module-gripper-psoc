/*******************************************************************************
* File Name: USB2UART_drv.c
* Version 2.80
*
* Description:
*  Endpoint 0 Driver for the USBFS Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB2UART.h"
#include "USB2UART_pvt.h"


/***************************************
* Global data allocation
***************************************/

volatile T_USB2UART_EP_CTL_BLOCK USB2UART_EP[USB2UART_MAX_EP];
volatile uint8 USB2UART_configuration;
volatile uint8 USB2UART_interfaceNumber;
volatile uint8 USB2UART_configurationChanged;
volatile uint8 USB2UART_deviceAddress;
volatile uint8 USB2UART_deviceStatus;
volatile uint8 USB2UART_interfaceSetting[USB2UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB2UART_interfaceSetting_last[USB2UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB2UART_interfaceStatus[USB2UART_MAX_INTERFACES_NUMBER];
volatile uint8 USB2UART_device;
const uint8 CYCODE *USB2UART_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 USB2UART_ep0Toggle;
volatile uint8 USB2UART_lastPacketSize;
volatile uint8 USB2UART_transferState;
volatile T_USB2UART_TD USB2UART_currentTD;
volatile uint8 USB2UART_ep0Mode;
volatile uint8 USB2UART_ep0Count;
volatile uint16 USB2UART_transferByteCount;


/*******************************************************************************
* Function Name: USB2UART_ep_0_Interrupt
********************************************************************************
*
* Summary:
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USB2UART_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;


    bRegTemp CY_GET_REG8(USB2UART_EP0_CR_PTR);
    if ((bRegTemp & USB2UART_MODE_ACKD) != 0u)
    {
        modifyReg 1u;
        if ((bRegTemp & USB2UART_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & USB2UART_MODE_MASK) != USB2UART_MODE_NAK_IN_OUT)
            {
                modifyReg 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                USB2UART_HandleSetup();
                if((USB2UART_ep0Mode & USB2UART_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & USB2UART_MODE_IN_RCVD) != 0u)
        {
            USB2UART_HandleIN();
        }
        else if ((bRegTemp & USB2UART_MODE_OUT_RCVD) != 0u)
        {
            USB2UART_HandleOUT();
        }
        else
        {
            modifyReg 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp CY_GET_REG8(USB2UART_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & USB2UART_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp USB2UART_ep0Toggle | USB2UART_ep0Count;
                CY_SET_REG8(USB2UART_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(USB2UART_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg USB2UART_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp CY_GET_REG8(USB2UART_EP0_CR_PTR) & USB2UART_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(USB2UART_EP0_CR_PTR, USB2UART_ep0Mode);
                            /* Writing check */
                            modifyReg CY_GET_REG8(USB2UART_EP0_CR_PTR) & USB2UART_MODE_MASK;
                        }
                    }while(modifyReg != USB2UART_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: USB2UART_HandleSetup
********************************************************************************
*
* Summary:
*  This Routine dispatches requests for the four USB request types
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
void USB2UART_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled CY_GET_REG8(USB2UART_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(USB2UART_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled CY_GET_REG8(USB2UART_EP0_CR_PTR);      /* reread register */
    if((requestHandled & USB2UART_MODE_SETUP_RCVD) != 0u)
    {
        USB2UART_ep0Mode requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        USB2UART_UpdateStatusBlock(USB2UART_XFER_PREMATURE);

        switch (CY_GET_REG8(USB2UART_bmRequestType) & USB2UART_RQST_TYPE_MASK)
        {
            case USB2UART_RQST_TYPE_STD:
                requestHandled USB2UART_HandleStandardRqst();
                break;
            case USB2UART_RQST_TYPE_CLS:
                requestHandled USB2UART_DispatchClassRqst();
                break;
            case USB2UART_RQST_TYPE_VND:
                requestHandled USB2UART_HandleVendorRqst();
                break;
            default:
                requestHandled USB2UART_FALSE;
                break;
        }
        if (requestHandled == USB2UART_FALSE)
        {
            USB2UART_ep0Mode USB2UART_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USB2UART_HandleIN
********************************************************************************
*
* Summary:
*  This routine handles EP0 IN transfers.
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
void USB2UART_HandleIN(void) 
{
    switch (USB2UART_transferState)
    {
        case USB2UART_TRANS_STATE_IDLE:
            break;
        case USB2UART_TRANS_STATE_CONTROL_READ:
            USB2UART_ControlReadDataStage();
            break;
        case USB2UART_TRANS_STATE_CONTROL_WRITE:
            USB2UART_ControlWriteStatusStage();
            break;
        case USB2UART_TRANS_STATE_NO_DATA_CONTROL:
            USB2UART_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB2UART_HandleOUT
********************************************************************************
*
* Summary:
*  This routine handles EP0 OUT transfers.
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
void USB2UART_HandleOUT(void) 
{
    switch (USB2UART_transferState)
    {
        case USB2UART_TRANS_STATE_IDLE:
            break;
        case USB2UART_TRANS_STATE_CONTROL_READ:
            USB2UART_ControlReadStatusStage();
            break;
        case USB2UART_TRANS_STATE_CONTROL_WRITE:
            USB2UART_ControlWriteDataStage();
            break;
        case USB2UART_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            USB2UART_UpdateStatusBlock(USB2UART_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            USB2UART_ep0Mode USB2UART_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USB2UART_LoadEP0
********************************************************************************
*
* Summary:
*  This routine loads the EP0 data registers for OUT transfers.  It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  USB2UART_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  USB2UART_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  USB2UART_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  USB2UART_ep0Toggle - inverted
*  USB2UART_ep0Mode  - prepare for mode register content.
*  USB2UART_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_LoadEP0(void) 
{
    uint8 ep0Count 0u;

    /* Update the transfer byte count from the last transaction */
    USB2UART_transferByteCount += USB2UART_lastPacketSize;
    /* Now load the next transaction */
    while ((USB2UART_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(USB2UART_EP0_DR0_IND + ep0Count), *USB2UART_currentTD.pData);
        USB2UART_currentTD.pData &USB2UART_currentTD.pData[1u];
        ep0Count++;
        USB2UART_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (USB2UART_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        USB2UART_ep0Toggle ^= USB2UART_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        USB2UART_ep0Mode USB2UART_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        USB2UART_transferState USB2UART_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        USB2UART_ep0Mode USB2UART_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        USB2UART_transferState USB2UART_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    USB2UART_lastPacketSize ep0Count;
    USB2UART_ep0Count ep0Count;
}


/*******************************************************************************
* Function Name: USB2UART_InitControlRead
********************************************************************************
*
* Summary:
*  Initialize a control read transaction, usable to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB2UART_currentTD.count - counts of data to be sent.
*  USB2UART_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_InitControlRead(void) 
{
    uint16 xferCount;
    if(USB2UART_currentTD.count == 0u)
    {
        (void) USB2UART_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        USB2UART_transferState USB2UART_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        USB2UART_ep0Toggle 0u;
        /* Initialize the Status Block */
        USB2UART_InitializeStatusBlock();
        xferCount (((uint16)CY_GET_REG8(USB2UART_lengthHi) << 8u) | (CY_GET_REG8(USB2UART_lengthLo)));

        if (USB2UART_currentTD.count > xferCount)
        {
            USB2UART_currentTD.count xferCount;
        }
        USB2UART_LoadEP0();
    }

    return(USB2UART_TRUE);
}


/*******************************************************************************
* Function Name: USB2UART_InitZeroLengthControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a zero length data IN transfer.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB2UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB2UART_ep0Mode  - prepare for mode register content.
*  USB2UART_transferState - set to TRANS_STATE_CONTROL_READ
*  USB2UART_ep0Count - cleared, means the zero-length packet.
*  USB2UART_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    USB2UART_transferState USB2UART_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    USB2UART_ep0Toggle USB2UART_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    USB2UART_ep0Mode USB2UART_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    USB2UART_lastPacketSize 0u;
    USB2UART_ep0Count 0u;

    return(USB2UART_TRUE);
}


/*******************************************************************************
* Function Name: USB2UART_ControlReadDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control read transfer.
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
void USB2UART_ControlReadDataStage(void) 

{
    USB2UART_LoadEP0();
}


/*******************************************************************************
* Function Name: USB2UART_ControlReadStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_USBFS_transferByteCount - updated with last packet size.
*  USB2UART_transferState - set to TRANS_STATE_IDLE.
*  USB2UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    USB2UART_transferByteCount += USB2UART_lastPacketSize;
    /* Go Idle */
    USB2UART_transferState USB2UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB2UART_UpdateStatusBlock(USB2UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB2UART_ep0Mode  USB2UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB2UART_InitControlWrite
********************************************************************************
*
* Summary:
*  Initialize a control write transaction
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB2UART_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  USB2UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB2UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    USB2UART_transferState USB2UART_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    USB2UART_ep0Toggle USB2UART_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    USB2UART_InitializeStatusBlock();

    xferCount (((uint16)CY_GET_REG8(USB2UART_lengthHi) << 8u) | (CY_GET_REG8(USB2UART_lengthLo)));

    if (USB2UART_currentTD.count > xferCount)
    {
        USB2UART_currentTD.count xferCount;
    }

    /* Expect Data or Status Stage */
    USB2UART_ep0Mode USB2UART_MODE_ACK_OUT_STATUS_IN;

    return(USB2UART_TRUE);
}


/*******************************************************************************
* Function Name: USB2UART_ControlWriteDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  USB2UART_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  USB2UART_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  USB2UART_ep0Toggle - inverted
*  USB2UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex 0u;

    ep0Count (CY_GET_REG8(USB2UART_EP0_CNT_PTR) & USB2UART_EPX_CNT0_MASK) -
               USB2UART_EPX_CNTX_CRC_COUNT;

    USB2UART_transferByteCount += ep0Count;

    while ((USB2UART_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *USB2UART_currentTD.pData CY_GET_REG8((reg8 *)(USB2UART_EP0_DR0_IND + regIndex));
        USB2UART_currentTD.pData &USB2UART_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        USB2UART_currentTD.count--;
    }
    USB2UART_ep0Count ep0Count;
    /* Update the data toggle */
    USB2UART_ep0Toggle ^= USB2UART_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    USB2UART_ep0Mode USB2UART_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: USB2UART_ControlWriteStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control write transfer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_transferState - set to TRANS_STATE_IDLE.
*  USB2UART_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    USB2UART_transferState USB2UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB2UART_UpdateStatusBlock(USB2UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    USB2UART_ep0Mode USB2UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB2UART_InitNoDataControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a no data control transfer
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  USB2UART_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  USB2UART_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  USB2UART_ep0Count - cleared.
*  USB2UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_InitNoDataControlTransfer(void) 
{
    USB2UART_transferState USB2UART_TRANS_STATE_NO_DATA_CONTROL;
    USB2UART_ep0Mode USB2UART_MODE_STATUS_IN_ONLY;
    USB2UART_ep0Toggle USB2UART_EP0_CNT_DATA_TOGGLE;
    USB2UART_ep0Count 0u;

    return(USB2UART_TRUE);
}


/*******************************************************************************
* Function Name: USB2UART_NoDataControlStatusStage
********************************************************************************
* Summary:
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_transferState - set to TRANS_STATE_IDLE.
*  USB2UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*  USB2UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USB2UART_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (USB2UART_deviceAddress != 0u)
    {
        CY_SET_REG8(USB2UART_CR0_PTR, USB2UART_deviceAddress | USB2UART_CR0_ENABLE);
        USB2UART_deviceAddress 0u;
    }
    /* Go Idle */
    USB2UART_transferState USB2UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    USB2UART_UpdateStatusBlock(USB2UART_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    USB2UART_ep0Mode USB2UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USB2UART_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the USB2UART_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  USB2UART_currentTD.pStatusBlock->length - updated.
*  USB2UART_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_UpdateStatusBlock(uint8 completionCode) 
{
    if (USB2UART_currentTD.pStatusBlock != NULL)
    {
        USB2UART_currentTD.pStatusBlock->status completionCode;
        USB2UART_currentTD.pStatusBlock->length USB2UART_transferByteCount;
        USB2UART_currentTD.pStatusBlock NULL;
    }
}


/*******************************************************************************
* Function Name: USB2UART_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes USB2UART_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB2UART_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  USB2UART_currentTD.pStatusBlock->length - cleared.
*  USB2UART_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB2UART_InitializeStatusBlock(void) 
{
    USB2UART_transferByteCount 0u;
    if(USB2UART_currentTD.pStatusBlock != NULL)
    {
        USB2UART_currentTD.pStatusBlock->status USB2UART_XFER_IDLE;
        USB2UART_currentTD.pStatusBlock->length 0u;
    }
}


/* [] END OF FILE */
