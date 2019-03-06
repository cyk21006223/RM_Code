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
  |--FileName    : Analysis.h                                                
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
#ifndef __ANALYSIS_H 
#define __ANALYSIS_H 

#include "stm32f4xx.h"
#include "PID.h"

#define PLATFORM_A_TURN 8192
#define UNDULATION_A_TURN 8192

/* =========================== RM3508 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*赋值（输出）部分*/
	incrementalpid_t pid_wheel;
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_t;
/* =========================== RM3508 of end =========================== */

/* =========================== RM6623 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*赋值（输出）部分*/
	positionpid_t pid_speed;		
  	positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM6623_t;
/* =========================== RM6623 of end =========================== */

/* =========================== RM2006 of begin =========================== */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*赋值（输出）部分*/
	positionpid_t pid_speed;		
  	positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*帧率控制（判断是否离线）*/
		uint8_t UpdateFlag;
		uint16_t UpdateFrame;
		uint8_t OFFLINE_SET;
}RM2006_t;    
/* =========================== RM2006 of end =========================== */

/*对应的四个轮子*/
extern RM3508_t RM3508s[4];
/*对应的两个云台*/
extern RM6623_t RM6623s[2];
/*对应的拨弹电机*/
extern RM2006_t RM2006s[1];

/*CAN1报文解码*/
void Analysis_getinfo(CanRxMsg RxMessage);

/*RM6623云台过零处理*/
void M6623_ZeroDealing_platform(int8_t id);

/*RM2006拨弹电机过零处理*/
void M2006_ZeroDealing_platform(int8_t id);



#endif	// __ANALYSIS_H
/*-----------------------------------file of end------------------------------*/


