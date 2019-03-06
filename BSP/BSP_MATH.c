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
  |--FileName    : BSP_MATH.c                                              
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
#include "BSP_MATH.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-19 15:16
  * @brief   目标绝对值
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
  * @brief   Ki限幅
  * @param   float *KI_OUT, 对应值
  *          float MAXER    限幅值
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
  * @brief   PWM输出限幅
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


