/*******************************************************************************
* File Name: .h
* Version 2.80
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB2UART_pvt_H)
#define CY_USBFS_USB2UART_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE USB2UART_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USB2UART_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_USB2UART_EP_SETTINGS_BLOCK CYCODE USB2UART_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE USB2UART_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USB2UART_LUT CYCODE USB2UART_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USB2UART_LUT CYCODE USB2UART_DEVICE0_TABLE[2u];
extern const T_USB2UART_LUT CYCODE USB2UART_TABLE[1u];
extern const uint8 CYCODE USB2UART_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USB2UART_STRING_DESCRIPTORS[159u];
extern const uint8 CYCODE USB2UART_HIDREPORT_DESCRIPTOR1[54u];


extern const uint8 CYCODE USB2UART_MSOS_DESCRIPTOR[USB2UART_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USB2UART_MSOS_CONFIGURATION_DESCR[USB2UART_MSOS_CONF_DESCR_LENGTH];
#if defined(USB2UART_ENABLE_IDSN_STRING)
    extern uint8 USB2UART_idSerialNumberStringDescriptor[USB2UART_IDSN_DESCR_LENGTH];
#endif /* USB2UART_ENABLE_IDSN_STRING */

extern volatile uint8 USB2UART_interfaceNumber;
extern volatile uint8 USB2UART_interfaceSetting[USB2UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB2UART_interfaceSetting_last[USB2UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB2UART_deviceAddress;
extern volatile uint8 USB2UART_interfaceStatus[USB2UART_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USB2UART_interfaceClass;

extern volatile T_USB2UART_EP_CTL_BLOCK USB2UART_EP[USB2UART_MAX_EP];
extern volatile T_USB2UART_TD USB2UART_currentTD;

#if(USB2UART_EP_MM != USB2UART__EP_MANUAL)
    extern uint8 USB2UART_DmaChan[USB2UART_MAX_EP];
    extern uint8 USB2UART_DmaTd[USB2UART_MAX_EP];
#endif /*  USB2UART_EP_MM */
#if((USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u))
    extern uint8 USB2UART_DmaNextTd[USB2UART_MAX_EP];
    extern const uint8 USB2UART_epX_TD_TERMOUT_EN[USB2UART_MAX_EP];
    extern volatile uint16 USB2UART_inLength[USB2UART_MAX_EP];
    extern const uint8 *USB2UART_inDataPointer[USB2UART_MAX_EP];
    extern volatile uint8 USB2UART_inBufFull[USB2UART_MAX_EP];
#endif /*  ((USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u)) */

extern volatile uint8 USB2UART_ep0Toggle;
extern volatile uint8 USB2UART_lastPacketSize;
extern volatile uint8 USB2UART_ep0Mode;
extern volatile uint8 USB2UART_ep0Count;
extern volatile uint16 USB2UART_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USB2UART_ReInitComponent(void) ;
void  USB2UART_HandleSetup(void) ;
void  USB2UART_HandleIN(void) ;
void  USB2UART_HandleOUT(void) ;
void  USB2UART_LoadEP0(void) ;
uint8 USB2UART_InitControlRead(void) ;
uint8 USB2UART_InitControlWrite(void) ;
void  USB2UART_ControlReadDataStage(void) ;
void  USB2UART_ControlReadStatusStage(void) ;
void  USB2UART_ControlReadPrematureStatus(void)
                                                ;
uint8 USB2UART_InitControlWrite(void) ;
uint8 USB2UART_InitZeroLengthControlTransfer(void)
                                                ;
void  USB2UART_ControlWriteDataStage(void) ;
void  USB2UART_ControlWriteStatusStage(void) ;
void  USB2UART_ControlWritePrematureStatus(void)
                                                ;
uint8 USB2UART_InitNoDataControlTransfer(void) ;
void  USB2UART_NoDataControlStatusStage(void) ;
void  USB2UART_InitializeStatusBlock(void) ;
void  USB2UART_UpdateStatusBlock(uint8 completionCode) ;
uint8 USB2UART_DispatchClassRqst(void) ;

void USB2UART_Config(uint8 clearAltSetting) ;
void USB2UART_ConfigAltChanged(void) ;
void USB2UART_ConfigReg(void) ;

const T_USB2UART_LUT CYCODE *USB2UART_GetConfigTablePtr(uint8 confIndex)
                                                            ;
const T_USB2UART_LUT CYCODE *USB2UART_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *USB2UART_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 USB2UART_ClearEndpointHalt(void) ;
uint8 USB2UART_SetEndpointHalt(void) ;
uint8 USB2UART_ValidateAlternateSetting(void) ;

void USB2UART_SaveConfig(void) ;
void USB2UART_RestoreConfig(void) ;

#if ((USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u))
    void USB2UART_LoadNextInEP(uint8 epNumber, uint8 mode) ;
#endif /* (USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u) */

#if defined(USB2UART_ENABLE_IDSN_STRING)
    void USB2UART_ReadDieID(uint8 descr[]) ;
#endif /* USB2UART_ENABLE_IDSN_STRING */

#if defined(USB2UART_ENABLE_HID_CLASS)
    uint8 USB2UART_DispatchHIDClassRqst(void);
#endif /*  USB2UART_ENABLE_HID_CLASS */
#if defined(USB2UART_ENABLE_AUDIO_CLASS)
    uint8 USB2UART_DispatchAUDIOClassRqst(void);
#endif /*  USB2UART_ENABLE_HID_CLASS */
#if defined(USB2UART_ENABLE_CDC_CLASS)
    uint8 USB2UART_DispatchCDCClassRqst(void);
#endif /*  USB2UART_ENABLE_CDC_CLASS */

CY_ISR_PROTO(USB2UART_EP_0_ISR);
#if(USB2UART_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_1_ISR);
#endif /*  USB2UART_EP1_ISR_REMOVE */
#if(USB2UART_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_2_ISR);
#endif /*  USB2UART_EP2_ISR_REMOVE */
#if(USB2UART_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_3_ISR);
#endif /*  USB2UART_EP3_ISR_REMOVE */
#if(USB2UART_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_4_ISR);
#endif /*  USB2UART_EP4_ISR_REMOVE */
#if(USB2UART_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_5_ISR);
#endif /*  USB2UART_EP5_ISR_REMOVE */
#if(USB2UART_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_6_ISR);
#endif /*  USB2UART_EP6_ISR_REMOVE */
#if(USB2UART_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_7_ISR);
#endif /*  USB2UART_EP7_ISR_REMOVE */
#if(USB2UART_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_EP_8_ISR);
#endif /*  USB2UART_EP8_ISR_REMOVE */
CY_ISR_PROTO(USB2UART_BUS_RESET_ISR);
#if(USB2UART_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_SOF_ISR);
#endif /*  USB2UART_SOF_ISR_REMOVE */
#if(USB2UART_EP_MM != USB2UART__EP_MANUAL)
    CY_ISR_PROTO(USB2UART_ARB_ISR);
#endif /*  USB2UART_EP_MM */
#if(USB2UART_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB2UART_DP_ISR);
#endif /*  USB2UART_DP_ISR_REMOVE */
#if ((USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u))
    CY_ISR_PROTO(USB2UART_EP_DMA_DONE_ISR);
#endif /* (USB2UART_EP_MM == USB2UART__EP_DMAAUTO) && (USB2UART_EP_DMA_AUTO_OPT == 0u) */

/***************************************
* Request Handlers
***************************************/

uint8 USB2UART_HandleStandardRqst(void) ;
uint8 USB2UART_DispatchClassRqst(void) ;
uint8 USB2UART_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USB2UART_ENABLE_HID_CLASS)
    void USB2UART_FindReport(void) ;
    void USB2UART_FindReportDescriptor(void) ;
    void USB2UART_FindHidClassDecriptor(void) ;
#endif /* USB2UART_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USB2UART_ENABLE_MIDI_STREAMING)
    void USB2UART_MIDI_IN_EP_Service(void) ;
#endif /* USB2UART_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_USB2UART_pvt_H */


/* [] END OF FILE */
