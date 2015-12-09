/*******************************************************************************
* File Name: UART2USBINT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART2USB.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART2USB_RX_INTERRUPT_ENABLED && (UART2USB_RX_ENABLED || UART2USB_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART2USB_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART2USB_rxBuffer - RAM buffer pointer for save received data.
    *  UART2USB_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART2USB_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART2USB_rxBufferOverflow - software overflow flag. Set to one
    *     when UART2USB_rxBufferWrite index overtakes
    *     UART2USB_rxBufferRead index.
    *  UART2USB_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART2USB_rxBufferWrite is equal to
    *    UART2USB_rxBufferRead
    *  UART2USB_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART2USB_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART2USB_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART2USB_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        readData UART2USB_RXSTATUS_REG;

        if((readData & (UART2USB_RX_STS_BREAK | UART2USB_RX_STS_PAR_ERROR |
                        UART2USB_RX_STS_STOP_ERROR | UART2USB_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            UART2USB_errorStatus readData & ( UART2USB_RX_STS_BREAK | 
                                                        UART2USB_RX_STS_PAR_ERROR | 
                                                        UART2USB_RX_STS_STOP_ERROR | 
                                                        UART2USB_RX_STS_OVERRUN);
            /* `#START UART2USB_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART2USB_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
        #if (UART2USB_RXHW_ADDRESS_ENABLED)
            if(UART2USB_rxAddressMode == (uint8)UART2USB__B_UART__AM_SW_DETECT_TO_BUFFER)
            {
                if((readData & UART2USB_RX_STS_MRKSPC) != 0u)
                {
                    if ((readData & UART2USB_RX_STS_ADDR_MATCH) != 0u)
                    {
                        UART2USB_rxAddressDetected 1u;
                    }
                    else
                    {
                        UART2USB_rxAddressDetected 0u;
                    }
                }

                readData UART2USB_RXDATA_REG;
                if(UART2USB_rxAddressDetected != 0u)
                {   /* Store only addressed data */
                    UART2USB_rxBuffer[UART2USB_rxBufferWrite] readData;
                    increment_pointer 1u;
                }
            }
            else /* Without software addressing */
            {
                UART2USB_rxBuffer[UART2USB_rxBufferWrite] UART2USB_RXDATA_REG;
                increment_pointer 1u;
            }
        #else  /* Without addressing */
            UART2USB_rxBuffer[UART2USB_rxBufferWrite] UART2USB_RXDATA_REG;
            increment_pointer 1u;
        #endif /* (UART2USB_RXHW_ADDRESS_ENABLED) */

            /* Do not increment buffer pointer when skip not addressed data */
            if(increment_pointer != 0u)
            {
                if(UART2USB_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART2USB_rxBufferOverflow 1u;
                }
                /* Set next pointer. */
                UART2USB_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART2USB_rxBufferWrite >= UART2USB_RX_BUFFER_SIZE)
                {
                    UART2USB_rxBufferWrite 0u;
                }

                /* Detect pre-overload condition and set flag */
                if(UART2USB_rxBufferWrite == UART2USB_rxBufferRead)
                {
                    UART2USB_rxBufferLoopDetect 1u;
                    /* When Hardware Flow Control selected */
                    #if (UART2USB_FLOW_CONTROL != 0u)
                        /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                        UART2USB_RXSTATUS_MASK_REG  &= (uint8)~UART2USB_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART2USB_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* (UART2USB_FLOW_CONTROL != 0u) */
                }
            }

            /* Read status to decide whether read more bytes */
            readData UART2USB_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART2USB_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART2USB_RX_INTERRUPT_ENABLED && (UART2USB_RX_ENABLED || UART2USB_HD_ENABLED)) */


#if (UART2USB_TX_INTERRUPT_ENABLED && UART2USB_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART2USB_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART2USB_txBuffer - RAM buffer pointer for transmit data from.
    *  UART2USB_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART2USB_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART2USB_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START UART2USB_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART2USB_txBufferRead != UART2USB_txBufferWrite) &&
             ((UART2USB_TXSTATUS_REG & UART2USB_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART2USB_txBufferRead >= UART2USB_TX_BUFFER_SIZE)
            {
                UART2USB_txBufferRead 0u;
            }

            UART2USB_TXDATA_REG UART2USB_txBuffer[UART2USB_txBufferRead];

            /* Set next pointer */
            UART2USB_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART2USB_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (UART2USB_TX_INTERRUPT_ENABLED && UART2USB_TX_ENABLED) */


/* [] END OF FILE */
