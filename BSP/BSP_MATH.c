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
  |--FileName    : BSP_MATH.c                                              
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
#include "BSP_MATH.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-19 15:16
  * @brief   Ŀ�����ֵ
  * @param   float myabs
  * @retval  float
  */
float abs_Calculation(float myabs)
{
    if(myabs >= 0)
    {
        myabs = myabs;
    }
    if(myabs < 0)
    {
        myabs = -myabs;
    }
    return myabs;
}

/**
  * @Data    2019-02-19 15:17
  * @brief   Ki�޷�
  * @param   float *KI_OUT, ��Ӧֵ
  *          float MAXER    �޷�ֵ
  * @retval  void
  */
void Ki_Limiting(float *KI_OUT,float MAXER)
{
    if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}

/**
  * @Data    2019-02-19 15:19
  * @brief   PWM����޷�
  * @param   float *Output,float MAXER
  * @retval  void
  */
void Output_Limting(float *Output,float MAXER)
{
    if(*Output > MAXER)
    {
        *Output = MAXER;
    }
    if(*Output < -MAXER)
    {
        *Output = -MAXER;
    }
}


