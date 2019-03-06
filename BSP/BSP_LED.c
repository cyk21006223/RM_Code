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
  |--FileName    : BSP_LED.c                                              
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
#include "BSP_LED.h" 
  
/*-----------------------------------file of end------------------------------*/




/**
  * @Data    2019-02-19 11:58
  * @brief   LED等初始化
  * @param   void
  * @retval  void
  */
void LED_Init(void)
{
  /*GPIO结构体初始化*/
  GPIO_InitTypeDef GPIO_InitStructure;

  /*RCC时钟初始化*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB \
  | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;

  #if New_RM
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);

  #else
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_RESET);
  GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
	
	#endif

  #if New_RM
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOG, GPIO_Pin_1, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_2, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_3, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_4, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_5, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_6, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_7, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_8, Bit_SET);
	#endif

	#if Wild_Wolf_BAND
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_11, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_12, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_13, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_14, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_15, Bit_SET);

	#endif


}
