/*******************************************************************************
* File Name: USB2UART_cls.c
* Version 2.80
*
* Description:
*  USB Class request handler.
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

#if(USB2UART_EXTERN_CLS == USB2UART_FALSE)

#include "USB2UART_pvt.h"


/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB2UART_DispatchClassRqst
********************************************************************************
* Summary:
*  This routine dispatches class specific requests depend on interface class.
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
uint8 USB2UART_DispatchClassRqst(void) 
{
    uint8 requestHandled USB2UART_FALSE;
    uint8 interfaceNumber 0u;

    switch(CY_GET_REG8(USB2UART_bmRequestType) & USB2UART_RQST_RCPT_MASK)
    {
        case USB2UART_RQST_RCPT_IFC:        /* Class-specific request directed to an interface */
            interfaceNumber CY_GET_REG8(USB2UART_wIndexLo); /* wIndexLo contain Interface number */
            break;
        case USB2UART_RQST_RCPT_EP:         /* Class-specific request directed to the endpoint */
            /* Find related interface to the endpoint, wIndexLo contain EP number */
            interfaceNumber USB2UART_EP[CY_GET_REG8(USB2UART_wIndexLo) &
                              USB2UART_DIR_UNUSED].interface;
            break;
        default:    /* RequestHandled is initialized as FALSE by default */
            break;
    }
    /* Handle Class request depend on interface type */
    switch(USB2UART_interfaceClass[interfaceNumber])
    {
        case USB2UART_CLASS_HID:
            #if defined(USB2UART_ENABLE_HID_CLASS)
                requestHandled USB2UART_DispatchHIDClassRqst();
            #endif /* USB2UART_ENABLE_HID_CLASS */
            break;
        case USB2UART_CLASS_AUDIO:
            #if defined(USB2UART_ENABLE_AUDIO_CLASS)
                requestHandled USB2UART_DispatchAUDIOClassRqst();
            #endif /* USB2UART_CLASS_AUDIO */
            break;
        case USB2UART_CLASS_CDC:
            #if defined(USB2UART_ENABLE_CDC_CLASS)
                requestHandled USB2UART_DispatchCDCClassRqst();
            #endif /* USB2UART_ENABLE_CDC_CLASS */
            break;
        default:    /* requestHandled is initialized as FALSE by default */
            break;
    }

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USB2UART_EXTERN_CLS */


/* [] END OF FILE */
