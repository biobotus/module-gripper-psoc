/*******************************************************************************
* File Name: USB2UART_midi.h
* Version 2.80
*
* Description:
*  Header File for the USBFS MIDI module.
*  Contains prototypes and constant values.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
*  MIDI 1.0 Detailed Specification Document Version 4.2
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB2UART_midi_H)
#define CY_USBFS_USB2UART_midi_H

#include "cytypes.h"
#include "USB2UART.h"


/***************************************
*    Data Structure Definition
***************************************/

/* The following structure is used to hold status information for
   building and parsing incoming MIDI messages. */
typedef struct
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4];    /* message buffer */
} USB2UART_MIDI_RX_STATUS;


/***************************************
*           MIDI Constants.
***************************************/

#define USB2UART_ONE_EXT_INTRF              (0x01u)
#define USB2UART_TWO_EXT_INTRF              (0x02u)

/* Flag definitions for use with MIDI device inquiry */
#define USB2UART_INQ_SYSEX_FLAG             (0x01u)
#define USB2UART_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define USB2UART_CIN_MASK                   (0x0Fu)
#define USB2UART_RESERVED0                  (0x00u)
#define USB2UART_RESERVED1                  (0x01u)
#define USB2UART_2BYTE_COMMON               (0x02u)
#define USB2UART_3BYTE_COMMON               (0x03u)
#define USB2UART_SYSEX                      (0x04u)
#define USB2UART_1BYTE_COMMON               (0x05u)
#define USB2UART_SYSEX_ENDS_WITH1           (0x05u)
#define USB2UART_SYSEX_ENDS_WITH2           (0x06u)
#define USB2UART_SYSEX_ENDS_WITH3           (0x07u)
#define USB2UART_NOTE_OFF                   (0x08u)
#define USB2UART_NOTE_ON                    (0x09u)
#define USB2UART_POLY_KEY_PRESSURE          (0x0Au)
#define USB2UART_CONTROL_CHANGE             (0x0Bu)
#define USB2UART_PROGRAM_CHANGE             (0x0Cu)
#define USB2UART_CHANNEL_PRESSURE           (0x0Du)
#define USB2UART_PITCH_BEND_CHANGE          (0x0Eu)
#define USB2UART_SINGLE_BYTE                (0x0Fu)

#define USB2UART_CABLE_MASK                 (0xF0u)
#define USB2UART_MIDI_CABLE_00              (0x00u)
#define USB2UART_MIDI_CABLE_01              (0x10u)

#define USB2UART_EVENT_BYTE0                (0x00u)
#define USB2UART_EVENT_BYTE1                (0x01u)
#define USB2UART_EVENT_BYTE2                (0x02u)
#define USB2UART_EVENT_BYTE3                (0x03u)
#define USB2UART_EVENT_LENGTH               (0x04u)

#define USB2UART_MIDI_STATUS_BYTE_MASK      (0x80u)
#define USB2UART_MIDI_STATUS_MASK           (0xF0u)
#define USB2UART_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define USB2UART_MIDI_NOTE_OFF              (0x80u)
#define USB2UART_MIDI_NOTE_ON               (0x90u)
#define USB2UART_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define USB2UART_MIDI_CONTROL_CHANGE        (0xB0u)
#define USB2UART_MIDI_PROGRAM_CHANGE        (0xC0u)
#define USB2UART_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define USB2UART_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define USB2UART_MIDI_SYSEX                 (0xF0u)
#define USB2UART_MIDI_EOSEX                 (0xF7u)
#define USB2UART_MIDI_QFM                   (0xF1u)
#define USB2UART_MIDI_SPP                   (0xF2u)
#define USB2UART_MIDI_SONGSEL               (0xF3u)
#define USB2UART_MIDI_TUNEREQ               (0xF6u)
#define USB2UART_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define USB2UART_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define USB2UART_MIDI_SYSEX_REALTIME        (0x7Fu)
/* ID of target device */
#define USB2UART_MIDI_SYSEX_ID_ALL          (0x7Fu)
/* Sub-ID#1*/
#define USB2UART_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define USB2UART_MIDI_SYSEX_GEN_MESSAGE     (0x09u)
/* Sub-ID#2*/
#define USB2UART_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define USB2UART_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define USB2UART_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define USB2UART_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

#define USB2UART_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#define USB2UART_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)

#define USB2UART_ISR_SERVICE_MIDI_OUT         \
        ( (USB2UART_ENABLE_MIDI_API != 0u) && \
          (USB2UART_MIDI_OUT_BUFF_SIZE > 0) && (USB2UART_EP_MM == USB2UART__EP_DMAAUTO))
#define USB2UART_ISR_SERVICE_MIDI_IN     \
        ( (USB2UART_ENABLE_MIDI_API != 0u) && (USB2UART_MIDI_IN_BUFF_SIZE > 0) )


/***************************************
* External function references
***************************************/

void USB2UART_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg)
                                                     ;


/***************************************
*    External references
***************************************/

#if (USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF)
    #include "MIDI1_UART.h"
#endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF */
#if (USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF)
    #include "MIDI2_UART.h"
#endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF */
#if(USB2UART_EP_MM != USB2UART__EP_MANUAL)
    #include <CyDmac.h>
#endif /*  USB2UART_EP_MM */


/***************************************
*    Private function prototypes
***************************************/

void USB2UART_PrepareInBuffer(uint8 ic, const uint8 srcBuff[], uint8 eventLen, uint8 cable)
                                                                 ;
#if (USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF)
    void USB2UART_MIDI_Init(void) ;
    uint8 USB2UART_ProcessMidiIn(uint8 mData, USB2UART_MIDI_RX_STATUS *rxStat)
                                                                ;
    uint8 USB2UART_MIDI1_GetEvent(void) ;
    void USB2UART_MIDI1_ProcessUsbOut(const uint8 epBuf[])
                                                     ;

    #if (USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF)
        uint8 USB2UART_MIDI2_GetEvent(void) ;
        void USB2UART_MIDI2_ProcessUsbOut(const uint8 epBuf[])
                                                    ;
    #endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF */
#endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF */


/***************************************
* External data references
***************************************/

#if defined(USB2UART_ENABLE_MIDI_STREAMING)

#if (USB2UART_MIDI_IN_BUFF_SIZE > 0)
    #if (USB2UART_MIDI_IN_BUFF_SIZE >= 256)
        extern volatile uint16 USB2UART_midiInPointer;                       /* Input endpoint buffer pointer */
    #else
        extern volatile uint8 USB2UART_midiInPointer;                        /* Input endpoint buffer pointer */
    #endif /*  USB2UART_MIDI_IN_BUFF_SIZE >=256 */
    extern volatile uint8 USB2UART_midi_in_ep;                               /* Input endpoint number */
    extern uint8 USB2UART_midiInBuffer[USB2UART_MIDI_IN_BUFF_SIZE];  /* Input endpoint buffer */
#endif /* USB2UART_MIDI_IN_BUFF_SIZE > 0 */

#if (USB2UART_MIDI_OUT_BUFF_SIZE > 0)
    extern volatile uint8 USB2UART_midi_out_ep;                               /* Output endpoint number */
    extern uint8 USB2UART_midiOutBuffer[USB2UART_MIDI_OUT_BUFF_SIZE]; /* Output endpoint buffer */
#endif /* USB2UART_MIDI_OUT_BUFF_SIZE > 0 */

#if (USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF)
    extern volatile uint8 USB2UART_MIDI1_InqFlags;                              /* Device inquiry flag */
    #if (USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF)
        extern volatile uint8 USB2UART_MIDI2_InqFlags;                          /* Device inquiry flag */
    #endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_TWO_EXT_INTRF */
#endif /*  USB2UART_MIDI_EXT_MODE >= USB2UART_ONE_EXT_INTRF */

#endif /* USB2UART_ENABLE_MIDI_STREAMING */


#endif /*  CY_USBFS_USB2UART_midi_H */


/* [] END OF FILE */
