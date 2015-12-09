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
#include "gripperCANInstruction.h"
#include "CANCommunication.h"
#include "zaxis.h"
#include "dynamixelCom.h"
#include "dynamixelPacket.h"
#include "gripperEeprom.h"
#include <stdlib.h>

CY_ISR(CounterCanInterruptHandler);

void init_can_module();
uint8 treatCanMessage(uint8* canPacket);

#endif
/* [] END OF FILE */
