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
  |--FileName    : IMU.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
  |--Date        : 2019-02-22               
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
#ifndef __IMU_H 
#define __IMU_H 

#include "Cloud_Control.h"
#include "stm32f4xx.h"
#include "BSP_USART.h"

/*有效数据长度*/
#define GY_IMU_BUFFSIZE 30

/*数据包长度*/
#define GY_IMU_PACKAGE_LENGTH 	18
/* =========================== Vec_Eul of begin =========================== */
typedef struct 
{
		float x;
		float y;
		float z;
}vector_t;

typedef struct 
{
	float roll;
	float pitch;
	float yaw;
}eular_t;

typedef struct
{
	vector_t gyro;
	eular_t eular;
	
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t devStatus; 
	
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}IMU_t;

/*云台IMU结构体*/
extern IMU_t Cloud_IMU;

/*云台IMU数据储存结构体*/
extern uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];
/* =========================== Vec_Eul of end =========================== */

/*IMU初始化*/
void IMU_Init(void);

/*IMU数据解码*/
void IMU_getinfo(uint8_t* buff, uint16_t dataLength, IMU_t* dataOut);

/*IMU单个数据校验*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

/*云台IMU数值状态同步*/
void IMU_Synchronization(float YAW_InputSetting,float Pitch_InputSetting);


#endif	// __IMU_H
/*-----------------------------------file of end------------------------------*/


