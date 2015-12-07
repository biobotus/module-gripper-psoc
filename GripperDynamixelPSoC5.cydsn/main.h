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
#ifndef _MAIN_H_
#define _MAIN_H_

#include <device.h>
#include <stdlib.h>
#include "CANInstruction.h"
#include "CAN_Communication.h"
#include "Z_Axis.h"
#include "DynamixelCom.h"
#include "DynamixelPacket.h"
#include "gripper_eeprom.h"
#include <stdlib.h>

CY_ISR(CounterCanInterruptHandler);

void init_can_module();
uint8 treatCanMessage(uint8* canPacket);
void sendMotorTypeToComputer(unsigned char id);

#endif
/* [] END OF FILE */
