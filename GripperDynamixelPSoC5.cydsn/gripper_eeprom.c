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

#include "gripper_eeprom.h"

uint8 motorType[] = {0, 0, 0, 0, 0};
uint16 motorMargin[] = {0, 0, 0, 0};

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
    EEPROM_WriteByte(1,EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID);
    EEPROM_WriteByte(2,EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID);
    EEPROM_WriteByte(3,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID);
    EEPROM_WriteByte(4,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID);
   
    EEPROM_WriteByte(17,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_L);
    EEPROM_WriteByte(0,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_H);
    EEPROM_WriteByte(235,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_L);
    EEPROM_WriteByte(0,EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_H);
    
    EEPROM_WriteByte((uint8)500,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_L);
    EEPROM_WriteByte((uint8)(500>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_H);
    EEPROM_WriteByte((uint8)721,EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_L);
    EEPROM_WriteByte((uint8)(721>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_H);
    //*/
}


void readEeprom() 
{
    uint8 L, H;
    motorType[MOTOR_TYPE_ROTATE] = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_ROTATE_MOTOR_ID);
    motorType[MOTOR_TYPE_TILT]   = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_TILT_MOTOR_ID);
    motorType[MOTOR_TYPE_RIGHT]  = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_ID);
    motorType[MOTOR_TYPE_LEFT]   = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_ID);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_H);
    //motorRightMargin.CW = (int16)(((int16)H<<8) | L);
    motorMargin[MOTOR_RIGHT_MARGIN_CW] = (int16)(((int16)H<<8) | L);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_H);
    //motorRightMargin.CCW = (int16)(((int16)H<<8) | L);
    motorMargin[MOTOR_RIGHT_MARGIN_CCW] = (int16)(((int16)H<<8) | L);
    
    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_H);
    //motorLeftMargin.CW = (int16)(((int16)H<<8) | L);
    motorMargin[MOTOR_LEFT_MARGIN_CW] = (int16)(((int16)H<<8) | L);

    L = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_L);
    H = EEPROM_ReadByte(EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_H);
    //motorLeftMargin.CCW = (int16)(((int16)H<<8) | L);
    motorMargin[MOTOR_LEFT_MARGIN_CCW] = (int16)(((int16)H<<8) | L);
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
            motorMargin[MOTOR_LEFT_MARGIN_CW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorMargin[MOTOR_LEFT_MARGIN_CW],EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_L);
            EEPROM_WriteByte((uint8)(motorMargin[MOTOR_LEFT_MARGIN_CW]>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CW_MARGIN_H);
        }
        else if(packet[2] == CCW_ANGLE_LIMIT_L)
        {
            motorMargin[MOTOR_LEFT_MARGIN_CCW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorMargin[MOTOR_LEFT_MARGIN_CCW],EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_L);
            EEPROM_WriteByte((uint8)(motorMargin[MOTOR_LEFT_MARGIN_CCW]>>8),EEPROM_ADDR_GRIPPER_LEFT_MOTOR_CCW_MARGIN_H);
        }
    }
    else if(packet[1] == motorType[MOTOR_TYPE_RIGHT])
    {
        if(packet[2] == CW_ANGLE_LIMIT_L)
        {
            motorMargin[MOTOR_RIGHT_MARGIN_CW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorMargin[MOTOR_RIGHT_MARGIN_CW],EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_L);
            EEPROM_WriteByte((uint8)(motorMargin[MOTOR_RIGHT_MARGIN_CW]>>8),EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CW_MARGIN_H);
        }
        if(packet[2] == CCW_ANGLE_LIMIT_L)
        {
            motorMargin[MOTOR_RIGHT_MARGIN_CCW] = (packet[5]<<8) + packet[4];
            EEPROM_WriteByte((uint8)motorMargin[MOTOR_RIGHT_MARGIN_CCW],EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_L);
            EEPROM_WriteByte((uint8)(motorMargin[MOTOR_RIGHT_MARGIN_CCW]>>8),EEPROM_ADDR_GRIPPER_RIGHT_MOTOR_CCW_MARGIN_H);
        }
    }
}


/* [] END OF FILE */
