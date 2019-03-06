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
  |--FileName    : Analysis.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-19             
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
#include "Analysis.h" 
    
/*-----------------------------------file of end------------------------------*/

/* =========================== WHELLSTRUCT of begin =========================== */
/*对应的四个轮子*/
RM3508_t RM3508s[4];
/*对应的两个云台*/
RM6623_t RM6623s[2];
/*对应的拨弹电机*/
RM2006_t RM2006s[1];
/* =========================== WHELLSTRUCT of end =========================== */

/**
  * @Data    2019-02-19 18:34
  * @brief   CAN1报文解码
  * @param   CanRxMsg RxMessage
  * @retval  void
  */
void Analysis_getinfo(CanRxMsg RxMessage)
{
    switch(RxMessage.StdId)
    {
    //wheel
    case 0x201://对应的为0号轮子
        RM3508s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[0].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[0].realTempeture = (RxMessage.Data[6]);
        RM3508s[0].UpdateFlag = 1;
        RM3508s[0].UpdateFrame++;
        break;

    case 0x202://对应的为1号轮子
        RM3508s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[1].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[1].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[1].realTempeture = (RxMessage.Data[6]);
        RM3508s[1].UpdateFlag = 1;
        RM3508s[1].UpdateFrame++;
        break;

    case 0x203://对应为2号轮子
        RM3508s[2].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[2].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[2].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[2].realTempeture = (RxMessage.Data[6]);
        RM3508s[2].UpdateFlag = 1;
        RM3508s[2].UpdateFrame++;
        break;

    case 0x204://对应为3号轮子
        RM3508s[3].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[3].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[3].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[3].realTempeture = (RxMessage.Data[6]);
        RM3508s[3].UpdateFlag = 1;
        RM3508s[3].UpdateFrame++;
        break;

    //platform
    case 0x205://对应的Yaw轴云台
        RM6623s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM6623s[0].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
//			RM6623s[0].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        M6623_ZeroDealing_platform(0);
        RM6623s[0].totalAngle = RM6623s[0].realAngle +(PLATFORM_A_TURN*\
				RM6623s[0].turnCount);
        RM6623s[0].UpdateFlag = 1;
        RM6623s[0].UpdateFrame++;
        break;

    case 0x206://对应的Pitch轴云台
        RM6623s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM6623s[1].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
//			RM6623s[1].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        M6623_ZeroDealing_platform(1);
        RM6623s[1].totalAngle = RM6623s[1].realAngle +(PLATFORM_A_TURN*\
				RM6623s[1].turnCount);
        RM6623s[1].UpdateFlag = 1;
        RM6623s[1].UpdateFrame++;
        break;

    case 0x207://对应拨弹电机
        RM2006s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM2006s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM2006s[0].realTorque = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        M2006_ZeroDealing_platform(0);
        RM2006s[0].totalAngle = RM2006s[0].realAngle +(UNDULATION_A_TURN*RM2006s[0].turnCount);
        RM2006s[0].UpdateFlag = 1;
        RM2006s[0].UpdateFrame++;

    // case 0x208://GM2060测试
    //     RGM6020[0].realAngle = (RxMessage.Data[0]<<8 | RxMessage.Data[1]);
    //     RGM6020[0].realSpeed = (RxMessage.Data[2]<<8 | RxMessage.Data[3]);
    //     RGM6020[0].realTorque = (RxMessage.Data[4]<<8 | RxMessage.Data[5]);
    //     RGM6020[0].realTempeture = RxMessage.Data[6];
    }
}

/**
  * @Data    2019-02-19 18:39
  * @brief   RM6623云台电机过零处理
  * @param   int8_t id 需要过零处理的电机对应的ID
  * @retval  void
  */
void M6623_ZeroDealing_platform(int8_t id)
{
    if(RM6623s[id].realAngle - RM6623s[id].lastAngle < -6000)
    {
        RM6623s[id].turnCount++;
    }

    if(RM6623s[id].lastAngle - RM6623s[id].realAngle < -6000)
    {
        RM6623s[id].turnCount--;
    }
    RM6623s[id].lastAngle =  RM6623s[id].realAngle;

}

/**
  * @Data    2019-02-19 18:41
  * @brief   RM2006过零处理
  * @param   int8_t id  需要过零处理的电机对应的ID
  * @retval  void
  */
void M2006_ZeroDealing_platform(int8_t id)
{
    if(RM2006s[id].realAngle - RM2006s[id].lastAngle < -6000)
    {
        RM2006s[id].turnCount++;
    }
    if(RM2006s[id].lastAngle - RM2006s[id].realAngle < -6000)
    {
        RM2006s[id].turnCount--;
    }
    RM2006s[id].lastAngle =  RM2006s[id].realAngle;
}




