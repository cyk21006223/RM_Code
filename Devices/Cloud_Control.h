/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Cloud_Control.h                                                
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

#ifndef __CLOUD_CONTROL_H 
#define __CLOUD_CONTROL_H 

#include "DR16.h"
#include "IMU.h"
#include "Current_Setting.h"
#include "Aiming_Control.h"
#include "Analysis.h"
#include "Filter.h"
#include "PID.h"



#define Cloud_LpfAttFactor 0.1f
#define Cloud_YawFilterAttFactor 0.4
#define Cloud_PitchFilterAttFactor 0.1

#define Cloud_Yaw_Min				1850.0f
#define Cloud_Yaw_Max				5950.0f
#define Cloud_Yaw_Center		3895.0f	
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min			3900.0f
#define Cloud_Pitch_Max			4650.0f
#define Cloud_Pitch_Center	4100.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

#define M6623_AngleToDEG(ang)	ang/22.75f

/*云台储存结构体*/
typedef struct 
{
  /*遥控器开关,用遥控右边的遥感*/
  uint8_t RCmodeswitch;

  /*PC控制模式*/
  uint8_t PCmodeswitch;

  /*云台基础储存数据*/
  float Filter_LPFfactor;
	float Yaw_Raw;
	float Yaw_LPF;
	float Pitch_Raw;
	float Pitch_LPF;
	
  /*IMU基础储存数据*/
	float IMUYaw_Raw;
	float IMUYaw_LPF;
	float IMUPitch_Raw;
	float IMUPitch_LPF;
	
  /*云台极值角度*/
	float IMUYawAngleMax;		//云台IMU最大角度(右)
	float IMUYawAngleMin;		//云台IMU最小角度(左)
	float IMUPitchAngleMax;		//云台IMU最大角度(下)
	float IMUPitchAngleMin;		//云台IMU最小角度(上)
	
  /*云台IMU对应PID*/
	positionpid_t YAW_Attitude_pid;
	positionpid_t YAW_Speed_pid;
	positionpid_t Roll_Attitude_pid;
	positionpid_t Roll_Speed_pid;

}Cloud_t;

extern Cloud_t Cloud;

/*云台初始化*/
void Cloud_Init(void);

/*云台数值赋值*/
void Cloud_Judgement(uint8_t switchmode);

/*云台处理*/
void Cloud_Process(float Delta_YAW, float Detla_Pitch,uint8_t switchmode);

/*获取云台的YAW轴和Pitch轴的旋转角度*/
/*YAW轴（以中间为零点）*/
float GetYAW_withCenter(void);
/*YAW轴（以左边为零点）*/
float GetYAW_withLeft(void);
/*Pitch轴（以中间为零点）*/
float GetPitch_withCenter(void);
/*Pitch轴（以下面为零点）*/
float GetPitch_withDown(void);

/*Pitch轴机械角度设定目标轴*/
void M6623_setTargetAngle(int Moto_Id,int32_t Target_Angle);

#endif	// __CLOUD_CONTROL_H
/*-----------------------------------file of end------------------------------*/


