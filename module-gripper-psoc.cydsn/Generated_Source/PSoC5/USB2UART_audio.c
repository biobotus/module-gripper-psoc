/*******************************************************************************
* File Name: USB2UART_audio.c
* Version 2.80
*
* Description:
*  USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB2UART.h"

#if defined(USB2UART_ENABLE_AUDIO_CLASS)

#include "USB2UART_audio.h"
#include "USB2UART_pvt.h"
#if defined(USB2UART_ENABLE_MIDI_STREAMING)
    #include "USB2UART_midi.h"
#endif /*  USB2UART_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(USB2UART_ENABLE_AUDIO_STREAMING)
    volatile uint8 USB2UART_currentSampleFrequency[USB2UART_MAX_EP][USB2UART_SAMPLE_FREQ_LEN];
    volatile uint8 USB2UART_frequencyChanged;
    volatile uint8 USB2UART_currentMute;
    volatile uint8 USB2UART_currentVolume[USB2UART_VOLUME_LEN];
    volatile uint8 USB2UART_minimumVolume[USB2UART_VOLUME_LEN] {USB2UART_VOL_MIN_LSB,
                                                                                  USB2UART_VOL_MIN_MSB};
    volatile uint8 USB2UART_maximumVolume[USB2UART_VOLUME_LEN] {USB2UART_VOL_MAX_LSB,
                                                                                  USB2UART_VOL_MAX_MSB};
    volatile uint8 USB2UART_resolutionVolume[USB2UART_VOLUME_LEN] {USB2UART_VOL_RES_LSB,
                                                                                     USB2UART_VOL_RES_MSB};
#endif /*  USB2UART_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: USB2UART_DispatchAUDIOClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches class requests
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   USB2UART_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   USB2UART_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((USB2UART_frequencyChanged != 0) &&
*       (USB2UART_transferState == USB2UART_TRANS_STATE_IDLE))
*       {
*          USB2UART_frequencyChanged 0;
*       }
*       USB2UART_transferState variable is checked to be sure that
*             transfer completes.
*   USB2UART_currentMute: Contains mute configuration set by Host.
*   USB2UART_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB2UART_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled USB2UART_FALSE;
    uint8 bmRequestType  CY_GET_REG8(USB2UART_bmRequestType);

    #if defined(USB2UART_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber CY_GET_REG8(USB2UART_wIndexLo) & USB2UART_DIR_UNUSED;
    #endif /*  USB2UART_ENABLE_AUDIO_STREAMING */


    if ((bmRequestType & USB2UART_RQST_DIR_MASK) == USB2UART_RQST_DIR_D2H)
    {
        /* Control Read */
        if((bmRequestType & USB2UART_RQST_RCPT_MASK) == USB2UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(USB2UART_bRequest))
            {
                case USB2UART_GET_CUR:
                #if defined(USB2UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB2UART_currentTD.wCount USB2UART_SAMPLE_FREQ_LEN;
                        USB2UART_currentTD.pData  USB2UART_currentSampleFrequency[epNumber];
                        requestHandled   USB2UART_InitControlRead();
                    }
                #endif /*  USB2UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & USB2UART_RQST_RCPT_MASK) == USB2UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB2UART_bRequest))
            {
                case USB2UART_GET_CUR:
                #if defined(USB2UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                         /* Entity ID Control Selector is MUTE */
                        USB2UART_currentTD.wCount 1u;
                        USB2UART_currentTD.pData  &USB2UART_currentMute;
                        requestHandled   USB2UART_InitControlRead();
                    }
                    else if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME, */
                        USB2UART_currentTD.wCount USB2UART_VOLUME_LEN;
                        USB2UART_currentTD.pData  USB2UART_currentVolume;
                        requestHandled   USB2UART_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                    break;
                case USB2UART_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB2UART_currentTD.wCount USB2UART_VOLUME_LEN;
                        USB2UART_currentTD.pData  &USB2UART_minimumVolume[0];
                        requestHandled   USB2UART_InitControlRead();
                    }
                    break;
                case USB2UART_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB2UART_currentTD.wCount USB2UART_VOLUME_LEN;
                        USB2UART_currentTD.pData  &USB2UART_maximumVolume[0];
                        requestHandled   USB2UART_InitControlRead();
                    }
                    break;
                case USB2UART_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        USB2UART_currentTD.wCount USB2UART_VOLUME_LEN;
                        USB2UART_currentTD.pData  &USB2UART_resolutionVolume[0];
                        requestHandled   USB2UART_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case USB2UART_GET_STAT:
                        USB2UART_currentTD.wCount 0u;
                        requestHandled   USB2UART_InitControlWrite();

                #endif /*  USB2UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* USB2UART_RQST_RCPT_OTHER */
        }
    }
    else
    {
        /* Control Write */
        if((bmRequestType & USB2UART_RQST_RCPT_MASK) == USB2UART_RQST_RCPT_EP)
        {
            /* point */
            switch (CY_GET_REG8(USB2UART_bRequest))
            {
                case USB2UART_SET_CUR:
                #if defined(USB2UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB2UART_currentTD.wCount USB2UART_SAMPLE_FREQ_LEN;
                        USB2UART_currentTD.pData  USB2UART_currentSampleFrequency[epNumber];
                        requestHandled   USB2UART_InitControlWrite();
                        USB2UART_frequencyChanged epNumber;
                    }
                #endif /*  USB2UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((bmRequestType & USB2UART_RQST_RCPT_MASK) == USB2UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(USB2UART_bRequest))
            {
                case USB2UART_SET_CUR:
                #if defined(USB2UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is MUTE */
                        USB2UART_currentTD.wCount 1u;
                        USB2UART_currentTD.pData  &USB2UART_currentMute;
                        requestHandled   USB2UART_InitControlWrite();
                    }
                    else if(CY_GET_REG8(USB2UART_wValueHi) == USB2UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME */
                        USB2UART_currentTD.wCount USB2UART_VOLUME_LEN;
                        USB2UART_currentTD.pData  USB2UART_currentVolume;
                        requestHandled   USB2UART_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                #endif /*  USB2UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {
            /* USB2UART_RQST_RCPT_OTHER */
        }
    }

    return(requestHandled);
}

#endif /* USER_SUPPLIED_AUDIO_HANDLER */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  USB2UART_ENABLE_AUDIO_CLASS */


/* [] END OF FILE */
