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
  |--FileName    : Filter.h                                                
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
#ifndef __FILTER_H 
#define __FILTER_H 

#include "stm32f4xx.h"

/*���ݵ�ͨ�˲�ͨ��float*/
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor);

/*���ݵ�ͨ�˲�ͨ��int*/
void Filter_IIRLPFInt(int *in, int *out, float LpfAttFactor);

#endif	// __FILTER_H
/*-----------------------------------file of end------------------------------*/


