/*******************************************************************************
* File Name: UART2DYNAMIXEL.h
* Version 2.50
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


#if !defined(CY_UART_UART2DYNAMIXEL_H)
#define CY_UART_UART2DYNAMIXEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART2DYNAMIXEL_RX_ENABLED                     (1u)
#define UART2DYNAMIXEL_TX_ENABLED                     (1u)
#define UART2DYNAMIXEL_HD_ENABLED                     (0u)
#define UART2DYNAMIXEL_RX_INTERRUPT_ENABLED           (1u)
#define UART2DYNAMIXEL_TX_INTERRUPT_ENABLED           (0u)
#define UART2DYNAMIXEL_INTERNAL_CLOCK_USED            (0u)
#define UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED           (0u)
#define UART2DYNAMIXEL_OVER_SAMPLE_COUNT              (8u)
#define UART2DYNAMIXEL_PARITY_TYPE                    (0u)
#define UART2DYNAMIXEL_PARITY_TYPE_SW                 (0u)
#define UART2DYNAMIXEL_BREAK_DETECT                   (0u)
#define UART2DYNAMIXEL_BREAK_BITS_TX                  (13u)
#define UART2DYNAMIXEL_BREAK_BITS_RX                  (13u)
#define UART2DYNAMIXEL_TXCLKGEN_DP                    (1u)
#define UART2DYNAMIXEL_USE23POLLING                   (1u)
#define UART2DYNAMIXEL_FLOW_CONTROL                   (0u)
#define UART2DYNAMIXEL_CLK_FREQ                       (0u)
#define UART2DYNAMIXEL_TX_BUFFER_SIZE                 (4u)
#define UART2DYNAMIXEL_RX_BUFFER_SIZE                 (8u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART2DYNAMIXEL_CONTROL_REG_REMOVED            (0u)
#else
    #define UART2DYNAMIXEL_CONTROL_REG_REMOVED            (1u)
#endif /* End UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART2DYNAMIXEL_backupStruct_
{
    uint8 enableState;

    #if(UART2DYNAMIXEL_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART2DYNAMIXEL_CONTROL_REG_REMOVED */

} UART2DYNAMIXEL_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART2DYNAMIXEL_Start(void) ;
void UART2DYNAMIXEL_Stop(void) ;
uint8 UART2DYNAMIXEL_ReadControlRegister(void) ;
void UART2DYNAMIXEL_WriteControlRegister(uint8 control) ;

void UART2DYNAMIXEL_Init(void) ;
void UART2DYNAMIXEL_Enable(void) ;
void UART2DYNAMIXEL_SaveConfig(void) ;
void UART2DYNAMIXEL_RestoreConfig(void) ;
void UART2DYNAMIXEL_Sleep(void) ;
void UART2DYNAMIXEL_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )

    #if (UART2DYNAMIXEL_RX_INTERRUPT_ENABLED)
        #define UART2DYNAMIXEL_EnableRxInt()  CyIntEnable (UART2DYNAMIXEL_RX_VECT_NUM)
        #define UART2DYNAMIXEL_DisableRxInt() CyIntDisable(UART2DYNAMIXEL_RX_VECT_NUM)
        CY_ISR_PROTO(UART2DYNAMIXEL_RXISR);
    #endif /* UART2DYNAMIXEL_RX_INTERRUPT_ENABLED */

    void UART2DYNAMIXEL_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART2DYNAMIXEL_SetRxAddress1(uint8 address) ;
    void UART2DYNAMIXEL_SetRxAddress2(uint8 address) ;

    void  UART2DYNAMIXEL_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART2DYNAMIXEL_ReadRxData(void) ;
    uint8 UART2DYNAMIXEL_ReadRxStatus(void) ;
    uint8 UART2DYNAMIXEL_GetChar(void) ;
    uint16 UART2DYNAMIXEL_GetByte(void) ;
    uint8 UART2DYNAMIXEL_GetRxBufferSize(void)
                                                            ;
    void UART2DYNAMIXEL_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART2DYNAMIXEL_GetRxInterruptSource   UART2DYNAMIXEL_ReadRxStatus

#endif /* End (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART2DYNAMIXEL_TX_ENABLED || UART2DYNAMIXEL_HD_ENABLED)

    #if(UART2DYNAMIXEL_TX_INTERRUPT_ENABLED)
        #define UART2DYNAMIXEL_EnableTxInt()  CyIntEnable (UART2DYNAMIXEL_TX_VECT_NUM)
        #define UART2DYNAMIXEL_DisableTxInt() CyIntDisable(UART2DYNAMIXEL_TX_VECT_NUM)
        #define UART2DYNAMIXEL_SetPendingTxInt() CyIntSetPending(UART2DYNAMIXEL_TX_VECT_NUM)
        #define UART2DYNAMIXEL_ClearPendingTxInt() CyIntClearPending(UART2DYNAMIXEL_TX_VECT_NUM)
        CY_ISR_PROTO(UART2DYNAMIXEL_TXISR);
    #endif /* UART2DYNAMIXEL_TX_INTERRUPT_ENABLED */

    void UART2DYNAMIXEL_SetTxInterruptMode(uint8 intSrc) ;
    void UART2DYNAMIXEL_WriteTxData(uint8 txDataByte) ;
    uint8 UART2DYNAMIXEL_ReadTxStatus(void) ;
    void UART2DYNAMIXEL_PutChar(uint8 txDataByte) ;
    void UART2DYNAMIXEL_PutString(const char8 string[]) ;
    void UART2DYNAMIXEL_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART2DYNAMIXEL_PutCRLF(uint8 txDataByte) ;
    void UART2DYNAMIXEL_ClearTxBuffer(void) ;
    void UART2DYNAMIXEL_SetTxAddressMode(uint8 addressMode) ;
    void UART2DYNAMIXEL_SendBreak(uint8 retMode) ;
    uint8 UART2DYNAMIXEL_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART2DYNAMIXEL_PutStringConst         UART2DYNAMIXEL_PutString
    #define UART2DYNAMIXEL_PutArrayConst          UART2DYNAMIXEL_PutArray
    #define UART2DYNAMIXEL_GetTxInterruptSource   UART2DYNAMIXEL_ReadTxStatus

#endif /* End UART2DYNAMIXEL_TX_ENABLED || UART2DYNAMIXEL_HD_ENABLED */

#if(UART2DYNAMIXEL_HD_ENABLED)
    void UART2DYNAMIXEL_LoadRxConfig(void) ;
    void UART2DYNAMIXEL_LoadTxConfig(void) ;
#endif /* End UART2DYNAMIXEL_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2DYNAMIXEL) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART2DYNAMIXEL_CyBtldrCommStart(void) CYSMALL ;
    void    UART2DYNAMIXEL_CyBtldrCommStop(void) CYSMALL ;
    void    UART2DYNAMIXEL_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART2DYNAMIXEL_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART2DYNAMIXEL_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2DYNAMIXEL)
        #define CyBtldrCommStart    UART2DYNAMIXEL_CyBtldrCommStart
        #define CyBtldrCommStop     UART2DYNAMIXEL_CyBtldrCommStop
        #define CyBtldrCommReset    UART2DYNAMIXEL_CyBtldrCommReset
        #define CyBtldrCommWrite    UART2DYNAMIXEL_CyBtldrCommWrite
        #define CyBtldrCommRead     UART2DYNAMIXEL_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2DYNAMIXEL) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART2DYNAMIXEL_BYTE2BYTE_TIME_OUT (25u)
    #define UART2DYNAMIXEL_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART2DYNAMIXEL_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART2DYNAMIXEL_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART2DYNAMIXEL_SET_SPACE      (0x00u)
#define UART2DYNAMIXEL_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART2DYNAMIXEL_TX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
    #if(UART2DYNAMIXEL_TX_INTERRUPT_ENABLED)
        #define UART2DYNAMIXEL_TX_VECT_NUM            (uint8)UART2DYNAMIXEL_TXInternalInterrupt__INTC_NUMBER
        #define UART2DYNAMIXEL_TX_PRIOR_NUM           (uint8)UART2DYNAMIXEL_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2DYNAMIXEL_TX_INTERRUPT_ENABLED */

    #define UART2DYNAMIXEL_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART2DYNAMIXEL_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART2DYNAMIXEL_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART2DYNAMIXEL_TX_ENABLED)
        #define UART2DYNAMIXEL_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART2DYNAMIXEL_HD_ENABLED) */
        #define UART2DYNAMIXEL_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART2DYNAMIXEL_TX_ENABLED) */

    #define UART2DYNAMIXEL_TX_STS_COMPLETE            (uint8)(0x01u << UART2DYNAMIXEL_TX_STS_COMPLETE_SHIFT)
    #define UART2DYNAMIXEL_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART2DYNAMIXEL_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART2DYNAMIXEL_TX_STS_FIFO_FULL           (uint8)(0x01u << UART2DYNAMIXEL_TX_STS_FIFO_FULL_SHIFT)
    #define UART2DYNAMIXEL_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART2DYNAMIXEL_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART2DYNAMIXEL_TX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED)*/

#if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
    #if(UART2DYNAMIXEL_RX_INTERRUPT_ENABLED)
        #define UART2DYNAMIXEL_RX_VECT_NUM            (uint8)UART2DYNAMIXEL_RXInternalInterrupt__INTC_NUMBER
        #define UART2DYNAMIXEL_RX_PRIOR_NUM           (uint8)UART2DYNAMIXEL_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2DYNAMIXEL_RX_INTERRUPT_ENABLED */
    #define UART2DYNAMIXEL_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART2DYNAMIXEL_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART2DYNAMIXEL_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART2DYNAMIXEL_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART2DYNAMIXEL_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART2DYNAMIXEL_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART2DYNAMIXEL_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART2DYNAMIXEL_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART2DYNAMIXEL_RX_STS_MRKSPC           (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_MRKSPC_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_BREAK            (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_BREAK_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_PAR_ERROR        (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_PAR_ERROR_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_STOP_ERROR       (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_STOP_ERROR_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_OVERRUN          (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_OVERRUN_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_ADDR_MATCH_SHIFT)
    #define UART2DYNAMIXEL_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART2DYNAMIXEL_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART2DYNAMIXEL_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */

/* Control Register definitions */
#define UART2DYNAMIXEL_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART2DYNAMIXEL_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART2DYNAMIXEL_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART2DYNAMIXEL_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART2DYNAMIXEL_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART2DYNAMIXEL_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART2DYNAMIXEL_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART2DYNAMIXEL_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART2DYNAMIXEL_CTRL_HD_SEND               (uint8)(0x01u << UART2DYNAMIXEL_CTRL_HD_SEND_SHIFT)
#define UART2DYNAMIXEL_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART2DYNAMIXEL_CTRL_HD_SEND_BREAK_SHIFT)
#define UART2DYNAMIXEL_CTRL_MARK                  (uint8)(0x01u << UART2DYNAMIXEL_CTRL_MARK_SHIFT)
#define UART2DYNAMIXEL_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART2DYNAMIXEL_CTRL_PARITY_TYPE0_SHIFT)
#define UART2DYNAMIXEL_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART2DYNAMIXEL_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART2DYNAMIXEL_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART2DYNAMIXEL_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART2DYNAMIXEL_SEND_BREAK                         (0x00u)
#define UART2DYNAMIXEL_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART2DYNAMIXEL_REINIT                             (0x02u)
#define UART2DYNAMIXEL_SEND_WAIT_REINIT                   (0x03u)

#define UART2DYNAMIXEL_OVER_SAMPLE_8                      (8u)
#define UART2DYNAMIXEL_OVER_SAMPLE_16                     (16u)

#define UART2DYNAMIXEL_BIT_CENTER                         (UART2DYNAMIXEL_OVER_SAMPLE_COUNT - 2u)

#define UART2DYNAMIXEL_FIFO_LENGTH                        (4u)
#define UART2DYNAMIXEL_NUMBER_OF_START_BIT                (1u)
#define UART2DYNAMIXEL_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART2DYNAMIXEL_TXBITCTR_BREAKBITS8X   ((UART2DYNAMIXEL_BREAK_BITS_TX * UART2DYNAMIXEL_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART2DYNAMIXEL_TXBITCTR_BREAKBITS ((UART2DYNAMIXEL_BREAK_BITS_TX * UART2DYNAMIXEL_OVER_SAMPLE_COUNT) - 1u)

#define UART2DYNAMIXEL_HALF_BIT_COUNT   \
                            (((UART2DYNAMIXEL_OVER_SAMPLE_COUNT / 2u) + (UART2DYNAMIXEL_USE23POLLING * 1u)) - 2u)
#if (UART2DYNAMIXEL_OVER_SAMPLE_COUNT == UART2DYNAMIXEL_OVER_SAMPLE_8)
    #define UART2DYNAMIXEL_HD_TXBITCTR_INIT   (((UART2DYNAMIXEL_BREAK_BITS_TX + \
                            UART2DYNAMIXEL_NUMBER_OF_START_BIT) * UART2DYNAMIXEL_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART2DYNAMIXEL_RXBITCTR_INIT  ((((UART2DYNAMIXEL_BREAK_BITS_RX + UART2DYNAMIXEL_NUMBER_OF_START_BIT) \
                            * UART2DYNAMIXEL_OVER_SAMPLE_COUNT) + UART2DYNAMIXEL_HALF_BIT_COUNT) - 1u)

#else /* UART2DYNAMIXEL_OVER_SAMPLE_COUNT == UART2DYNAMIXEL_OVER_SAMPLE_16 */
    #define UART2DYNAMIXEL_HD_TXBITCTR_INIT   ((8u * UART2DYNAMIXEL_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART2DYNAMIXEL_RXBITCTR_INIT      (((7u * UART2DYNAMIXEL_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART2DYNAMIXEL_HALF_BIT_COUNT)
#endif /* End UART2DYNAMIXEL_OVER_SAMPLE_COUNT */

#define UART2DYNAMIXEL_HD_RXBITCTR_INIT                   UART2DYNAMIXEL_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART2DYNAMIXEL_initVar;
#if (UART2DYNAMIXEL_TX_INTERRUPT_ENABLED && UART2DYNAMIXEL_TX_ENABLED)
    extern volatile uint8 UART2DYNAMIXEL_txBuffer[UART2DYNAMIXEL_TX_BUFFER_SIZE];
    extern volatile uint8 UART2DYNAMIXEL_txBufferRead;
    extern uint8 UART2DYNAMIXEL_txBufferWrite;
#endif /* (UART2DYNAMIXEL_TX_INTERRUPT_ENABLED && UART2DYNAMIXEL_TX_ENABLED) */
#if (UART2DYNAMIXEL_RX_INTERRUPT_ENABLED && (UART2DYNAMIXEL_RX_ENABLED || UART2DYNAMIXEL_HD_ENABLED))
    extern uint8 UART2DYNAMIXEL_errorStatus;
    extern volatile uint8 UART2DYNAMIXEL_rxBuffer[UART2DYNAMIXEL_RX_BUFFER_SIZE];
    extern volatile uint8 UART2DYNAMIXEL_rxBufferRead;
    extern volatile uint8 UART2DYNAMIXEL_rxBufferWrite;
    extern volatile uint8 UART2DYNAMIXEL_rxBufferLoopDetect;
    extern volatile uint8 UART2DYNAMIXEL_rxBufferOverflow;
    #if (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART2DYNAMIXEL_rxAddressMode;
        extern volatile uint8 UART2DYNAMIXEL_rxAddressDetected;
    #endif /* (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED) */
#endif /* (UART2DYNAMIXEL_RX_INTERRUPT_ENABLED && (UART2DYNAMIXEL_RX_ENABLED || UART2DYNAMIXEL_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART2DYNAMIXEL__B_UART__AM_SW_BYTE_BYTE 1
#define UART2DYNAMIXEL__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART2DYNAMIXEL__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART2DYNAMIXEL__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART2DYNAMIXEL__B_UART__AM_NONE 0

#define UART2DYNAMIXEL__B_UART__NONE_REVB 0
#define UART2DYNAMIXEL__B_UART__EVEN_REVB 1
#define UART2DYNAMIXEL__B_UART__ODD_REVB 2
#define UART2DYNAMIXEL__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART2DYNAMIXEL_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART2DYNAMIXEL_NUMBER_OF_STOP_BITS    (1u)

#if (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED)
    #define UART2DYNAMIXEL_RX_ADDRESS_MODE    (0u)
    #define UART2DYNAMIXEL_RX_HW_ADDRESS1     (0u)
    #define UART2DYNAMIXEL_RX_HW_ADDRESS2     (0u)
#endif /* (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED) */

#define UART2DYNAMIXEL_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART2DYNAMIXEL_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_RX_STS_OVERRUN_SHIFT))

#define UART2DYNAMIXEL_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART2DYNAMIXEL_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART2DYNAMIXEL_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2DYNAMIXEL_CONTROL_REG \
                            (* (reg8 *) UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART2DYNAMIXEL_CONTROL_PTR \
                            (  (reg8 *) UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2DYNAMIXEL_TX_ENABLED)
    #define UART2DYNAMIXEL_TXDATA_REG          (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2DYNAMIXEL_TXDATA_PTR          (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2DYNAMIXEL_TXDATA_AUX_CTL_REG  (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2DYNAMIXEL_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2DYNAMIXEL_TXSTATUS_REG        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__STATUS_REG)
    #define UART2DYNAMIXEL_TXSTATUS_PTR        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__STATUS_REG)
    #define UART2DYNAMIXEL_TXSTATUS_MASK_REG   (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__MASK_REG)
    #define UART2DYNAMIXEL_TXSTATUS_MASK_PTR   (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__MASK_REG)
    #define UART2DYNAMIXEL_TXSTATUS_ACTL_REG   (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART2DYNAMIXEL_TXSTATUS_ACTL_PTR   (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART2DYNAMIXEL_TXCLKGEN_DP)
        #define UART2DYNAMIXEL_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2DYNAMIXEL_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2DYNAMIXEL_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART2DYNAMIXEL_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART2DYNAMIXEL_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2DYNAMIXEL_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2DYNAMIXEL_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2DYNAMIXEL_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2DYNAMIXEL_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART2DYNAMIXEL_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART2DYNAMIXEL_TXCLKGEN_DP */

#endif /* End UART2DYNAMIXEL_TX_ENABLED */

#if(UART2DYNAMIXEL_HD_ENABLED)

    #define UART2DYNAMIXEL_TXDATA_REG             (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2DYNAMIXEL_TXDATA_PTR             (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2DYNAMIXEL_TXDATA_AUX_CTL_REG     (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART2DYNAMIXEL_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2DYNAMIXEL_TXSTATUS_REG           (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_REG )
    #define UART2DYNAMIXEL_TXSTATUS_PTR           (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_REG )
    #define UART2DYNAMIXEL_TXSTATUS_MASK_REG      (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__MASK_REG )
    #define UART2DYNAMIXEL_TXSTATUS_MASK_PTR      (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__MASK_REG )
    #define UART2DYNAMIXEL_TXSTATUS_ACTL_REG      (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2DYNAMIXEL_TXSTATUS_ACTL_PTR      (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART2DYNAMIXEL_HD_ENABLED */

#if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
    #define UART2DYNAMIXEL_RXDATA_REG             (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2DYNAMIXEL_RXDATA_PTR             (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2DYNAMIXEL_RXADDRESS1_REG         (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2DYNAMIXEL_RXADDRESS1_PTR         (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2DYNAMIXEL_RXADDRESS2_REG         (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2DYNAMIXEL_RXADDRESS2_PTR         (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2DYNAMIXEL_RXDATA_AUX_CTL_REG     (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2DYNAMIXEL_RXBITCTR_PERIOD_REG    (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2DYNAMIXEL_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2DYNAMIXEL_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2DYNAMIXEL_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2DYNAMIXEL_RXBITCTR_COUNTER_REG   (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART2DYNAMIXEL_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART2DYNAMIXEL_RXSTATUS_REG           (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_REG )
    #define UART2DYNAMIXEL_RXSTATUS_PTR           (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_REG )
    #define UART2DYNAMIXEL_RXSTATUS_MASK_REG      (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__MASK_REG )
    #define UART2DYNAMIXEL_RXSTATUS_MASK_PTR      (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__MASK_REG )
    #define UART2DYNAMIXEL_RXSTATUS_ACTL_REG      (* (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2DYNAMIXEL_RXSTATUS_ACTL_PTR      (  (reg8 *) UART2DYNAMIXEL_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */

#if(UART2DYNAMIXEL_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART2DYNAMIXEL_INTCLOCK_CLKEN_REG     (* (reg8 *) UART2DYNAMIXEL_IntClock__PM_ACT_CFG)
    #define UART2DYNAMIXEL_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART2DYNAMIXEL_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART2DYNAMIXEL_INTCLOCK_CLKEN_MASK    UART2DYNAMIXEL_IntClock__PM_ACT_MSK
#endif /* End UART2DYNAMIXEL_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART2DYNAMIXEL_TX_ENABLED)
    #define UART2DYNAMIXEL_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART2DYNAMIXEL_TX_ENABLED */

#if(UART2DYNAMIXEL_HD_ENABLED)
    #define UART2DYNAMIXEL_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART2DYNAMIXEL_HD_ENABLED */

#if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
    #define UART2DYNAMIXEL_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART2DYNAMIXEL_WAIT_1_MS      UART2DYNAMIXEL_BL_CHK_DELAY_MS   

#define UART2DYNAMIXEL_TXBUFFERSIZE   UART2DYNAMIXEL_TX_BUFFER_SIZE
#define UART2DYNAMIXEL_RXBUFFERSIZE   UART2DYNAMIXEL_RX_BUFFER_SIZE

#if (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED)
    #define UART2DYNAMIXEL_RXADDRESSMODE  UART2DYNAMIXEL_RX_ADDRESS_MODE
    #define UART2DYNAMIXEL_RXHWADDRESS1   UART2DYNAMIXEL_RX_HW_ADDRESS1
    #define UART2DYNAMIXEL_RXHWADDRESS2   UART2DYNAMIXEL_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART2DYNAMIXEL_RXAddressMode  UART2DYNAMIXEL_RXADDRESSMODE
#endif /* (UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART2DYNAMIXEL_initvar                    UART2DYNAMIXEL_initVar

#define UART2DYNAMIXEL_RX_Enabled                 UART2DYNAMIXEL_RX_ENABLED
#define UART2DYNAMIXEL_TX_Enabled                 UART2DYNAMIXEL_TX_ENABLED
#define UART2DYNAMIXEL_HD_Enabled                 UART2DYNAMIXEL_HD_ENABLED
#define UART2DYNAMIXEL_RX_IntInterruptEnabled     UART2DYNAMIXEL_RX_INTERRUPT_ENABLED
#define UART2DYNAMIXEL_TX_IntInterruptEnabled     UART2DYNAMIXEL_TX_INTERRUPT_ENABLED
#define UART2DYNAMIXEL_InternalClockUsed          UART2DYNAMIXEL_INTERNAL_CLOCK_USED
#define UART2DYNAMIXEL_RXHW_Address_Enabled       UART2DYNAMIXEL_RXHW_ADDRESS_ENABLED
#define UART2DYNAMIXEL_OverSampleCount            UART2DYNAMIXEL_OVER_SAMPLE_COUNT
#define UART2DYNAMIXEL_ParityType                 UART2DYNAMIXEL_PARITY_TYPE

#if( UART2DYNAMIXEL_TX_ENABLED && (UART2DYNAMIXEL_TXBUFFERSIZE > UART2DYNAMIXEL_FIFO_LENGTH))
    #define UART2DYNAMIXEL_TXBUFFER               UART2DYNAMIXEL_txBuffer
    #define UART2DYNAMIXEL_TXBUFFERREAD           UART2DYNAMIXEL_txBufferRead
    #define UART2DYNAMIXEL_TXBUFFERWRITE          UART2DYNAMIXEL_txBufferWrite
#endif /* End UART2DYNAMIXEL_TX_ENABLED */
#if( ( UART2DYNAMIXEL_RX_ENABLED || UART2DYNAMIXEL_HD_ENABLED ) && \
     (UART2DYNAMIXEL_RXBUFFERSIZE > UART2DYNAMIXEL_FIFO_LENGTH) )
    #define UART2DYNAMIXEL_RXBUFFER               UART2DYNAMIXEL_rxBuffer
    #define UART2DYNAMIXEL_RXBUFFERREAD           UART2DYNAMIXEL_rxBufferRead
    #define UART2DYNAMIXEL_RXBUFFERWRITE          UART2DYNAMIXEL_rxBufferWrite
    #define UART2DYNAMIXEL_RXBUFFERLOOPDETECT     UART2DYNAMIXEL_rxBufferLoopDetect
    #define UART2DYNAMIXEL_RXBUFFER_OVERFLOW      UART2DYNAMIXEL_rxBufferOverflow
#endif /* End UART2DYNAMIXEL_RX_ENABLED */

#ifdef UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2DYNAMIXEL_CONTROL                UART2DYNAMIXEL_CONTROL_REG
#endif /* End UART2DYNAMIXEL_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2DYNAMIXEL_TX_ENABLED)
    #define UART2DYNAMIXEL_TXDATA                 UART2DYNAMIXEL_TXDATA_REG
    #define UART2DYNAMIXEL_TXSTATUS               UART2DYNAMIXEL_TXSTATUS_REG
    #define UART2DYNAMIXEL_TXSTATUS_MASK          UART2DYNAMIXEL_TXSTATUS_MASK_REG
    #define UART2DYNAMIXEL_TXSTATUS_ACTL          UART2DYNAMIXEL_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART2DYNAMIXEL_TXCLKGEN_DP)
        #define UART2DYNAMIXEL_TXBITCLKGEN_CTR        UART2DYNAMIXEL_TXBITCLKGEN_CTR_REG
        #define UART2DYNAMIXEL_TXBITCLKTX_COMPLETE    UART2DYNAMIXEL_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART2DYNAMIXEL_TXBITCTR_PERIOD        UART2DYNAMIXEL_TXBITCTR_PERIOD_REG
        #define UART2DYNAMIXEL_TXBITCTR_CONTROL       UART2DYNAMIXEL_TXBITCTR_CONTROL_REG
        #define UART2DYNAMIXEL_TXBITCTR_COUNTER       UART2DYNAMIXEL_TXBITCTR_COUNTER_REG
    #endif /* UART2DYNAMIXEL_TXCLKGEN_DP */
#endif /* End UART2DYNAMIXEL_TX_ENABLED */

#if(UART2DYNAMIXEL_HD_ENABLED)
    #define UART2DYNAMIXEL_TXDATA                 UART2DYNAMIXEL_TXDATA_REG
    #define UART2DYNAMIXEL_TXSTATUS               UART2DYNAMIXEL_TXSTATUS_REG
    #define UART2DYNAMIXEL_TXSTATUS_MASK          UART2DYNAMIXEL_TXSTATUS_MASK_REG
    #define UART2DYNAMIXEL_TXSTATUS_ACTL          UART2DYNAMIXEL_TXSTATUS_ACTL_REG
#endif /* End UART2DYNAMIXEL_HD_ENABLED */

#if( (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) )
    #define UART2DYNAMIXEL_RXDATA                 UART2DYNAMIXEL_RXDATA_REG
    #define UART2DYNAMIXEL_RXADDRESS1             UART2DYNAMIXEL_RXADDRESS1_REG
    #define UART2DYNAMIXEL_RXADDRESS2             UART2DYNAMIXEL_RXADDRESS2_REG
    #define UART2DYNAMIXEL_RXBITCTR_PERIOD        UART2DYNAMIXEL_RXBITCTR_PERIOD_REG
    #define UART2DYNAMIXEL_RXBITCTR_CONTROL       UART2DYNAMIXEL_RXBITCTR_CONTROL_REG
    #define UART2DYNAMIXEL_RXBITCTR_COUNTER       UART2DYNAMIXEL_RXBITCTR_COUNTER_REG
    #define UART2DYNAMIXEL_RXSTATUS               UART2DYNAMIXEL_RXSTATUS_REG
    #define UART2DYNAMIXEL_RXSTATUS_MASK          UART2DYNAMIXEL_RXSTATUS_MASK_REG
    #define UART2DYNAMIXEL_RXSTATUS_ACTL          UART2DYNAMIXEL_RXSTATUS_ACTL_REG
#endif /* End  (UART2DYNAMIXEL_RX_ENABLED) || (UART2DYNAMIXEL_HD_ENABLED) */

#if(UART2DYNAMIXEL_INTERNAL_CLOCK_USED)
    #define UART2DYNAMIXEL_INTCLOCK_CLKEN         UART2DYNAMIXEL_INTCLOCK_CLKEN_REG
#endif /* End UART2DYNAMIXEL_INTERNAL_CLOCK_USED */

#define UART2DYNAMIXEL_WAIT_FOR_COMLETE_REINIT    UART2DYNAMIXEL_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART2DYNAMIXEL_H */


/* [] END OF FILE */
