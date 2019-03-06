/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Filter.c                                              
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
#include "Filter.h" 

/*-----------------------------------file of end------------------------------*/


/**
  * @Data    2019-02-28 19:35
  * @brief   �����˲�ͨ��
  * @param   float *in,float *out,float LpfAttFactor
  * @retval  void
  */
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}

/**
  * @Data    2019-02-28 20:04
  * @brief   ���ݵ�ͨ�˲�ͨ��
  * @param   float *in, float *out, float LpfAttFactor
  * @retval  int
  */
void Filter_IIRLPFInt(int *in, int *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}