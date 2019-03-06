/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     				 |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_CAN.c                                              
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
#include "BSP_CAN.h" 
    
/*-----------------------------------file of end------------------------------*/





/**
  * @Data    2019-02-18 20:52
  * @brief   CAN1快速初始化
  * @param   void
  * @retval  void
  */
void CAN1_QuickInit(void)
{
    /*各种结构体使能*/
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 
    /*CAN1TX -> PD1*/
    /*CAN1RX -> PD0*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*配置CAN1的TX引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* 连接 IO 到 CAN1_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);


    /*配置CAN1的RX引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*  连接 IO 到 CAN1_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    /********************************CAN基本配置*******************************/
    /*MCR-TTCM  时间触发通信模式*/
    CAN_InitStructure.CAN_TTCM = DISABLE;

    /*MCR-ABOM  自动离线管理*/
    CAN_InitStructure.CAN_ABOM = ENABLE;

    /*MCR-AWUM  使用自动唤醒模式*/
    CAN_InitStructure.CAN_AWUM = ENABLE;

    /*MCR-NART  禁止报文自动重传 DISABLE-自动重传*/			   
    CAN_InitStructure.CAN_NART = DISABLE;

    /*MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文*/
    CAN_InitStructure.CAN_RFLM = DISABLE;

	/*MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符*/
    CAN_InitStructure.CAN_TXFP = DISABLE;

    /*Mode  工作模式*/
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	  

    /*三时间宽度设置，分频器设置，定义了时间单元的时间长度 45/(1+3+5)/5=1 Mbps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 5;
    
    CAN_Init(CAN1, &CAN_InitStructure);


    /*************************CAN筛选器初始化*************************/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			

    CAN_FilterInit(&CAN_FilterInitStructure);

    NVIC_Config(CAN1_RX0_IRQn, 10, 0);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}


/**
  * @Data    2019-02-19 11:42
  * @brief   通过CAN发送指令到对应的ID上
  * @param   CAN_TypeDef* CANx,   对应的CAN
  *          uint8_t id_type,     对应的ID模式
  *          uint32_t id,         对应的ID
  *          uint8_t data[8]      储存的数据
  * @retval  void
  */
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8])
{ 
    CanTxMsg TxMessage;

    /*ID号*/
    if(id_type == CAN_Id_Standard) 
		{
        TxMessage.StdId = id;
    }
    else 
		{
        TxMessage.ExtId = id;					 
    }

    /*ID类型*/
    TxMessage.IDE = id_type;

    /*发送的数据*/					 
    TxMessage.RTR = CAN_RTR_DATA;	

    /*数据长度字节为8*/
    TxMessage.DLC = 0x08;						 

    /*设置要发送的数据，储存进结构体中*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    /*发送数据*/
    CAN_Transmit(CANx, &TxMessage);
}


 



 


