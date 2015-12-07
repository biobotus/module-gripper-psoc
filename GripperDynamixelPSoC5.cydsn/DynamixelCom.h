/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef _DYNAMIXEL_COMMUNICATION_H__
#define _DYNAMIXEL_COMMUNICATION_H__ 
    
#include <device.h>
#include <project.h>
#include "CAN_Communication.h"
#include "CANInstruction.h"  
#include "DynamixelPacket.h"
#include "gripper_eeprom.h"

CY_ISR(isr_uart_rx_gripper);

void init_uart_dynamixel();

void sendPacketToDynamixel(uint8 *packet);
void sendCanPacketToDynamixel(uint8 *canPacket);
void sendDynamixelDataToComputer(uint8 *packet);


#endif
/* [] END OF FILE */
