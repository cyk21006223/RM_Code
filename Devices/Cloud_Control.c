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
  |--FileName    : Cloud_Control.c                                              
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
#include "Cloud_Control.h" 

/*云台数据结构体*/
Cloud_t Cloud;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-03-01 19:55
  * @brief   云台初始化
  * @param   void
  * @retval  void
  */
void Cloud_Init(void)
{
  /*滤波函数初始化*/
  Cloud.Filter_LPFfactor = Cloud_LpfAttFactor;

  /*机械角度读取初始化*/
  Cloud.Yaw_Raw = Cloud.Yaw_LPF = RM6623s[0].totalAngle;
  Cloud.Pitch_Raw = Cloud.Pitch_LPF = RM6623s[1].totalAngle;

  /*PITCH轴模糊PID规则（暂定）*/
  float PITCH_KpRule[4] = {0.486,0.648,0.729,0.7873};
  float PITCH_KiRule[4] = {0.0,0.0,0.0,0.0};
  float PITCH_KdRule[4] = {1.1289,1.101,1.4862,1.6035};
  float PITCH_KpRuleS[4] = {-17.8,-23.06,-28.11,-30.35};
  float PITCH_KiRuleS[4] = {0.0,0.0,0.0,0.0};
  float PITCH_KdRuleS[4] = {-9.26,-9.50,-12.82,-13.83};

  /*机械角度PID*/
  /*YAW轴*/
  PositionPID_Init(&RM6623s[0].pid_speed,-10.0f, 0.0f, 0.0f, 4000, 0);
  PositionPID_Init(&RM6623s[0].pid_angle,2.0f, 0.0f, 1.0f, 500, 0);

  /*PITCH轴*/
  PositionPID_Init(&RM6623s[1].pid_speed,-20.0f, 0.0f, -10.5f, 4000, 0);
  PositionPID_Init(&RM6623s[1].pid_angle, 0.23f, 0.0f, 0.5f, 500, 0);

  /*云台IMU对应PID*/
  /*模糊PID*/
  /*双环模糊PID YAW*/
  // POSFuzzationPID_Init(&Cloud.YAW_PID_ATT,YAW_KpRule,YAW_KiRule,YAW_KdRule,4000,0);
  // POSFuzzationPID_Init(&Cloud.YAW_PID_SPEE,YAW_KpRule,YAW_KiRule,YAW_KdRule,4000,0);
  
  /*双环模糊PID PITCH*/
  POSFuzzationPID_Init(&Cloud.Roll_PID_ATT,PITCH_KpRule,PITCH_KiRule,\
  PITCH_KdRule,4000,0);
  POSFuzzationPID_Init(&Cloud.Roll_PID_SPEE,PITCH_KpRuleS,PITCH_KiRuleS,\
  PITCH_KdRuleS,4000,0);


  /*双环Yaw普通位置PID*/
  PositionPID_Init(&Cloud.YAW_Attitude_pid,  -1.3f, -2.5f, -0.5f, 500, 0);
  PositionPID_Init(&Cloud.YAW_Speed_pid, -60.0f, 0.0f, -48.0, 4000, 0);

  /*双环Pitch普通位置PID*/
  PositionPID_Init(&Cloud.Roll_Attitude_pid,-2.0f, 0.0f, 0.0f, 500, 0);
  PositionPID_Init(&Cloud.Roll_Speed_pid, -60.0f, 0.0f, -40.0f, 4000, 0);
}


/**
  * @Data    2019-03-03 10:39
  * @brief   云台处理赋值
  * @param   uint8_t switchmode
  * @retval  void
  */
void Cloud_Judgement(uint8_t switchmode)
{
  /*云台储存数据变量*/
  float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;

  switch(switchmode)
  {
    case PC_Controling:
    break;

    case RC_Controling:
    /*普通遥控器控制方式*/
    Cloud_delta_Yaw = RCRocket.Right_x / 8;
    Cloud_delta_Pitch = RCRocket.Right_y / 7;
    break;

    case None_Controling:
    break;

    default:
    break;
  }

  /*云台处理*/
  Cloud_Process(Cloud_delta_Yaw,Cloud_delta_Pitch,switchmode);
}

/**
  * @Data    2019-03-03 10:48
  * @brief   云台处理
  * @param   float Delta_YAW, float Detla_Pitch,uint8_t switchmode
  * @retval  void
  */
void Cloud_Process(float Delta_YAW, float Detla_Pitch,uint8_t switchmode)
{
  /*YAW轴机械角度跟随，无论是否处于掉线状态*/
  Cloud.Yaw_LPF = Cloud.Yaw_Raw = RM6623s[0].totalAngle;

  if(switchmode == None_Controling || Cloud_IMU.OFFLINE_SET == 1 || \
  DR16.OFFLINE_SET == 1)
  {
    /*IMU数据同步*/
    IMU_Synchronization(Cloud_IMU.totalYaw,Cloud_IMU.eular.pitch);

    /*机械角度数据同步*/
    Cloud.Pitch_LPF = Cloud.Pitch_Raw = Cloud_Pitch_Center;

    /*电流归零防炸*/
    Cloud_And_Emitter_CurrentSetting(0,0,0,0);

    /*数据清零防炸*/
    Delta_YAW =0;
    Detla_Pitch =0;
    
    return;
  }

  /*遥控器赋值转换*/
  Cloud.IMUYaw_Raw = Delta_YAW / 30.0f;
  Cloud.Pitch_Raw = Detla_Pitch;

  /*动态IMU极值点赋值 */ 
  Cloud.IMUYawAngleMax = Cloud_IMU.totalYaw + GetYAW_withLeft();
  Cloud.IMUYawAngleMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta)\
  - GetYAW_withLeft());
  Cloud.IMUPitchAngleMax = Cloud_IMU.eular.roll + GetPitch_withDown();
  Cloud.IMUPitchAngleMin = Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) \
  - GetPitch_withDown());

  /*云台限幅*/
  /*注意这里以后可以增加判断，在不同的模式下可以决定是否判断这个限幅*/
  if(Cloud_IMU.totalYaw > Cloud.IMUYawAngleMax)
  {
    if(Delta_YAW < 0.0f)
    { 
        Cloud.IMUYaw_Raw += (Delta_YAW/8)/30.0f;
    }
    else
    {
        Cloud.IMUYaw_Raw = Cloud.IMUYawAngleMax;
    }
  }

  if(Cloud_IMU.totalYaw < Cloud.IMUYawAngleMin)
  {
    if(Delta_YAW > 0.0f)
    {
        Cloud.IMUYaw_Raw -= (Delta_YAW/8)/30.0f;
    }
    else
    {
        Cloud.IMUYaw_Raw = Cloud.IMUYawAngleMin;
    }
  }

  Filter_IIRLPF(&Cloud.IMUYaw_Raw,&Cloud.IMUPitch_Raw,Cloud_YawFilterAttFactor);
  Filter_IIRLPF(&Cloud.Pitch_Raw,&Cloud.Pitch_LPF,Cloud_LpfAttFactor);

  if(!RM6623s[0].OFFLINE_SET)
  {
    /*双环PID计算辅助*/
    float M6623s_YawOPIDOut;

    /*PID外环计算*/
    M6623s_YawOPIDOut = PositionPID_Calculation(&Cloud.YAW_Attitude_pid, \
    Cloud.IMUYaw_LPF, Cloud_IMU.totalYaw);

    /*PID内环计算*/
    RM6623s[0].outCurrent = PositionPID_Calculation(&Cloud.YAW_Speed_pid, \
    M6623s_YawOPIDOut, Cloud_IMU.gyro.z);

    /*清除标志位*/
    RM6623s[0].UpdateFlag = 0;
  }

  if(!RM6623s[1].OFFLINE_SET)
  {
    /*双环PID计算辅助*/
    int M6623s_PIDOut;

    /*PID外环计算*/
//		M6623s_PIDOut = PositionPID_Calculation(&RM6623s[1].pid_angle, \
//		RM6623s[1].targetAngle, RM6623s[1].totalAngle);

//    /*PID内环计算*/
//    RM6623s[1].outCurrent = PositionPID_Calculation(&RM6623s[1].pid_speed, \
//    M6623s_PIDOut, Cloud_IMU.gyro.y);

    /*清除标志位*/
    RM6623s[1].UpdateFlag = 0;
  }

  /*电流值发送*/
  Cloud_CurrentSetting(RM6623s[0].outCurrent,RM6623s[1].outCurrent);


}

/**
  * @Data    2019-03-03 15:01
  * @brief   获取云台YAW轴和PITCH轴的旋转角度
  * @param   void
  * @retval  float
  */
float GetYAW_withCenter(void)
{
  return(RM6623s[0].totalAngle - Cloud_Yaw_Center) / 22.75f;
}

float GetYAW_withLeft(void)
{
  return(RM6623s[0].totalAngle - Cloud_Yaw_Min) / 22.75f;
}

float GetPitch_withCenter(void)
{
   return(RM6623s[1].totalAngle - Cloud_Pitch_Center);
}

float GetPitch_withDown(void)
{
  return(RM6623s[1].totalAngle - Cloud_Pitch_Min);
}

/**
  * @Data    2019-03-06 18:45
  * @brief   Pitch轴机械角度设定目标轴
  * @param   int Moto_Id,int32_t Target_Angle
  * @retval  void
  */
void M6623_setTargetAngle(int Moto_Id,int32_t Target_Angle)
{
  RM6623s[Moto_Id].targetAngle = Target_Angle;
}
