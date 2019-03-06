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
  |--FileName    : Aiming_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-27             
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
#include "Aiming_Control.h"

/*自瞄数据储存数组*/
uint8_t CV_RXBUFF[8];
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-27 17:46
  * @brief   自瞄初始化
  * @param   void
  * @retval  void
  */
void Aiming_Init(void)
{
  USART2_QuickInit(1500000);
  USART2_RXDMA_Config((uint32_t)CV_RXBUFF, 8);
}


/**
  * @Data    2019-02-27 18:44
  * @brief   自瞄数据判断
  * @param   void
  * @retval  void
  */
 /*方便查看外移*/

void Aiming_Process(int Input_x,int Input_y)
{
  /*正常输出之后的X轴和Y轴数据*/
	int Output_x = 0,Output_y = 0;
	/*滤波之后的X轴和Y轴的数据*/
	int x_ILF = 0,y_ILF = 0;

  Filter_IIRLPFInt(&Input_x,&x_ILF,0.6);
  Filter_IIRLPFInt(&Input_y,&y_ILF,0.4);

	Output_x = x_ILF-320;
	Output_y = y_ILF-240;
}
