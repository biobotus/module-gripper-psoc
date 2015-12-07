/*******************************************************************************
* File Name: USB2UART_vnd.c
* Version 2.80
*
* Description:
*  USB vendor request handler.
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

#if(USB2UART_EXTERN_VND == USB2UART_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB2UART_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specific
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_HandleVendorRqst(void) 
{
    uint8 requestHandled USB2UART_FALSE;

    if ((CY_GET_REG8(USB2UART_bmRequestType) & USB2UART_RQST_DIR_MASK) == USB2UART_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(USB2UART_bRequest))
        {
            case USB2UART_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(USB2UART_ENABLE_MSOS_STRING)
                    USB2UART_currentTD.pData (volatile uint8 *)&USB2UART_MSOS_CONFIGURATION_DESCR[0u];
                    USB2UART_currentTD.count USB2UART_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  USB2UART_InitControlRead();
                #endif /*  USB2UART_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* USB2UART_EXTERN_VND */


/* [] END OF FILE */
