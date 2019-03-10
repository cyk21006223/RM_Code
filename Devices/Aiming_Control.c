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
  |--FileName    : Aiming_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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

/*�������ݴ�������*/
uint8_t CV_RXBUFF[8];

/*�������ݴ���ṹ��*/
CV_t ControlVision;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-27 17:46
  * @brief   �����ʼ��
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
  * @brief   ���������ж�
  * @param   void
  * @retval  void
  */
 /*����鿴����*/

void Aiming_Process(int Input_x,int Input_y,CV_t* CV)
{
	/*�˲�֮���X���Y�������*/
	int x_ILF = 0,y_ILF = 0;
  /*����ת��*/
  CV->Input_x = Input_x;
  CV->Input_y = Input_y;

  Filter_IIRLPFInt(&Input_x,&x_ILF,0.6);
  Filter_IIRLPFInt(&Input_y,&y_ILF,0.4);
	
	CV->LPF_x = x_ILF;
	CV->LPF_y = y_ILF;
	
	CV->Output_x = x_ILF-320;
	CV->Output_y = y_ILF-240;
}
