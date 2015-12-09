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

#ifndef _CAN_INSTRUCTION_H_
#define _CAN_INSTRUCTION_H_

#define CAN_HARDWARE_FILTER_ID              0x30
    
    
//CAN Instruction list
#define CAN_INSTRUCTION_SET_Z_AXIS_HOME     0
#define CAN_INSTRUCTION_SET_Z_AXIS_POSITION 1
    
#define CAN_INSTRUCTION_OPEN_GRIPPER        2
#define CAN_INSTRUCTION_SET_MOVING_SPEED    3
#define CAN_INSTRUCTION_SET_TORQUE          4
#define CAN_INSTRUCTION_SET_TORQUE_ENABLE   5

#define CAN_INSTRUCTION_TILT                6
#define CAN_INSTRUCTION_ROTATE              7
#define CAN_INSTRUCTION_MOVE                8

#define CAN_INSTRUCTION_GET_DATA			9
#define CAN_INSTRUCTION_SET_DATA			10
    
#define CAN_INSTRUCTION_CLOCK_4M            11
#define CAN_INSTRUCTION_CLOCK_8M            12

#define CAN_INSTRUCTION_GET_MOTOR_TYPE      13
#define CAN_INSTRUCTION_SET_MOTOR_TYPE      14
    
#define CAN_INSTRUCTION_GET_MODEL_FIRMWARE 254
    
    
#endif
/* [] END OF FILE */
