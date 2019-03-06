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
  |--FileName    : Chassis_Control.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
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
/*滤波系数*/
#define Fif_Factor 0.04f  

#define Chassis_MaxSpeed_Y	6600.0f		
#define Chassis_MaxSpeed_X	6600.0f		
#define Chassis_MaxSpeed_W	6600.0f		
/* =========================== FilterSetting of end =========================== */

/* =========================== Chassis Conment of begin =========================== */
/*底盘储存结构体*/
typedef struct
{
	/*遥控模式，用遥控右遥杆*/
	uint8_t RCmodeswitch;
	
	/*PC的控制模式*/
	uint8_t PCmodeswitch;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
  /*跟随相关数据*/
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*超功率标志位*/
	uint8_t Power_OverflowFlag;
	
}Chassis_t;
/* =========================== Chassis Conment of end =========================== */

/*底盘数据储存结构体*/
extern Chassis_t Chassis;

/*底盘初始化*/
void Chassis_Init(void);

/*底盘数据赋值处理*/
void Chassis_Judgement(uint8_t switchmode);

/*底盘处理函数*/
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode);

/*麦轮解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*功率限制*/
void Chassis_powerLimit(RM3508_t *p_M3508s, float CurrentLimit);

#endif	// __CHASSIS_CONTROL_H
/*-----------------------------------file of end------------------------------*/


