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
  |--FileName    : Current_Setting.h                                                
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
#ifndef __CURRENT_SETTING_H 
#define __CURRENT_SETTING_H 

#include "stm32f4xx.h"
#include "BSP_CAN.h"

/*���̵���ֵ����*/
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4);

/*��̨������Ħ���ֵ�������*/
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, \
int16_t I_Emitter, int16_t OVER);

/*��̨����ֵ����*/
void Cloud_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch);

/*�����������ֵ����*/
void Cartridge_CurrentSetting(int16_t I_Emitter);

#endif	// __CURRENT_SETTING_H
/*-----------------------------------file of end------------------------------*/


