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
  |--FileName    : PID.h                                                
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
#ifndef __PID_H 
#define __PID_H 

#include "stm32f4xx.h"
#include "BSP_MATH.h"

/* =========================== INC_PID of begin =========================== */
typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}incrementalpid_t;
/* =========================== INC_PID of end =========================== */

/* =========================== POS_PID of begin =========================== */
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float Kp,Ki,Kd;
	float PWM;

	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}positionpid_t;
/* =========================== POS_PID of end =========================== */


/* =========================== POSFUZ_PID of begin =========================== */
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
    float Add_error;
	float ec_error; /*误差变化率*/ 
	float Kp,Ki,Kd;
	float PWM;

	/*模糊子集*/
	float KpRule[4];
	float KiRule[4];
	float KdRule[4];
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}POSfuzzationpid_t;
/* =========================== POSFUZ_PID of end =========================== */

/*增量式PID初始化*/
void IncrementalPID_Init(incrementalpid_t *pid, float kp, float ki, float kd, \
uint32_t MaxOutput, uint32_t IntegralLimit);

/*位置式PID初始化*/
void PositionPID_Init(positionpid_t *pid, float kp, float ki, float kd, \
uint32_t MaxOutput, uint32_t IntegralLimit);

/*模糊位置式PID初始化*/
void POSFuzzationPID_Init(POSfuzzationpid_t *pid,float InputKpRule[4],\
float InputKiRule[4],float InputKdRule[4],uint32_t MaxOutput, \
int32_t IntegralLimit);

/*增量式PID计算*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured);

/*位置式PID计算*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured);

/*模糊位置式PID计算*/
int FuzzationPID_POSCalculation(POSfuzzationpid_t * pid, float target, float measured);




/* =========================== FUZZYCAL of begin =========================== */
/*kp模糊值推导*/
float fuzzy_kp(float e, float ec,float InputKpRule[4]);

/*ki模糊值推导*/
float fuzzy_ki(float e, float ec, float InputKiRule[4]);

/*Kd模糊值推导*/
float fuzzy_kd(float e, float ec,float InputKdRule[4]);

/* =========================== FUZZYCAL of end =========================== */





#endif	// __PID_H
/*-----------------------------------file of end------------------------------*/


