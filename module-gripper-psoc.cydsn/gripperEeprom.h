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
#ifndef __EEPROM_GRIPPER_H__
#define __EEPROM_GRIPPER_H__

//#include <project.h>
#include <device.h>
#include "DynamixelPacket.h"

#define EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID    1
#define EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID      2
#define EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID     3
#define EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID      4

#define EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_L   5
#define EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_H   6
#define EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_L  7
#define EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_H  8
#define EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_L    9
#define EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_H    10
#define EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_L   11
#define EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_H   12


#define MOTOR_LEFT_ANGLE_CW    0
#define MOTOR_LEFT_ANGLE_CCW   1
#define MOTOR_RIGHT_ANGLE_CW   2
#define MOTOR_RIGHT_ANGLE_CCW  3

extern uint16 motorAngleLimits[4];


#define MOTOR_TYPE_NONE     0
#define MOTOR_TYPE_ROTATE   1
#define MOTOR_TYPE_TILT     2
#define MOTOR_TYPE_RIGHT    3
#define MOTOR_TYPE_LEFT     4
#define NB_OF_MOTOR_TYPE    5
// motorType = {none, rotate, tilt, right, left}
extern uint8 motorType[NB_OF_MOTOR_TYPE];


void init_eeprom();
void readEeprom();
void eraseMotorType(uint8 motorID);
void saveMotorType(uint8 motorID, uint8 type);
uint8 getMotorType(uint8 motorID);
void updateAngleLimitData(uint8 *packet);

#endif
/* [] END OF FILE */
