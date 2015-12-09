/*******************************************************************************
* Project Name:      module-gripper-psoc
* Version:           1.0
*
* Device Used:       PSoC 5 CY8C5588AXI-LP035
* Software Used:     PSoC Creator v3.3
* Compiler Used:     ARM GCC 4.9-2015-q1-update
********************************************************************************
* Theory of Operation:
*
*
*******************************************************************************/
#include "main.h"


/* **************************************
   MACROS
 * *************************************/

#define SETCLOCK_4MHZ ControlReg_Write(ControlReg_Read() | 0x01)
#define SETCLOCK_8MHZ ControlReg_Write(ControlReg_Read() & 0xFE)

/* **************************************
   VARIABLES
 * *************************************/


// ------- VARIABLES CAN ---------
int messageToBeTreatedCount = 0;
int msgToBeTreatedIndex = 0;
int msgToBeStoredIndex = 0;
CAN_MSG receivedMsgs[MAX_MSG_BUFFER_SIZE];
// ----------------------------

volatile uint8 readCanMessage = 0;
uint8 treatingAddress = 0;



uint8 treatCanMessage(uint8* canPacket)
{   
    uint16 rightMotorPosition = 0;
    uint16 leftMotorPosition = 0;
    
    switch(canPacket[0])
    {
        case CAN_INSTRUCTION_SET_Z_AXIS_HOME:
            
            Z_Axis_Home();
            break;
        
        case CAN_INSTRUCTION_SET_Z_AXIS_POSITION:
            
            Z_Axis_GoTo((uint16)(canPacket[6]<<8) | canPacket[7]);
            break;
            
        case CAN_INSTRUCTION_OPEN_GRIPPER:
            
            // canPacket[1]:
            //      pourcentage of the openning
            
            rightMotorPosition = ((motorAngleLimits[MOTOR_RIGHT_ANGLE_CCW] - motorAngleLimits[MOTOR_RIGHT_ANGLE_CW]) * (canPacket[1]))/100 + motorAngleLimits[MOTOR_RIGHT_ANGLE_CW];
            leftMotorPosition  = ((motorAngleLimits[MOTOR_LEFT_ANGLE_CCW] - motorAngleLimits[MOTOR_LEFT_ANGLE_CW])* ((100-canPacket[1])))/100 + motorAngleLimits[MOTOR_LEFT_ANGLE_CW];
            
            sendPacketToDynamixel(dynamixel_setPositionRegPacket(motorType[MOTOR_TYPE_RIGHT], rightMotorPosition/*249*/));
            sendPacketToDynamixel(dynamixel_setPositionRegPacket(motorType[MOTOR_TYPE_LEFT], leftMotorPosition/*491*/));
            sendPacketToDynamixel(dynamixel_getActionPacket());
            break;
            
        case CAN_INSTRUCTION_MOVE:
            
            // canPacket[1]:
            //      ID of the motor
            // canPacket[2] & canPacket[3]:
            //      Position of the motor (between 0 and 0x3ff)
            
            sendPacketToDynamixel(dynamixel_setPositionPacket(canPacket[1], (uint16)((canPacket[3]<<8) + canPacket[2])));
            break;
        
        case CAN_INSTRUCTION_TILT:
            
            // canPacket[1] & canPacket[2]:
            //      position of the motor

            sendPacketToDynamixel(dynamixel_setPositionPacket(motorType[MOTOR_TYPE_TILT], (uint16)((canPacket[2]<<8) + canPacket[1])));
            break;
            
        case CAN_INSTRUCTION_ROTATE:
            
            // canPacket[1] & canPacket[2]:
            //      position of the motor
            
            sendPacketToDynamixel(dynamixel_setPositionPacket(motorType[MOTOR_TYPE_ROTATE], (uint16)((canPacket[2]<<8) + canPacket[1])));
            break;
        
        case CAN_INSTRUCTION_SET_MOVING_SPEED:
            
            // canPacket[1]:
            //      ID of the motor
            // canPacket[2] & canPacket[3]:
            //      Moving speed of the motor (between 0 and 0x3ff)
            
            sendPacketToDynamixel(dynamixel_setMovingSpeedPacket(canPacket[1], (uint16)((canPacket[3]<<8) + canPacket[2])));
            break;
            
        case CAN_INSTRUCTION_SET_TORQUE:
            
            // canPacket[1]:
            //      ID of the motor
            // canPacket[2] & canPacket[3]:
            //      Torque of the motor (between 0 and 0x3ff)
            
            sendPacketToDynamixel(dynamixel_setTorquePacket(canPacket[1], (uint16)((canPacket[3]<<8) + canPacket[2])));
            break;
            
        case CAN_INSTRUCTION_SET_TORQUE_ENABLE:
            
            // canPacket[1]: 
            //      ID of the motor
            //
            // canPacket[2]: 
            //      0 means no torque
            //      1 means apply torque
            
            sendPacketToDynamixel(dynamixel_setTorqueEnablePacket(canPacket[1], canPacket[2]));
            break;
            
        case CAN_INSTRUCTION_GET_DATA:
			
			// canPacket[1]:
			//		ID of the motor
		    // canPacket[2]: 
			//      address of the first data in the dynamixel table
			// canPacket[3]:
			//		number of byte to retreive (max of 4)
			
			treatingAddress = canPacket[2];
			sendPacketToDynamixel(dynamixel_getReadPacket(canPacket[1], canPacket[2], canPacket[3]));
			break;
        
        case CAN_INSTRUCTION_SET_DATA:
            
		    // canPacket[1]: 
			//      ID of the motor
			// canPacket[2]:
			//		address of the first data in the dynamixel table
			// canPacket[3]:
			//		number of byte to retreive (max of 2)
            // canPacket[4] & canPacket[5]:
            //      data to push to the motor
            
            switch(canPacket[3]) 
            {
                case 1:
                    sendPacketToDynamixel(dynamixel_setByte(canPacket[1], canPacket[2], canPacket[4]));
                    break;
                case 2:
                    updateAngleLimitData(canPacket);
                    sendPacketToDynamixel(dynamixel_set2Bytes(canPacket[1], canPacket[2], (canPacket[5]<<8) + canPacket[4]));
                    break;
            }
            
            break;
            
        case CAN_INSTRUCTION_CLOCK_4M:
            
            SETCLOCK_4MHZ;
            break;
            
        case CAN_INSTRUCTION_CLOCK_8M:
            
            SETCLOCK_8MHZ;
            break;
            
        case CAN_INSTRUCTION_GET_MOTOR_TYPE:
            
		    // canPacket[1]: 
			//      ID of the motor
			
            sendDataToCAN(0,CAN_HARDWARE_FILTER_ID, CAN_INSTRUCTION_GET_MOTOR_TYPE, canPacket[1], getMotorType(canPacket[1]), 0,0,0);
            break;
            
        case CAN_INSTRUCTION_SET_MOTOR_TYPE:
            
            // canPacket[1]: 
			//      ID of the motor
            // canPacket[2]: 
			//      Motor type (0 to 4)
            
            eraseMotorType(canPacket[1]);
            saveMotorType(canPacket[1], canPacket[2]);
            break;
            
    }
    return 0;
}

/*******************************************************************************
* COUNTER CAN READER INTERRUPT ROUTINE
********************************************************************************/
CY_ISR(CounterCanInterruptHandler)
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. 
     */
    Counter_CanReader_STATUS;
    readCanMessage = 1;
}


int main()
{
    init_eeprom();
    readEeprom();
    
    init_uart_dynamixel();
    init_can_module();
    Z_Axis_Init();
    
    SETCLOCK_4MHZ;
    CyGlobalIntEnable; // Enable Global Interrupts

	for(;;){
        
        
        //Verify if a message needs to be treated in the message received buffer.       
        if(readCanMessage == 1 && messageToBeTreatedCount > 0)
        {
            readCanMessage = 0;
            // Treat the last message received and echo it back on the CAN bus as an acknowledgement.
            CAN_MSG msgToTreat = can_getReceivedMessage(); 
            treatCanMessage(msgToTreat.msgBytes.byte);
        }//*/
    
    }
}


/******************************************************************************
* HELPER FUNCTIONS
*******************************************************************************/

void init_can_module()
{
    // Initializing required components for CAN communication
    CAN_1_Start();
    CAN_1_GlobalIntEnable();
    CAN_Standby_Write(0);
    
    // CAN message are read every time the counter turns to zero
    CanReaderISR_StartEx(CounterCanInterruptHandler);
    Counter_CanReader_Start();
}


/* [] END OF FILE */
