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
  |--FileName    : Analysis.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
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
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*��ֵ�����������*/
	incrementalpid_t pid_wheel;
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_t;
/* =========================== RM3508 of end =========================== */

/* =========================== RM6623 of begin =========================== */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*��ֵ�����������*/
	positionpid_t pid_speed;		
  	positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM6623_t;
/* =========================== RM6623 of end =========================== */

/* =========================== RM2006 of begin =========================== */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*��ֵ�����������*/
	positionpid_t pid_speed;		
  	positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
		uint8_t UpdateFlag;
		uint16_t UpdateFrame;
		uint8_t OFFLINE_SET;
}RM2006_t;    
/* =========================== RM2006 of end =========================== */

/*��Ӧ���ĸ�����*/
extern RM3508_t RM3508s[4];
/*��Ӧ��������̨*/
extern RM6623_t RM6623s[2];
/*��Ӧ�Ĳ������*/
extern RM2006_t RM2006s[1];

/*CAN1���Ľ���*/
void Analysis_getinfo(CanRxMsg RxMessage);

/*RM6623��̨���㴦��*/
void M6623_ZeroDealing_platform(int8_t id);

/*RM2006����������㴦��*/
void M2006_ZeroDealing_platform(int8_t id);



#endif	// __ANALYSIS_H
/*-----------------------------------file of end------------------------------*/


