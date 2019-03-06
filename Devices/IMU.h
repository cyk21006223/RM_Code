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
  |--FileName    : IMU.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ����                                                       
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

/*��Ч���ݳ���*/
#define GY_IMU_BUFFSIZE 30

/*���ݰ�����*/
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

/*��̨IMU�ṹ��*/
extern IMU_t Cloud_IMU;

/*��̨IMU���ݴ���ṹ��*/
extern uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];
/* =========================== Vec_Eul of end =========================== */

/*IMU��ʼ��*/
void IMU_Init(void);

/*IMU���ݽ���*/
void IMU_getinfo(uint8_t* buff, uint16_t dataLength, IMU_t* dataOut);

/*IMU��������У��*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

/*��̨IMU��ֵ״̬ͬ��*/
void IMU_Synchronization(float YAW_InputSetting,float Pitch_InputSetting);


#endif	// __IMU_H
/*-----------------------------------file of end------------------------------*/


