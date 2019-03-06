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
  |--FileName    : DR16.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
  |--Date        : 2019-02-21             
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
#include "DR16.h" 

/*DR16������*/
uint8_t DR16_Buff[18u+2];

/*DR16ң����������*/
DR16_t DR16;

/*ң������ֵ*/
RCRocket_t RCRocket;

/*����PC��ֵ*/

/*����ͨ�ýṹ��*/
Key_st keyBorad;
Key_st MouseKeyLeft;
Key_st MouseKeyRight;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-21 10:53
  * @brief   DR16ң������ʼ��
  * @param   void
  * @retval  void
  */
void DR16_Init(void)
{
  USART1_QuickInit(100000);
	USART1_RXDMA_Config((uint32_t)DR16_Buff, 18u+2);
}

/**
  * @Data    2019-02-21 11:07
  * @brief   DR16ң��������
  * @param   uint8_t *pData
  * @retval  void
  */
void DR16_Process(uint8_t *pData)
{
    /*��ֵ����*/
	if(pData == NULL)
	{
		return;
	}

    /*ң����*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
  DR16.rc.ch5_wheel = (pData[16] | (pData[17] << 8)) & 0x07FF;
  
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
  
	
	/*���*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);

  /*ͨ�����ֵ���*/
  DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	DR16.rc.ch5_wheel -=1024;
  /*ͨ��ֵ�˶�*/
  DR16.rc.ch0 = Data_Suppers(DR16.rc.ch0);
	DR16.rc.ch1 = Data_Suppers(DR16.rc.ch1);
	DR16.rc.ch2 = Data_Suppers(DR16.rc.ch2);
	DR16.rc.ch3 = Data_Suppers(DR16.rc.ch3);
  DR16.rc.ch5_wheel = Data_Suppers(DR16.rc.ch5_wheel);

  /*ң����ҡ��ģ�͸�ֵ*/
  Rocket_transport(DR16.rc.ch3,-DR16.rc.ch2,DR16.rc.ch0,DR16.rc.ch1,\
  DR16.rc.ch5_wheel,&RCRocket);

  /*�����ж�*/
  DR16_KeyState(DR16.mouse.keyLeft,&MouseKeyLeft);
  DR16_KeyState(DR16.mouse.keyRight,&MouseKeyRight);
  DR16_KeyState(DR16.keyBoard.key_code,&keyBorad);

  /*֡�ʼ���*/
  DR16.UpdateFrame++;

  /*ң����ģʽ��ȡ*/
  Chassis.RCmodeswitch = DR16.rc.s_right;
  Cloud.RCmodeswitch = DR16.rc.s_right;


}


/**
  * @Data    2019-02-21 11:09
  * @brief   DR16ͨ��ֵ�˶�����
  * @param   int16_t data
  * @retval  int
  */
int Data_Suppers(int16_t data)
{
    if(abs_Calculation(data) < 20)
	{
		data = 0;
	}
	return data;
}

/**
  * @Data    2019-02-21 11:13
  * @brief   ҡ��ģ�͸�ֵ
  * @param   float POSLeft_x, 
  *          float POSLeft_y,
  *          float POSRight_x,
  *          float POSRight_y,
  *          Rocket_t *rocket
  * @retval  void
  */
void Rocket_transport(float POSLeft_x, float POSLeft_y,float POSRight_x,\
float POSRight_y,float Flatwheel,RCRocket_t *rocket)
{
    /*ҡ�˸�ֵ*/
    rocket->Left_x = POSLeft_x;
    rocket->Left_y = POSLeft_y;
    rocket->Right_x = POSRight_x;
    rocket->Right_y = POSRight_y;

    rocket->Left_radian = atan2(rocket->Left_y,rocket->Left_x);
    rocket->Right_radian = atan2(rocket->Right_y,rocket->Right_x);

    rocket->Left_degrees = rocket->Left_radian * 180.0f / PI;
    rocket->Right_degrees = rocket->Right_radian * 180.0f / PI;

    rocket->Left_distance = __sqrtf(pow(rocket->Left_x,2) + pow(rocket->Left_y,2));
    rocket->Right_distance = __sqrtf(pow(rocket->Right_x,2) + pow(rocket->Right_y,2));
    if(rocket -> Left_degrees > 180)
    {
        rocket -> Left_distance = -rocket -> Left_distance;
    }
    if(rocket ->Right_degrees > 180)
    {
        rocket -> Right_distance = -rocket -> Right_distance;
    }



}


