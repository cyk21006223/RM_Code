/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���ޣ�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Cloud_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
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

/*��̨����ṹ��*/
typedef struct 
{
  /*ң��������,��ң���ұߵ�ң��*/
  uint8_t RCmodeswitch;

  /*PC����ģʽ*/
  uint8_t PCmodeswitch;

  /*��̨������������*/
  float Filter_LPFfactor;
	float Yaw_Raw;
	float Yaw_LPF;
	float Pitch_Raw;
	float Pitch_LPF;
	
  /*IMU������������*/
	float IMUYaw_Raw;
	float IMUYaw_LPF;
	float IMUPitch_Raw;
	float IMUPitch_LPF;
	
  /*��̨��ֵ�Ƕ�*/
	float IMUYawAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUYawAngleMin;		//��̨IMU��С�Ƕ�(��)
	float IMUPitchAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUPitchAngleMin;		//��̨IMU��С�Ƕ�(��)
	
  /*��̨IMU��ӦPID*/
	positionpid_t YAW_Attitude_pid;
	positionpid_t YAW_Speed_pid;
	positionpid_t Roll_Attitude_pid;
	positionpid_t Roll_Speed_pid;

}Cloud_t;

extern Cloud_t Cloud;

/*��̨��ʼ��*/
void Cloud_Init(void);

/*��̨��ֵ��ֵ*/
void Cloud_Judgement(uint8_t switchmode);

/*��̨����*/
void Cloud_Process(float Delta_YAW, float Detla_Pitch,uint8_t switchmode);

/*��ȡ��̨��YAW���Pitch�����ת�Ƕ�*/
/*YAW�ᣨ���м�Ϊ��㣩*/
float GetYAW_withCenter(void);
/*YAW�ᣨ�����Ϊ��㣩*/
float GetYAW_withLeft(void);
/*Pitch�ᣨ���м�Ϊ��㣩*/
float GetPitch_withCenter(void);
/*Pitch�ᣨ������Ϊ��㣩*/
float GetPitch_withDown(void);

/*Pitch���е�Ƕ��趨Ŀ����*/
void M6623_setTargetAngle(int Moto_Id,int32_t Target_Angle);

#endif	// __CLOUD_CONTROL_H
/*-----------------------------------file of end------------------------------*/


