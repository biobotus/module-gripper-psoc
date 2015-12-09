
#include "DynamixelCom.h"

void sendDynamixelDataToComputer(uint8 *packet);


// ------- VARIABLES RECEPTION DYNAMIXEL ---------
volatile uint8 dynamixelReceivedBuffer[256];
volatile int16 dynamixelbufferPos = 0;
uint16 dynamixelSendDataPos = 0;
extern uint8 treatingAddress;
// ----------------------------

uint8 motorType[];


void init_uart_dynamixel() 
{
    UART2DYNAMIXEL_Start();
	UART2DYNAMIXEL_ClearRxBuffer();
	UART2DYNAMIXEL_ClearTxBuffer();  
    isr_rx_interrupt_StartEx(isr_uart_rx_gripper);
    UART2DYNAMIXEL_EnableRxInt();
}


// Interruption function for the RX UART (data sent by motors)
CY_ISR(isr_uart_rx_gripper)
{
    // read one byte
    dynamixelbufferPos = (dynamixelbufferPos+1)%255;
    dynamixelReceivedBuffer[dynamixelbufferPos] = UART2DYNAMIXEL_GetByte();
    
    if (dynamixelbufferPos > 2)
    {
        if (!(dynamixelbufferPos < (3 + dynamixelReceivedBuffer[3])))
        {
            while((UART2DYNAMIXEL_TXSTATUS_REG & UART2DYNAMIXEL_TX_STS_FIFO_FULL) != 0u)
            {
                // Wait for room in the FIFO 
            }
            
            uint8 tmp[10];
            memcpy ( &tmp, (const uint8*)dynamixelReceivedBuffer, 10 );
            
            
            // TODO: ERROR HANDLING
            //if(dynamixelReceivedBuffer[dynamixelReceivedBuffer[3]+3] == dynamixelCalculateChecksum(tmp)) 
            
            sendDynamixelDataToComputer(tmp);
            
            UART2DYNAMIXEL_ClearRxBuffer();
            UART2DYNAMIXEL_ClearTxBuffer(); 
            dynamixelbufferPos = -1;
        }
    } else if(dynamixelbufferPos < 2) {
        if (dynamixelReceivedBuffer[dynamixelbufferPos] != 0xff)
        {
            dynamixelbufferPos = -1;
        }
    }
}


void sendPacketToDynamixel(uint8 *packet)
{
    // send data to dynamixel
    UART2DYNAMIXEL_PutArray(packet, 9);
    while(UART2DYNAMIXEL_GetTxBufferSize() != 0) {};
    
    free(packet);
}


void sendCanPacketToDynamixel(uint8 *canPacket)
{
    uint8 i;
    uint8 packet[20];
    
    packet[0] = 0xff;
    packet[1] = 0xff;
    packet[2] = canPacket[1]; // ID MOTEUR
    packet[3] = canPacket[2]; // LENGTH
    for(i=0; i < packet[3]; i++) {
       packet[4+i] = canPacket[3+i];
    }
    
    // send data to dynamixel
    UART2DYNAMIXEL_PutArray(packet, 9);
    while(UART2DYNAMIXEL_GetTxBufferSize() != 0) {};
}


void sendDynamixelDataToComputer(uint8 *packet) 
{   
    CAN_MSG canMsg;
    uint8 i;
    
    // index        :  0    1      2         3        4
    // packet format: [ff] [ff] [MotorID] [Length] [ERROR] [.. data]

    // index        :   0            1            2         3
    // can format   : [ERROR] [TreatingFunc] [MotorID] [.. data]
    
    // test
    // T: [0] [2] [4] [2] [0] [2] [F5] [0]
    // R: [0] [2] [4] [0] [C] [0] [ED] [0]
    //  
    
    canMsg.msgBytes.byte[0] = packet[4];
    canMsg.msgBytes.byte[1] = CAN_HARDWARE_FILTER_ID;
    canMsg.msgBytes.byte[2] = treatingAddress; // Treating function
    canMsg.msgBytes.byte[3] = packet[2]; // ID MOTEUR
    for(i=0; i < packet[3]-1; i++) {	// [data] [..] [data]
       canMsg.msgBytes.byte[4+i] = packet[5+i];
    }
    i += 3;
    canMsg.DLC = i; // number of bytes to send
    
    can_sendMessage(&canMsg, CAN_COMPUTER_ID);
}

/* [] END OF FILE */
