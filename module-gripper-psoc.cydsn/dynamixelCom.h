/* ========================================
 *
 * Autor: Dave Plouffe
 *
 * This file is used to send data to dynamixel's motors
 * and to send dynamixel's received data to the computer.
 *
 * Each time a dynamixel sends data, it will be automatically
 * sent to the computer.
 *
 * The variable called "treatingAddress" must be set before
 * we receive data from dynamixels. This variable is used
 * in the computer application as a filter. In other words,
 * it helps the computeur application to know where to treat
 * the CAN message it has received.
 *
 * ========================================
*/

#ifndef _DYNAMIXEL_COMMUNICATION_H__
#define _DYNAMIXEL_COMMUNICATION_H__ 
    
#include <device.h>
#include <project.h>
#include "CANCommunication.h"
#include "gripperCANInstruction.h"  
#include "dynamixelPacket.h"
#include "gripperEeprom.h"

CY_ISR(isr_uart_rx_gripper);

void init_uart_dynamixel();

void sendPacketToDynamixel(uint8 *packet);
void sendCanPacketToDynamixel(uint8 *canPacket);


#endif
/* [] END OF FILE */
