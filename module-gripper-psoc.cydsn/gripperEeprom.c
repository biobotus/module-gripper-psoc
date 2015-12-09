
#include "gripperEeprom.h"

uint8 motorType[] = {0, 0, 0, 0, 0};
uint16 motorAngleLimits[] = {0, 0, 0, 0};

void init_eeprom()
{
    EEPROM_Start();
    CyDelayUs(5); // the EEPROM needs 5 μS to start
    
    /*
    It is necessary to acquire the die temperature by calling the EEPROM_UpdateTemperature() 
    function before a series of EEPROM write operations. The EEPROM_UpdateTemperature() 
    function queries SPC for the die temperature and stores it in a global variable, 
    which is used while performing EEPROM write operations. If the application is used 
    in an environment where the die temperature changes 10° C or more, the temperature 
    should be refreshed to adjust the write times for the optimal performance.
    */
    EEPROM_UpdateTemperature();
    
    /*
    // EEPROM default values
    
    EEPROM_WriteByte(1,EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID);
    EEPROM_WriteByte(2,EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID);
    EEPROM_WriteByte(3,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID);
    EEPROM_WriteByte(4,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID);
   
    EEPROM_WriteByte(17,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_L);
    EEPROM_WriteByte(0,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_H);
    EEPROM_WriteByte(235,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_L);
    EEPROM_WriteByte(0,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_H);
    
    EEPROM_WriteByte((uint8)500,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_L);
    EEPROM_WriteByte((uint8)(500>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_H);
    EEPROM_WriteByte((uint8)721,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_L);
    EEPROM_WriteByte((uint8)(721>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_H);
    //*/
}


void readEeprom() 
{
    uint8 L, H;
    motorType[MOTOR_TYPE_ROTATE] = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID);
    motorType[MOTOR_TYPE_TILT]   = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID);
    motorType[MOTOR_TYPE_RIGHT]  = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID);
    motorType[MOTOR_TYPE_LEFT]   = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_H);
    motorAngleLimits[MOTOR_RIGHT_ANGLE_CW] = (int16)(((int16)H<<8) | L);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_H);
    motorAngleLimits[MOTOR_RIGHT_ANGLE_CCW] = (int16)(((int16)H<<8) | L);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_H);
    motorAngleLimits[MOTOR_LEFT_ANGLE_CW] = (int16)(((int16)H<<8) | L);

    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_H);
    motorAngleLimits[MOTOR_LEFT_ANGLE_CCW] = (int16)(((int16)H<<8) | L);
}


void eraseMotorType(uint8 motorID)
{
    uint8 type = getMotorType(motorID);
    if(type != MOTOR_TYPE_NONE) {
        EEPROM_WriteByte(0,type);
        motorType[type] = 0;
    }
}

void saveMotorType(uint8 motorID, uint8 type)
{
    if(type != MOTOR_TYPE_NONE)
    {
        switch(type) 
        {
            case MOTOR_TYPE_ROTATE:
                EEPROM_WriteByte(motorID, EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID);
                break;
            case MOTOR_TYPE_TILT:
                EEPROM_WriteByte(motorID, EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID);
                break;
            case MOTOR_TYPE_RIGHT:
                EEPROM_WriteByte(motorID, EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID);
                break;
            case MOTOR_TYPE_LEFT:
                EEPROM_WriteByte(motorID, EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID);
                break;
        }
        motorType[type] = motorID;
    }
}

uint8 getMotorType(uint8 motorID)
{
    int type = 0;
    for(; type < NB_OF_MOTOR_TYPE; type++)
    {
        if(motorID == motorType[type])
        {
            return type;
        }
    }
    return 0;
}


void updateAngleLimitData(uint8 *packet)
{

    if(packet[1] == motorType[MOTOR_TYPE_LEFT])
    {
        if(packet[2] == CW_ANGLE_LIMIT_L)
        {
            motorAngleLimits[MOTOR_LEFT_ANGLE_CW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorAngleLimits[MOTOR_LEFT_ANGLE_CW],EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_L);
            EEPROM_WriteByte((uint8)(motorAngleLimits[MOTOR_LEFT_ANGLE_CW]>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_ANGLE_H);
        }
        else if(packet[2] == CCW_ANGLE_LIMIT_L)
        {
            motorAngleLimits[MOTOR_LEFT_ANGLE_CCW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorAngleLimits[MOTOR_LEFT_ANGLE_CCW],EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_L);
            EEPROM_WriteByte((uint8)(motorAngleLimits[MOTOR_LEFT_ANGLE_CCW]>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_ANGLE_H);
        }
    }
    else if(packet[1] == motorType[MOTOR_TYPE_RIGHT])
    {
        if(packet[2] == CW_ANGLE_LIMIT_L)
        {
            motorAngleLimits[MOTOR_RIGHT_ANGLE_CW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorAngleLimits[MOTOR_RIGHT_ANGLE_CW],EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_L);
            EEPROM_WriteByte((uint8)(motorAngleLimits[MOTOR_RIGHT_ANGLE_CW]>>8),EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_ANGLE_H);
        }
        if(packet[2] == CCW_ANGLE_LIMIT_L)
        {
            motorAngleLimits[MOTOR_RIGHT_ANGLE_CCW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorAngleLimits[MOTOR_RIGHT_ANGLE_CCW],EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_L);
            EEPROM_WriteByte((uint8)(motorAngleLimits[MOTOR_RIGHT_ANGLE_CCW]>>8),EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_ANGLE_H);
        }
    }
}


/* [] END OF FILE */
