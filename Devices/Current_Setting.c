/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Current_Setting.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-28             
  |--Libsupports : 
  |--Description :                                                     
  |--FunctionList                                                     
  |-------1. ....                                                     
  |          <version>:                                                     
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#include "Current_Setting.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-28 21:39
  * @brief   底盘电流值发送
  * @param   int16_t I1,int16_t I2,int16_t I3,int16_t I4
  * @retval  void
  */
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4)
{
    uint8_t RM3508_Sending[8];

    RM3508_Sending[0] = I1 >> 8;
    RM3508_Sending[1] = I1;

    RM3508_Sending[2] = I2 >> 8;
    RM3508_Sending[3] = I2;

    RM3508_Sending[4] = I3 >> 8;
    RM3508_Sending[5] = I3;

    RM3508_Sending[6] = I4 >> 8;
    RM3508_Sending[7] = I4;

    CAN_sendData(CAN1,CAN_ID_STD,0x200,RM3508_Sending);
}

/**
  * @Data    2019-02-28 21:40
  * @brief   云台电流和拨弹电流值发送
  * @param   int16_t I_Yaw, int16_t I_Pitch, \
	int16_t I_Emitter, int16_t OVER
  * @retval  void
  */
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, \
int16_t I_Emitter, int16_t OVER)
{
  uint8_t Cloud_Sending[8];

    Cloud_Sending[0] = I_Yaw >> 8;
    Cloud_Sending[1] = I_Yaw;

    Cloud_Sending[2] = I_Pitch >> 8;
    Cloud_Sending[3] = I_Pitch;

    Cloud_Sending[4] = I_Emitter >> 8;
    Cloud_Sending[5] = I_Emitter;

    Cloud_Sending[6] = OVER >> 8;
    Cloud_Sending[7] = OVER;

    CAN_sendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}


/**
  * @Data    2019-03-06 19:42
  * @brief   云台电流值发送
  * @param   int16_t I_Yaw, int16_t I_Pitch,
  * @retval  void
  */
void Cloud_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch)
{
  uint8_t Cloud_Sending[8];

  Cloud_Sending[0] = I_Yaw >> 8;
  Cloud_Sending[1] = I_Yaw;

  Cloud_Sending[2] = I_Pitch >> 8;
  Cloud_Sending[3] = I_Pitch;

  Cloud_Sending[4] = NULL;
  Cloud_Sending[5] = NULL;

  Cloud_Sending[6] = NULL;
  Cloud_Sending[7] = NULL;

  CAN_sendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}

/**
  * @Data    2019-03-06 19:50
  * @brief   拨弹电机电流值发送
  * @param   int16_t I_Emitter
  * @retval  void
  */
void Cartridge_CurrentSetting(int16_t I_Emitter)
{
  uint8_t Cloud_Sending[8];

  Cloud_Sending[0] = NULL;
  Cloud_Sending[1] = NULL;

  Cloud_Sending[2] = NULL;
  Cloud_Sending[3] = NULL;

  Cloud_Sending[4] = I_Emitter >> 8;
  Cloud_Sending[5] = I_Emitter;

  Cloud_Sending[6] = NULL;
  Cloud_Sending[7] = NULL;

  CAN_sendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}