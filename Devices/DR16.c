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
  |--FileName    : DR16.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
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

/*DR16储存体*/
uint8_t DR16_Buff[18u+2];

/*DR16遥控器储存体*/
DR16_t DR16;

/*遥控器赋值*/
RCRocket_t RCRocket;

/*电脑PC赋值*/

/*按键通用结构体*/
Key_st keyBorad;
Key_st MouseKeyLeft;
Key_st MouseKeyRight;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-21 10:53
  * @brief   DR16遥控器初始化
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
  * @brief   DR16遥控器解码
  * @param   uint8_t *pData
  * @retval  void
  */
void DR16_Process(uint8_t *pData)
{
    /*空值返回*/
	if(pData == NULL)
	{
		return;
	}

    /*遥控器*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
  DR16.rc.ch5_wheel = (pData[16] | (pData[17] << 8)) & 0x07FF;
  
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
  
	
	/*鼠标*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);

  /*通道数字调零*/
  DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	DR16.rc.ch5_wheel -=1024;
  /*通道值滤抖*/
  DR16.rc.ch0 = Data_Suppers(DR16.rc.ch0);
	DR16.rc.ch1 = Data_Suppers(DR16.rc.ch1);
	DR16.rc.ch2 = Data_Suppers(DR16.rc.ch2);
	DR16.rc.ch3 = Data_Suppers(DR16.rc.ch3);
  DR16.rc.ch5_wheel = Data_Suppers(DR16.rc.ch5_wheel);

  /*遥控器摇杆模型赋值*/
  Rocket_transport(DR16.rc.ch3,-DR16.rc.ch2,DR16.rc.ch0,DR16.rc.ch1,\
  DR16.rc.ch5_wheel,&RCRocket);

  /*按键判定*/
  DR16_KeyState(DR16.mouse.keyLeft,&MouseKeyLeft);
  DR16_KeyState(DR16.mouse.keyRight,&MouseKeyRight);
  DR16_KeyState(DR16.keyBoard.key_code,&keyBorad);

  /*帧率计算*/
  DR16.UpdateFrame++;

  /*遥控器模式读取*/
  Chassis.RCmodeswitch = DR16.rc.s_right;
  Cloud.RCmodeswitch = DR16.rc.s_right;


}


/**
  * @Data    2019-02-21 11:09
  * @brief   DR16通道值滤抖处理
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
  * @brief   摇杆模型赋值
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
    /*摇杆赋值*/
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


