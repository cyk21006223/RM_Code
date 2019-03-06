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
  |--FileName    : BSP_NVIC.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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
  * @brief   NVIC���ٳ�ʼ��
  * @param   uint16_t IRQChannel,   ��Ӧ��NVICͨ��
  *          uint16_t MainPriority, ��Ӧ�������ȼ�
  *          uint16_t SubPriority   ��Ӧ�ĸ����ȼ�
  * @retval  void
  */
void NVIC_Config(uint16_t IRQChannel,uint16_t MainPriority,uint16_t SubPriority)
{
    /*�жϽṹ��*/
    NVIC_InitTypeDef NVIC_InitStructure;

    /*�ж���Դͨ��������*/
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;

    /*��Ҫ�����ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;

    /*������ռ�ĵ����ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;

    /*ͨ��ʹ��*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    /*NVIC�жϺ�����װ*/
    NVIC_Init(&NVIC_InitStructure);
}

 