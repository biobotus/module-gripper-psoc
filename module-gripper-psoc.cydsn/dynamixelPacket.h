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

#ifndef _DYNAMIXEL_PACKET_H_
#define _DYNAMIXEL_PACKET_H_

#include <project.h>
#include <stdlib.h>
    
#define DYNAMIXEL_BROADCAST_ID    0xFE
    
 // INSTRUCTIONS
#define DYNAMIXEL_INST_PING       0x01        // Used to obtain a Status Packet
#define DYNAMIXEL_INST_READ       0x02        // Reading values in Control Table
#define DYNAMIXEL_INST_WRITE      0x03        // Writing values in Control Table
#define DYNAMIXEL_INST_REG_WRITE  0x04        // Write data byte to REGISTERED_INSTRUCION
#define DYNAMIXEL_INST_ACTION     0x05        // Triggers the action stored byteo REGISTERED_INSTRUCTION
#define DYNAMIXEL_INST_RESET      0x06        // Change the control table values to the factory default values
#define DYNAMIXEL_INST_SYNC_WRITE 0x83        // Used to control many Dynamixel actuators at the same time

    
// EEPROM ADDRESS
#define MODEL_NUMBER_L          0       // RD, Model Number, 0x000C for AX-12
#define MODEL_NUMBER_H          1       // RD
#define FIRMWARE                2       // RD, Firmware Version

#define ID                      3       // RD-WR, Unique ID
#define BAUD_RATE               4       // RD-WR, Baud Rate, see page 14/38 of Datasheet
    // data = 1 -> 1Mbps
    // data = 3 -> 0.5Mbps
    
#define RETURN_DELAY_TIME       5       // RD-WR, Return Delay Time, time is given by (2usec * RETURN_VALUE_TIME)

#define CW_ANGLE_LIMIT_L        6       // RD-WR, Clock-Wise Angle Limit
#define CW_ANGLE_LIMIT_H        7       // RD-WR
#define CCW_ANGLE_LIMIT_L       8       // RD-WR, Counter-Clock-Wise Angle Limit
#define CCW_ANGLE_LIMIT_H       9       // RD-WR

#define TEMPERATURE_LIMIT       11      // RD-WR, Highest Limit Temperature, If Temperature goes higher than the specficied value, Over Heating Error Bit 1 (Bit 2 of the Status Packet)and an alarm will be set by address 17 and 18.
#define LOWEST_LIMIT_VOLTAGE    12      // RD-WR, Lowest Limit Voltage, If voltage out of specified range, Voltage Range Error Bit 1 (Bit 0 of Status Packet) and an alarm will be set by address 17 and 18.
#define HIGHEST_LIMIT_VOLTAGE   13      // RD-WR, Highest Limit Voltage, Values are 10 times the actual voltage

#define MAX_TORQUE_L            14      // RD-WR, Maximum torque output, when set to 0, actuator goes in Free Run mode
#define MAX_TORQUE_H            15      // RD-WR, Torque limited by value in the RAM Torque_Limit

#define RETURN_LEVEL            16      // RD-WR, Determine if the Dynamixel return a Status Packet after receiving an Instruction Packet, 0 No Respond, 1 Respond only to READ_DATA INST, 2 Respond to all instruction

#define ALARM_LED               17      // RD-WR, Set if LED should blink for the different errors, see table page 16/38 of datasheet
#define ALARM_SHUTDOWN          18      // RD-WR, Set if Actuator should shutdown when different alarm occurs, see table page 16/38 of datasheet

#define MULTI_TURN_OFFSET_L     20      // RD-WR, Adjusts position (zeroing). This value gets included in Present Position (36).
#define MULTI_TURN_OFFSET_H     21      // RD-WR, Present position + multi-turn offset.
#define RESOLUTION_DIVIDER      22      // RD-WR, It allows the user to change Dynamixel’s resolution.

#define DOWN_CALIBRATION_L      20      // RD, Data used for compensating for the differences betwwen the potentiometers used in the Dynamixel
#define DOWN_CALIBRATION_H      21      // RD
#define UP_CALIBRATION_L        22      // RD
#define UP_CALIBRATION_H        23      // RD


//RAM AREA
#define TORQUE_ENABLE           (24)    // RD-WR, Initial value 0 Free Run Mode, to Enable Torque Control set value to 1
#define LED                     (25)    // RD-WR, LED turns on if value 1, turns off when value 0

#define CW_COMPLIANCE_MARGIN    (26)    // RD-WR, See graph page 17/38 of datasheet
#define CCW_COMPLIANCE_MARGIN   (27)    // RD-WR, See graph page 17/38 of datasheet
#define CW_COMPLIANCE_SLOPE     (28)    // RD-WR, See graph page 17/38 of datasheet
#define CCW_COMPLIANCE_SLOPE    (29)    // RD-WR, See graph page 17/38 of datasheet

#define GOAL_POSITION_L         (30)    // RD-WR, Requested angular position between 0 and 300 degree, 0x0 0 degree, 0x1ff 150 degree, 0x3ff 300 degree
#define GOAL_POSITION_H         (31)    // RD-WR, Values range between 0 and 1023 (0x3ff)

#define MOVING_SPEED_L          (32)    // RD-WR, Set the angular velocity pf the output moving to the goal position. 0x3ff max velocity 114 rpm, lowest velocity 0x1, 0x0 highest velocity for supplied voltage
#define MOVING_SPEED_H          (33)    // RD-WR, See table page 19/38 of datasheet

#define TORQUE_LIMIT_L          (34)    // RD-WR, When turned on, MAX_TORQUE_L/H is copied byteo TORQUE_LIMIT_L/H
#define TORQUE_LIMIT_H          (35)    // RD-WR

#define PRESENT_POSITION_L      (36)    // RD, Current angular position
#define PRESENT_POSITION_H      (37)    // RD

#define PRESENT_SPEED_L         (38)    // RD, Current angular velocity
#define PRESENT_SPEED_H         (39)    // RD

#define PRESENT_LOAD_L          (40)    // RD, Magnitude of the load, see table page 18/38 of datasheet
#define PRESENT_LOAD_H          (41)    // RD

#define PRESENT_VOLTAGE         (42)    // RD, Current voltage applied, value is 10 times the actual voltage
#define PRESENT_TEMPERATURE     (43)    // RD, Current byteernal temperature in degree
#define REGISTERED_INSTRUCTION  (44)    // RD-WR, Set to 1 when an insctruction is assignedd by REG_WRITE instruction. Set to 0 after it completes the assigned insctruction by the ACTION instruction

#define MOVING                  (46)    // RD, Set to 1 when the actuator is movin by its own power
#define LOCK                    (47)    // RD-WR, Value 1, only Address 0x18 tp 0x23 can be written to. When locked, can only be unloakc by turning the device power off
#define PUNCH_L                 (48)    // RD-WR, Minimum current supplied to the motor during operation, initial value 0x20, maximum value 0x3ff
#define PUNCH_H                 (49)    // RD-WR


// TO GET INFORMATION FROM MOTORS

uint8 *dynamixel_getPingPacket(uint8 id);
uint8 *dynamixel_getReadPacket(uint8 id, uint8 address, uint8 nbOfByteToRead);


// RAM ALTERATION FUNCTION

uint8 *dynamixel_setTorqueEnablePacket(uint8 id, uint8 enabled);
uint8 *dynamixel_setLedPacket(uint8 id, uint8 value);
uint8 *dynamixel_setCWComplianceMarginPacket(uint8 id, uint8 value);
uint8 *dynamixel_setCCWComplianceMarginPacket(uint8 id, uint8 value);
uint8 *dynamixel_setCWComplianceSlopePacket(uint8 id, uint8 value);
uint8 *dynamixel_setCCWComplianceSlopePacket(uint8 id, uint8 value);
uint8 *dynamixel_setPositionRegPacket(uint8 id, uint16 position);
uint8 *dynamixel_setPositionPacket(uint8 id, uint16 position);
uint8 *dynamixel_setMovingSpeedPacket(uint8 id, uint16 speed);
uint8 *dynamixel_setTorquePacket(uint8 id, uint16 torque);


// EEPROM ALTERATION FUNCTION

uint8 *dynamixel_setIdPacket(uint8 id);
uint8 *dynamixel_setBaudratePacket(uint8 id, uint8 baudrate);
uint8 *dynamixel_setReturnTimeDelayPacket(uint8 id, uint8 delay);
uint8 *dynamixel_setCWLimitPacket(uint8 id, uint16 cw_limit);
uint8 *dynamixel_setCCWLimitPacket(uint8 id, uint16 ccw_limit);
uint8 *dynamixel_setTemperatureLimitPacket(uint8 id, uint8 temperature_limit);
uint8 *dynamixel_setLowestVoltageLimitPacket(uint8 id, uint8 voltage);
uint8 *dynamixel_setHighestVoltageLimitPacket(uint8 id, uint8 voltage);
uint8 *dynamixel_setMaxTorquePacket(uint8 id, uint16 torque);
uint8 *dynamixel_setReturnLevelPacket(uint8 id, uint8 level);
uint8 *dynamixel_setAlarmLedPacket(uint8 id, uint8 alarm);
uint8 *dynamixel_setAlarmShutdownPacket(uint8 id, uint8 alarm);
uint8 *dynamixel_setMultiturnOffsetPacket(uint8 id, uint16 offset);
uint8 *dynamixel_setResolutionDividerPacket(uint8 id, uint16 resolution);

// helper

uint8 *dynamixel_setByte(uint8 id, uint8 address, uint8 data);
uint8 *dynamixel_set2Bytes(uint8 id, uint8 address, uint16 value);
uint8 *dynamixel_set2BytesReg(uint8 id, uint8 address, uint16 value);

uint8 *dynamixel_getWritePacket(uint8 id, uint8 *param, uint8 nbOfParam);
uint8 *dynamixel_getWritePacketSimple(uint8 id, uint8 address, uint8 data);

uint8 *dynamixel_getActionPacket();
uint8 *dynamixel_getRegWritePacket(uint8 id, uint8 *param, uint8 nbOfParam);
uint8 *dynamixel_getRegWritePacketSimple(uint8 id, uint8 address, uint8 data);

uint8 *dynamixel_createSimpleInstructionPacket(uint8 instruction, uint8 id, uint8 param1, uint8 param2);
uint8 *dynamixel_createInstructionPacket(uint8 instruction, uint8 id, uint8 *param, uint8 nbOfParam);
uint8 dynamixel_calculateChecksum(uint8 *packet);

#endif

/* [] END OF FILE */
