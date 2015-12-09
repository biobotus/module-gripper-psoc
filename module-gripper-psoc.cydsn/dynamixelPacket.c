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

#include "DynamixelPacket.h"


// RAM ALTERATION FUNCTION
uint8 *dynamixel_setTorqueEnablePacket(uint8 id, uint8 enabled)
{
    return dynamixel_getWritePacketSimple(id, TORQUE_ENABLE, enabled);
}

uint8 *dynamixel_setLedPacket(uint8 id, uint8 value)
{
    return dynamixel_getWritePacketSimple(id, LED, value);
}

uint8 *dynamixel_setCWComplianceMarginPacket(uint8 id, uint8 value)
{
    return dynamixel_getWritePacketSimple(id, CW_COMPLIANCE_MARGIN, value);
}

uint8 *dynamixel_setCCWComplianceMarginPacket(uint8 id, uint8 value)
{
    return dynamixel_getWritePacketSimple(id, CCW_COMPLIANCE_MARGIN, value);
}

uint8 *dynamixel_setCWComplianceSlopePacket(uint8 id, uint8 value)
{
    return dynamixel_getWritePacketSimple(id, CW_COMPLIANCE_SLOPE, value);
}

uint8 *dynamixel_setCCWComplianceSlopePacket(uint8 id, uint8 value)
{
    return dynamixel_getWritePacketSimple(id, CCW_COMPLIANCE_SLOPE, value);
}

uint8 *dynamixel_setPositionRegPacket(uint8 id, uint16 position)
{
    return dynamixel_set2BytesReg(id, GOAL_POSITION_L, position);
}

uint8 *dynamixel_setPositionPacket(uint8 id, uint16 position)
{
    return dynamixel_set2Bytes(id, GOAL_POSITION_L, position);
}

uint8 *dynamixel_setMovingSpeedPacket(uint8 id, uint16 speed)
{
    return dynamixel_set2Bytes(id, MOVING_SPEED_L, speed);
}

uint8 *dynamixel_setTorquePacket(uint8 id, uint16 torque)
{
    return dynamixel_set2Bytes(id, TORQUE_LIMIT_L, torque);
}




// EEPROM ALTERATION FUNCTION

uint8 *dynamixel_setIdPacket(uint8 id)
{
    return dynamixel_setByte(DYNAMIXEL_BROADCAST_ID, ID, id);   
}

uint8 *dynamixel_setBaudratePacket(uint8 id, uint8 baudrate)
{
    return dynamixel_setByte(id, BAUD_RATE, baudrate);   
}

uint8 *dynamixel_setReturnTimeDelayPacket(uint8 id, uint8 delay)
{
    return dynamixel_setByte(id, RETURN_DELAY_TIME, delay);   
}

uint8 *dynamixel_setCWLimitPacket(uint8 id, uint16 cw_limit)
{
    return dynamixel_set2Bytes(id, CW_ANGLE_LIMIT_L, cw_limit);
}

uint8 *dynamixel_setCCWLimitPacket(uint8 id, uint16 ccw_limit)
{
    return dynamixel_set2Bytes(id, CCW_ANGLE_LIMIT_L, ccw_limit);
}

uint8 *dynamixel_setTemperatureLimitPacket(uint8 id, uint8 temperature_limit)
{
    return dynamixel_setByte(id, TEMPERATURE_LIMIT, temperature_limit);   
}

uint8 *dynamixel_setLowestVoltageLimitPacket(uint8 id, uint8 voltage)
{
    return dynamixel_setByte(id, LOWEST_LIMIT_VOLTAGE, voltage);   
}

uint8 *dynamixel_setHighestVoltageLimitPacket(uint8 id, uint8 voltage)
{
    return dynamixel_setByte(id, HIGHEST_LIMIT_VOLTAGE, voltage);   
}

uint8 *dynamixel_setMaxTorquePacket(uint8 id, uint16 torque)
{
    return dynamixel_set2Bytes(id, MAX_TORQUE_L, torque); 
}

uint8 *dynamixel_setReturnLevelPacket(uint8 id, uint8 level)
{
    return dynamixel_setByte(id, RETURN_LEVEL, level);   
}

uint8 *dynamixel_setAlarmLedPacket(uint8 id, uint8 alarm)
{
    /*  
        Bit 7. 0
        Bit 6. If set to 1, the LED blinks when an Instruction Error occurs
        Bit 5. If set to 1, the LED blinks when an Overload Error occurs
        Bit 4. If set to 1, the LED blinks when a Checksum Error occurs
        Bit 3. If set to 1, the LED blinks when a Range Error occurs
        Bit 2. If set to 1, the LED blinks when an Overheating Error occurs
        Bit 1. If set to 1, the LED blinks when an Angle Limit Error occurs
        Bit 0. If set to 1, the LED blinks when an Input Voltage Error occurs
    */
    return dynamixel_setByte(id, ALARM_LED, alarm);   
}

uint8 *dynamixel_setAlarmShutdownPacket(uint8 id, uint8 alarm)
{
    /*
        Bit 7. 0
        Bit 6. If set to 1, torque off when an Instruction Error occurs
        Bit 5. If set to 1, torque off when an Overload Error occurs
        Bit 4. If set to 1, torque off when a Checksum Error occurs
        Bit 3. If set to 1, torque off when a Range Error occurs
        Bit 2. If set to 1, torque off when an Overheating Error occurs
        Bit 1. If set to 1, torque off when an Angle Limit Error occurs
        Bit 0. If set to 1, torque off when an Input Voltage Error occurs
    */
    return dynamixel_setByte(id, ALARM_SHUTDOWN, alarm);   
}


uint8 *dynamixel_setMultiturnOffsetPacket(uint8 id, uint16 offset)
{
    return dynamixel_set2Bytes(id, MULTI_TURN_OFFSET_L, offset); 
}

uint8 *dynamixel_setResolutionDividerPacket(uint8 id, uint16 resolution)
{
    return dynamixel_set2Bytes(id, RESOLUTION_DIVIDER, resolution); 
}


// --------------------------------------------------------------
//                      HELPER FUNCTIONS
// --------------------------------------------------------------


uint8 *dynamixel_set2Bytes(uint8 id, uint8 address, uint16 value)
{
    uint8 param[3];
    param[0] = address;
    param[1] = ((0xff) & value);
    param[2] = ((0xff) & (value >> 8));
    return dynamixel_getWritePacket(id, param, 3);
}


uint8 *dynamixel_set2BytesReg(uint8 id, uint8 address, uint16 value)
{
    uint8 param[3];
    param[0] = address;
    param[1] = ((0xff) & value);
    param[2] = ((0xff) & (value >> 8));
    return dynamixel_getRegWritePacket(id, param, 3);
}


uint8 *dynamixel_setByte(uint8 id, uint8 address, uint8 data)
{
    return dynamixel_getWritePacketSimple(id, address, data);
}










// --------------------------------------------------------------
//              DYNAMIXEL PACKET GENERATOR
// --------------------------------------------------------------


/*
    Used for requesting a status packet or to check the existence of a
    Dynamixel actuator with a specific ID.
*/
uint8 *dynamixel_getPingPacket(uint8 id)
{
    return dynamixel_createInstructionPacket(DYNAMIXEL_INST_PING, id, NULL, 0);
}


/*
    Read data from the control table of a Dynamixel actuator
*/
uint8 *dynamixel_getReadPacket(uint8 id, uint8 address, uint8 nbOfByteToRead)
{
    return dynamixel_createSimpleInstructionPacket(DYNAMIXEL_INST_READ, id, address, nbOfByteToRead);
}


/*
    To write data into the control table of the Dynamixel actuator
    The first parameter must be the starting addresse of the location where
    the data is to be written.
*/
uint8 *dynamixel_getWritePacket(uint8 id, uint8 *param, uint8 nbOfParam)
{
    return dynamixel_createInstructionPacket(DYNAMIXEL_INST_WRITE, id, param, nbOfParam);
}


uint8 *dynamixel_getWritePacketSimple(uint8 id, uint8 address, uint8 data)
{
    return dynamixel_createSimpleInstructionPacket(DYNAMIXEL_INST_WRITE, id, address, data);
}


/*
    The REG_WRITE instruction is similar to the WRITE_DATA instruction, but the
    execution timing is different. When the instruction packet is received, the
    values are stored in the buffer and the write instruction is under a stanby
    status. At this time, the registered instruction register (address 0x2C) is
    set to 1. After the action instruction packet is received, the registered
    write instruction is finally executed.
*/
uint8 *dynamixel_getRegWritePacket(uint8 id, uint8 *param, uint8 nbOfParam)
{
    return dynamixel_createInstructionPacket(DYNAMIXEL_INST_REG_WRITE, id, param, nbOfParam);
}

uint8 *dynamixel_getRegWritePacketSimple(uint8 id, uint8 address, uint8 data)
{
    return dynamixel_createSimpleInstructionPacket(DYNAMIXEL_INST_REG_WRITE, id, address, data);
}



/*
    Triggers the action registered by the REG_WRITE instruction
*/
uint8 *dynamixel_getActionPacket()
{
    return dynamixel_createInstructionPacket(DYNAMIXEL_INST_ACTION, DYNAMIXEL_BROADCAST_ID, NULL, 0);
}


/*
    Changes the control table values of the Dynamixel actuator to the Factory
    Default Value.
*/
uint8 *dynamixel_getResetPacket(uint8 id)
{
    return dynamixel_createInstructionPacket(DYNAMIXEL_INST_RESET, id, NULL, 0);
}


uint8 *dynamixel_createSimpleInstructionPacket(uint8 instruction, uint8 id, uint8 param1, uint8 param2)
{
    uint8 param[2];
    param[0] = param1;
    param[1] = param2;

    return dynamixel_createInstructionPacket(instruction, id, param, 2);
}


uint8 *dynamixel_createInstructionPacket(uint8 instruction, uint8 id, uint8 *param, uint8 nbOfParam)
{
    uint8 n;
    uint8 *packet = (uint8*)malloc(3 + nbOfParam + 3);
    uint8 i = 0;

    packet[i++] = 0xff;
    packet[i++] = 0xff;
    packet[i++] = id;				        // motor id
    packet[i++] = (uint8)(nbOfParam + 2);	// length
    packet[i++] = instruction;		        // instruction

    for (n = 0; n < nbOfParam; n++)
    {
        packet[i++] = param[n];
    }
    packet[i] = dynamixel_calculateChecksum(packet); // checksum

    return packet;
}


uint8 dynamixel_calculateChecksum(uint8 *packet)
{
    uint8 n;
    uint8 N = (uint8)(packet[3] + 1);
    uint8 checksum = 0;
    
    for (n = 0; n < N; n++)
    {
        checksum += packet[2 + n];
    }
    
    return (uint8)(~checksum);
}


/* [] END OF FILE */
