/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Filter.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
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
#include "Filter.h" 

/*-----------------------------------file of end------------------------------*/


/**
  * @Data    2019-02-28 19:35
  * @brief   数据滤波通道
  * @param   float *in,float *out,float LpfAttFactor
  * @retval  void
  */
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}

/**
  * @Data    2019-02-28 20:04
  * @brief   数据低通滤波通道
  * @param   float *in, float *out, float LpfAttFactor
  * @retval  int
  */
void Filter_IIRLPFInt(int *in, int *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}