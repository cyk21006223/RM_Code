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
  |--FileName    : BSP_NVIC.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-18             
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
#include "BSP_NVIC.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-18 20:55
  * @brief   NVIC快速初始化
  * @param   uint16_t IRQChannel,   对应的NVIC通道
  *          uint16_t MainPriority, 对应的主优先级
  *          uint16_t SubPriority   对应的副优先级
  * @retval  void
  */
void NVIC_Config(uint16_t IRQChannel,uint16_t MainPriority,uint16_t SubPriority)
{
    /*中断结构体*/
    NVIC_InitTypeDef NVIC_InitStructure;

    /*中断来源通道的设置*/
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;

    /*主要的优先级*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;

    /*设置抢占的的优先级*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;

    /*通道使能*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    /*NVIC中断函数封装*/
    NVIC_Init(&NVIC_InitStructure);
}

 