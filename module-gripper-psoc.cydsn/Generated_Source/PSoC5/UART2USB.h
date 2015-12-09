/*******************************************************************************
* File Name: UART2USB.h
* Version 2.40
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UART2USB_H)
#define CY_UART_UART2USB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART2USB_RX_ENABLED                     (1u)
#define UART2USB_TX_ENABLED                     (1u)
#define UART2USB_HD_ENABLED                     (0u)
#define UART2USB_RX_INTERRUPT_ENABLED           (0u)
#define UART2USB_TX_INTERRUPT_ENABLED           (0u)
#define UART2USB_INTERNAL_CLOCK_USED            (1u)
#define UART2USB_RXHW_ADDRESS_ENABLED           (0u)
#define UART2USB_OVER_SAMPLE_COUNT              (8u)
#define UART2USB_PARITY_TYPE                    (0u)
#define UART2USB_PARITY_TYPE_SW                 (0u)
#define UART2USB_BREAK_DETECT                   (0u)
#define UART2USB_BREAK_BITS_TX                  (13u)
#define UART2USB_BREAK_BITS_RX                  (13u)
#define UART2USB_TXCLKGEN_DP                    (1u)
#define UART2USB_USE23POLLING                   (1u)
#define UART2USB_FLOW_CONTROL                   (0u)
#define UART2USB_CLK_FREQ                       (0u)
#define UART2USB_TX_BUFFER_SIZE                 (4u)
#define UART2USB_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART2USB_CONTROL_REG_REMOVED            (0u)
#else
    #define UART2USB_CONTROL_REG_REMOVED            (1u)
#endif /* End UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART2USB_backupStruct_
{
    uint8 enableState;

    #if(UART2USB_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART2USB_CONTROL_REG_REMOVED */

} UART2USB_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART2USB_Start(void) ;
void UART2USB_Stop(void) ;
uint8 UART2USB_ReadControlRegister(void) ;
void UART2USB_WriteControlRegister(uint8 control) ;

void UART2USB_Init(void) ;
void UART2USB_Enable(void) ;
void UART2USB_SaveConfig(void) ;
void UART2USB_RestoreConfig(void) ;
void UART2USB_Sleep(void) ;
void UART2USB_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )

    #if (UART2USB_RX_INTERRUPT_ENABLED)
        #define UART2USB_EnableRxInt()  CyIntEnable (UART2USB_RX_VECT_NUM)
        #define UART2USB_DisableRxInt() CyIntDisable(UART2USB_RX_VECT_NUM)
        CY_ISR_PROTO(UART2USB_RXISR);
    #endif /* UART2USB_RX_INTERRUPT_ENABLED */

    void UART2USB_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART2USB_SetRxAddress1(uint8 address) ;
    void UART2USB_SetRxAddress2(uint8 address) ;

    void  UART2USB_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART2USB_ReadRxData(void) ;
    uint8 UART2USB_ReadRxStatus(void) ;
    uint8 UART2USB_GetChar(void) ;
    uint16 UART2USB_GetByte(void) ;
    uint8 UART2USB_GetRxBufferSize(void)
                                                            ;
    void UART2USB_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART2USB_GetRxInterruptSource   UART2USB_ReadRxStatus

#endif /* End (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART2USB_TX_ENABLED || UART2USB_HD_ENABLED)

    #if(UART2USB_TX_INTERRUPT_ENABLED)
        #define UART2USB_EnableTxInt()  CyIntEnable (UART2USB_TX_VECT_NUM)
        #define UART2USB_DisableTxInt() CyIntDisable(UART2USB_TX_VECT_NUM)
        #define UART2USB_SetPendingTxInt() CyIntSetPending(UART2USB_TX_VECT_NUM)
        #define UART2USB_ClearPendingTxInt() CyIntClearPending(UART2USB_TX_VECT_NUM)
        CY_ISR_PROTO(UART2USB_TXISR);
    #endif /* UART2USB_TX_INTERRUPT_ENABLED */

    void UART2USB_SetTxInterruptMode(uint8 intSrc) ;
    void UART2USB_WriteTxData(uint8 txDataByte) ;
    uint8 UART2USB_ReadTxStatus(void) ;
    void UART2USB_PutChar(uint8 txDataByte) ;
    void UART2USB_PutString(const char8 string[]) ;
    void UART2USB_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART2USB_PutCRLF(uint8 txDataByte) ;
    void UART2USB_ClearTxBuffer(void) ;
    void UART2USB_SetTxAddressMode(uint8 addressMode) ;
    void UART2USB_SendBreak(uint8 retMode) ;
    uint8 UART2USB_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART2USB_PutStringConst         UART2USB_PutString
    #define UART2USB_PutArrayConst          UART2USB_PutArray
    #define UART2USB_GetTxInterruptSource   UART2USB_ReadTxStatus

#endif /* End UART2USB_TX_ENABLED || UART2USB_HD_ENABLED */

#if(UART2USB_HD_ENABLED)
    void UART2USB_LoadRxConfig(void) ;
    void UART2USB_LoadTxConfig(void) ;
#endif /* End UART2USB_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2USB) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART2USB_CyBtldrCommStart(void) CYSMALL ;
    void    UART2USB_CyBtldrCommStop(void) CYSMALL ;
    void    UART2USB_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART2USB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART2USB_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2USB)
        #define CyBtldrCommStart    UART2USB_CyBtldrCommStart
        #define CyBtldrCommStop     UART2USB_CyBtldrCommStop
        #define CyBtldrCommReset    UART2USB_CyBtldrCommReset
        #define CyBtldrCommWrite    UART2USB_CyBtldrCommWrite
        #define CyBtldrCommRead     UART2USB_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2USB) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART2USB_BYTE2BYTE_TIME_OUT (25u)
    #define UART2USB_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART2USB_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART2USB_WAIT_1_MS          (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART2USB_SET_SPACE      (0x00u)
#define UART2USB_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART2USB_TX_ENABLED) || (UART2USB_HD_ENABLED) )
    #if(UART2USB_TX_INTERRUPT_ENABLED)
        #define UART2USB_TX_VECT_NUM            (uint8)UART2USB_TXInternalInterrupt__INTC_NUMBER
        #define UART2USB_TX_PRIOR_NUM           (uint8)UART2USB_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2USB_TX_INTERRUPT_ENABLED */

    #define UART2USB_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART2USB_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART2USB_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART2USB_TX_ENABLED)
        #define UART2USB_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART2USB_HD_ENABLED) */
        #define UART2USB_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART2USB_TX_ENABLED) */

    #define UART2USB_TX_STS_COMPLETE            (uint8)(0x01u << UART2USB_TX_STS_COMPLETE_SHIFT)
    #define UART2USB_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART2USB_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART2USB_TX_STS_FIFO_FULL           (uint8)(0x01u << UART2USB_TX_STS_FIFO_FULL_SHIFT)
    #define UART2USB_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART2USB_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART2USB_TX_ENABLED) || (UART2USB_HD_ENABLED)*/

#if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )
    #if(UART2USB_RX_INTERRUPT_ENABLED)
        #define UART2USB_RX_VECT_NUM            (uint8)UART2USB_RXInternalInterrupt__INTC_NUMBER
        #define UART2USB_RX_PRIOR_NUM           (uint8)UART2USB_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2USB_RX_INTERRUPT_ENABLED */
    #define UART2USB_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART2USB_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART2USB_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART2USB_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART2USB_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART2USB_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART2USB_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART2USB_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART2USB_RX_STS_MRKSPC           (uint8)(0x01u << UART2USB_RX_STS_MRKSPC_SHIFT)
    #define UART2USB_RX_STS_BREAK            (uint8)(0x01u << UART2USB_RX_STS_BREAK_SHIFT)
    #define UART2USB_RX_STS_PAR_ERROR        (uint8)(0x01u << UART2USB_RX_STS_PAR_ERROR_SHIFT)
    #define UART2USB_RX_STS_STOP_ERROR       (uint8)(0x01u << UART2USB_RX_STS_STOP_ERROR_SHIFT)
    #define UART2USB_RX_STS_OVERRUN          (uint8)(0x01u << UART2USB_RX_STS_OVERRUN_SHIFT)
    #define UART2USB_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART2USB_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART2USB_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART2USB_RX_STS_ADDR_MATCH_SHIFT)
    #define UART2USB_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART2USB_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART2USB_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */

/* Control Register definitions */
#define UART2USB_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART2USB_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART2USB_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART2USB_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART2USB_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART2USB_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART2USB_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART2USB_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART2USB_CTRL_HD_SEND               (uint8)(0x01u << UART2USB_CTRL_HD_SEND_SHIFT)
#define UART2USB_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART2USB_CTRL_HD_SEND_BREAK_SHIFT)
#define UART2USB_CTRL_MARK                  (uint8)(0x01u << UART2USB_CTRL_MARK_SHIFT)
#define UART2USB_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART2USB_CTRL_PARITY_TYPE0_SHIFT)
#define UART2USB_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART2USB_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART2USB_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART2USB_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART2USB_SEND_BREAK                         (0x00u)
#define UART2USB_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART2USB_REINIT                             (0x02u)
#define UART2USB_SEND_WAIT_REINIT                   (0x03u)

#define UART2USB_OVER_SAMPLE_8                      (8u)
#define UART2USB_OVER_SAMPLE_16                     (16u)

#define UART2USB_BIT_CENTER                         (UART2USB_OVER_SAMPLE_COUNT - 2u)

#define UART2USB_FIFO_LENGTH                        (4u)
#define UART2USB_NUMBER_OF_START_BIT                (1u)
#define UART2USB_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART2USB_TXBITCTR_BREAKBITS8X   ((UART2USB_BREAK_BITS_TX * UART2USB_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART2USB_TXBITCTR_BREAKBITS ((UART2USB_BREAK_BITS_TX * UART2USB_OVER_SAMPLE_COUNT) - 1u)

#define UART2USB_HALF_BIT_COUNT   \
                            (((UART2USB_OVER_SAMPLE_COUNT / 2u) + (UART2USB_USE23POLLING * 1u)) - 2u)
#if (UART2USB_OVER_SAMPLE_COUNT == UART2USB_OVER_SAMPLE_8)
    #define UART2USB_HD_TXBITCTR_INIT   (((UART2USB_BREAK_BITS_TX + \
                            UART2USB_NUMBER_OF_START_BIT) * UART2USB_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART2USB_RXBITCTR_INIT  ((((UART2USB_BREAK_BITS_RX + UART2USB_NUMBER_OF_START_BIT) \
                            * UART2USB_OVER_SAMPLE_COUNT) + UART2USB_HALF_BIT_COUNT) - 1u)

#else /* UART2USB_OVER_SAMPLE_COUNT == UART2USB_OVER_SAMPLE_16 */
    #define UART2USB_HD_TXBITCTR_INIT   ((8u * UART2USB_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount 16 */
    #define UART2USB_RXBITCTR_INIT      (((7u * UART2USB_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART2USB_HALF_BIT_COUNT)
#endif /* End UART2USB_OVER_SAMPLE_COUNT */

#define UART2USB_HD_RXBITCTR_INIT                   UART2USB_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART2USB_initVar;
#if (UART2USB_TX_INTERRUPT_ENABLED && UART2USB_TX_ENABLED)
    extern volatile uint8 UART2USB_txBuffer[UART2USB_TX_BUFFER_SIZE];
    extern volatile uint8 UART2USB_txBufferRead;
    extern uint8 UART2USB_txBufferWrite;
#endif /* (UART2USB_TX_INTERRUPT_ENABLED && UART2USB_TX_ENABLED) */
#if (UART2USB_RX_INTERRUPT_ENABLED && (UART2USB_RX_ENABLED || UART2USB_HD_ENABLED))
    extern uint8 UART2USB_errorStatus;
    extern volatile uint8 UART2USB_rxBuffer[UART2USB_RX_BUFFER_SIZE];
    extern volatile uint8 UART2USB_rxBufferRead;
    extern volatile uint8 UART2USB_rxBufferWrite;
    extern volatile uint8 UART2USB_rxBufferLoopDetect;
    extern volatile uint8 UART2USB_rxBufferOverflow;
    #if (UART2USB_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART2USB_rxAddressMode;
        extern volatile uint8 UART2USB_rxAddressDetected;
    #endif /* (UART2USB_RXHW_ADDRESS_ENABLED) */
#endif /* (UART2USB_RX_INTERRUPT_ENABLED && (UART2USB_RX_ENABLED || UART2USB_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART2USB__B_UART__AM_SW_BYTE_BYTE 1
#define UART2USB__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART2USB__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART2USB__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART2USB__B_UART__AM_NONE 0

#define UART2USB__B_UART__NONE_REVB 0
#define UART2USB__B_UART__EVEN_REVB 1
#define UART2USB__B_UART__ODD_REVB 2
#define UART2USB__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART2USB_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART2USB_NUMBER_OF_STOP_BITS    (1u)

#if (UART2USB_RXHW_ADDRESS_ENABLED)
    #define UART2USB_RX_ADDRESS_MODE    (0u)
    #define UART2USB_RX_HW_ADDRESS1     (0u)
    #define UART2USB_RX_HW_ADDRESS2     (0u)
#endif /* (UART2USB_RXHW_ADDRESS_ENABLED) */

#define UART2USB_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART2USB_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART2USB_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART2USB_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART2USB_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART2USB_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART2USB_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART2USB_RX_STS_OVERRUN_SHIFT))

#define UART2USB_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART2USB_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART2USB_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART2USB_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART2USB_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2USB_CONTROL_REG \
                            (* (reg8 *) UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART2USB_CONTROL_PTR \
                            (  (reg8 *) UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2USB_TX_ENABLED)
    #define UART2USB_TXDATA_REG          (* (reg8 *) UART2USB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2USB_TXDATA_PTR          (  (reg8 *) UART2USB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2USB_TXDATA_AUX_CTL_REG  (* (reg8 *) UART2USB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2USB_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART2USB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2USB_TXSTATUS_REG        (* (reg8 *) UART2USB_BUART_sTX_TxSts__STATUS_REG)
    #define UART2USB_TXSTATUS_PTR        (  (reg8 *) UART2USB_BUART_sTX_TxSts__STATUS_REG)
    #define UART2USB_TXSTATUS_MASK_REG   (* (reg8 *) UART2USB_BUART_sTX_TxSts__MASK_REG)
    #define UART2USB_TXSTATUS_MASK_PTR   (  (reg8 *) UART2USB_BUART_sTX_TxSts__MASK_REG)
    #define UART2USB_TXSTATUS_ACTL_REG   (* (reg8 *) UART2USB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART2USB_TXSTATUS_ACTL_PTR   (  (reg8 *) UART2USB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART2USB_TXCLKGEN_DP)
        #define UART2USB_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2USB_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2USB_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART2USB_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART2USB_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2USB_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2USB_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2USB_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2USB_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART2USB_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART2USB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART2USB_TXCLKGEN_DP */

#endif /* End UART2USB_TX_ENABLED */

#if(UART2USB_HD_ENABLED)

    #define UART2USB_TXDATA_REG             (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2USB_TXDATA_PTR             (  (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2USB_TXDATA_AUX_CTL_REG     (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART2USB_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2USB_TXSTATUS_REG           (* (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_REG )
    #define UART2USB_TXSTATUS_PTR           (  (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_REG )
    #define UART2USB_TXSTATUS_MASK_REG      (* (reg8 *) UART2USB_BUART_sRX_RxSts__MASK_REG )
    #define UART2USB_TXSTATUS_MASK_PTR      (  (reg8 *) UART2USB_BUART_sRX_RxSts__MASK_REG )
    #define UART2USB_TXSTATUS_ACTL_REG      (* (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2USB_TXSTATUS_ACTL_PTR      (  (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART2USB_HD_ENABLED */

#if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )
    #define UART2USB_RXDATA_REG             (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2USB_RXDATA_PTR             (  (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2USB_RXADDRESS1_REG         (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2USB_RXADDRESS1_PTR         (  (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2USB_RXADDRESS2_REG         (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2USB_RXADDRESS2_PTR         (  (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2USB_RXDATA_AUX_CTL_REG     (* (reg8 *) UART2USB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2USB_RXBITCTR_PERIOD_REG    (* (reg8 *) UART2USB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2USB_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART2USB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2USB_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2USB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2USB_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2USB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2USB_RXBITCTR_COUNTER_REG   (* (reg8 *) UART2USB_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART2USB_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART2USB_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART2USB_RXSTATUS_REG           (* (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_REG )
    #define UART2USB_RXSTATUS_PTR           (  (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_REG )
    #define UART2USB_RXSTATUS_MASK_REG      (* (reg8 *) UART2USB_BUART_sRX_RxSts__MASK_REG )
    #define UART2USB_RXSTATUS_MASK_PTR      (  (reg8 *) UART2USB_BUART_sRX_RxSts__MASK_REG )
    #define UART2USB_RXSTATUS_ACTL_REG      (* (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2USB_RXSTATUS_ACTL_PTR      (  (reg8 *) UART2USB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */

#if(UART2USB_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART2USB_INTCLOCK_CLKEN_REG     (* (reg8 *) UART2USB_IntClock__PM_ACT_CFG)
    #define UART2USB_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART2USB_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART2USB_INTCLOCK_CLKEN_MASK    UART2USB_IntClock__PM_ACT_MSK
#endif /* End UART2USB_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART2USB_TX_ENABLED)
    #define UART2USB_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART2USB_TX_ENABLED */

#if(UART2USB_HD_ENABLED)
    #define UART2USB_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART2USB_HD_ENABLED */

#if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )
    #define UART2USB_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART2USB_TXBUFFERSIZE   UART2USB_TX_BUFFER_SIZE
#define UART2USB_RXBUFFERSIZE   UART2USB_RX_BUFFER_SIZE

#if (UART2USB_RXHW_ADDRESS_ENABLED)
    #define UART2USB_RXADDRESSMODE  UART2USB_RX_ADDRESS_MODE
    #define UART2USB_RXHWADDRESS1   UART2USB_RX_HW_ADDRESS1
    #define UART2USB_RXHWADDRESS2   UART2USB_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART2USB_RXAddressMode  UART2USB_RXADDRESSMODE
#endif /* (UART2USB_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART2USB_initvar                    UART2USB_initVar

#define UART2USB_RX_Enabled                 UART2USB_RX_ENABLED
#define UART2USB_TX_Enabled                 UART2USB_TX_ENABLED
#define UART2USB_HD_Enabled                 UART2USB_HD_ENABLED
#define UART2USB_RX_IntInterruptEnabled     UART2USB_RX_INTERRUPT_ENABLED
#define UART2USB_TX_IntInterruptEnabled     UART2USB_TX_INTERRUPT_ENABLED
#define UART2USB_InternalClockUsed          UART2USB_INTERNAL_CLOCK_USED
#define UART2USB_RXHW_Address_Enabled       UART2USB_RXHW_ADDRESS_ENABLED
#define UART2USB_OverSampleCount            UART2USB_OVER_SAMPLE_COUNT
#define UART2USB_ParityType                 UART2USB_PARITY_TYPE

#if( UART2USB_TX_ENABLED && (UART2USB_TXBUFFERSIZE > UART2USB_FIFO_LENGTH))
    #define UART2USB_TXBUFFER               UART2USB_txBuffer
    #define UART2USB_TXBUFFERREAD           UART2USB_txBufferRead
    #define UART2USB_TXBUFFERWRITE          UART2USB_txBufferWrite
#endif /* End UART2USB_TX_ENABLED */
#if( ( UART2USB_RX_ENABLED || UART2USB_HD_ENABLED ) && \
     (UART2USB_RXBUFFERSIZE > UART2USB_FIFO_LENGTH) )
    #define UART2USB_RXBUFFER               UART2USB_rxBuffer
    #define UART2USB_RXBUFFERREAD           UART2USB_rxBufferRead
    #define UART2USB_RXBUFFERWRITE          UART2USB_rxBufferWrite
    #define UART2USB_RXBUFFERLOOPDETECT     UART2USB_rxBufferLoopDetect
    #define UART2USB_RXBUFFER_OVERFLOW      UART2USB_rxBufferOverflow
#endif /* End UART2USB_RX_ENABLED */

#ifdef UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2USB_CONTROL                UART2USB_CONTROL_REG
#endif /* End UART2USB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2USB_TX_ENABLED)
    #define UART2USB_TXDATA                 UART2USB_TXDATA_REG
    #define UART2USB_TXSTATUS               UART2USB_TXSTATUS_REG
    #define UART2USB_TXSTATUS_MASK          UART2USB_TXSTATUS_MASK_REG
    #define UART2USB_TXSTATUS_ACTL          UART2USB_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART2USB_TXCLKGEN_DP)
        #define UART2USB_TXBITCLKGEN_CTR        UART2USB_TXBITCLKGEN_CTR_REG
        #define UART2USB_TXBITCLKTX_COMPLETE    UART2USB_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART2USB_TXBITCTR_PERIOD        UART2USB_TXBITCTR_PERIOD_REG
        #define UART2USB_TXBITCTR_CONTROL       UART2USB_TXBITCTR_CONTROL_REG
        #define UART2USB_TXBITCTR_COUNTER       UART2USB_TXBITCTR_COUNTER_REG
    #endif /* UART2USB_TXCLKGEN_DP */
#endif /* End UART2USB_TX_ENABLED */

#if(UART2USB_HD_ENABLED)
    #define UART2USB_TXDATA                 UART2USB_TXDATA_REG
    #define UART2USB_TXSTATUS               UART2USB_TXSTATUS_REG
    #define UART2USB_TXSTATUS_MASK          UART2USB_TXSTATUS_MASK_REG
    #define UART2USB_TXSTATUS_ACTL          UART2USB_TXSTATUS_ACTL_REG
#endif /* End UART2USB_HD_ENABLED */

#if( (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) )
    #define UART2USB_RXDATA                 UART2USB_RXDATA_REG
    #define UART2USB_RXADDRESS1             UART2USB_RXADDRESS1_REG
    #define UART2USB_RXADDRESS2             UART2USB_RXADDRESS2_REG
    #define UART2USB_RXBITCTR_PERIOD        UART2USB_RXBITCTR_PERIOD_REG
    #define UART2USB_RXBITCTR_CONTROL       UART2USB_RXBITCTR_CONTROL_REG
    #define UART2USB_RXBITCTR_COUNTER       UART2USB_RXBITCTR_COUNTER_REG
    #define UART2USB_RXSTATUS               UART2USB_RXSTATUS_REG
    #define UART2USB_RXSTATUS_MASK          UART2USB_RXSTATUS_MASK_REG
    #define UART2USB_RXSTATUS_ACTL          UART2USB_RXSTATUS_ACTL_REG
#endif /* End  (UART2USB_RX_ENABLED) || (UART2USB_HD_ENABLED) */

#if(UART2USB_INTERNAL_CLOCK_USED)
    #define UART2USB_INTCLOCK_CLKEN         UART2USB_INTCLOCK_CLKEN_REG
#endif /* End UART2USB_INTERNAL_CLOCK_USED */

#define UART2USB_WAIT_FOR_COMLETE_REINIT    UART2USB_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART2USB_H */


/* [] END OF FILE */
