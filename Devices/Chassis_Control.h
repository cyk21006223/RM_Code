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
  |--FileName    : Chassis_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
  |--Date        : 2019-02-25               
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
#ifndef __CHASSIS_CONTROL_H 
#define __CHASSIS_CONTROL_H 

#include "Cloud_Control.h"
#include "Current_Setting.h"
#include "Analysis.h"
#include "PID.h"
#include "DR16.h"
#include "Filter.h"
#include "BSP_MATH.h"

/* =========================== FilterSetting of begin =========================== */
/*�˲�ϵ��*/
#define Fif_Factor 0.04f  

#define Chassis_MaxSpeed_Y	6600.0f		
#define Chassis_MaxSpeed_X	6600.0f		
#define Chassis_MaxSpeed_W	6600.0f		
/* =========================== FilterSetting of end =========================== */

/* =========================== Chassis Conment of begin =========================== */
/*���̴���ṹ��*/
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t RCmodeswitch;
	
	/*PC�Ŀ���ģʽ*/
	uint8_t PCmodeswitch;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
  /*�����������*/
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*�����ʱ�־λ*/
	uint8_t Power_OverflowFlag;
	
}Chassis_t;
/* =========================== Chassis Conment of end =========================== */

/*�������ݴ���ṹ��*/
extern Chassis_t Chassis;

/*���̳�ʼ��*/
void Chassis_Init(void);

/*�������ݸ�ֵ����*/
void Chassis_Judgement(uint8_t switchmode);

/*���̴�����*/
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode);

/*���ֽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*��������*/
void Chassis_powerLimit(RM3508_t *p_M3508s, float CurrentLimit);

#endif	// __CHASSIS_CONTROL_H
/*-----------------------------------file of end------------------------------*/


