/* ========================================
 *
 * Copyright BioBot Instrumentation, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF BioBot Instrumentation.
 *
 * WRITTEN BY : Philippe-Antoine Major &
 *              Louis-Vincent Major
 * ========================================
*/

#ifndef __CAN_COMMUNICATION_H__
#define __CAN_COMMUNICATION_H__

#include <project.h>

// GLOBAL DEFINITIONS FOR THE CAN BUS.
#define MAX_MSG_BUFFER_SIZE         (50)    // Maximum amount of bytes to be stored in the CAN_MSG_BUFFER
#define MASTER_ID                   (0xFF)
#define MSG_RTR                     (0)
#define MSG_IDE                     (0)
#define MSG_IRQ                     (0)
#define DATALENGTH                  0x08

//Device ID
#define CAN_COMPUTER_ID                 (0xFF)

#ifndef CAN_COMMUNICATION_H
#define CAN_COMMUNICATION_H
// Structure of a basic CAN Message.
typedef struct
{
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 sst;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
    CAN_1_DATA_BYTES_MSG msgBytes;
    uint8 DLC;
    uint32 CAN_ID;
}CAN_MSG;
#endif

// Definitions and variables used throughout the entire program.
extern int msgToBeTreatedIndex;
extern int msgToBeStoredIndex;
extern int messageToBeTreatedCount;
extern CAN_MSG receivedMsgs[MAX_MSG_BUFFER_SIZE];

// Declaration of the functions used with the CAN bus.
CAN_MSG can_getReceivedMessage(void);
int8 can_sendMessage(CAN_MSG* msgPtr, uint32 ID);
void sendDataToCAN(uint8 instruction, uint8 byte1, uint8 byte2, uint8 byte3, uint8 byte4, uint8 byte5, uint8 byte6, uint8 byte7);


#endif
/* [] END OF FILE */
