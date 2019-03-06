/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     				 |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_CAN.c                                              
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
#include "BSP_CAN.h" 
    
/*-----------------------------------file of end------------------------------*/





/**
  * @Data    2019-02-18 20:52
  * @brief   CAN1���ٳ�ʼ��
  * @param   void
  * @retval  void
  */
void CAN1_QuickInit(void)
{
    /*���ֽṹ��ʹ��*/
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

    /*����CAN1��TX����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* ���� IO �� CAN1_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);


    /*����CAN1��RX����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*  ���� IO �� CAN1_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    /********************************CAN��������*******************************/
    /*MCR-TTCM  ʱ�䴥��ͨ��ģʽ*/
    CAN_InitStructure.CAN_TTCM = DISABLE;

    /*MCR-ABOM  �Զ����߹���*/
    CAN_InitStructure.CAN_ABOM = ENABLE;

    /*MCR-AWUM  ʹ���Զ�����ģʽ*/
    CAN_InitStructure.CAN_AWUM = ENABLE;

    /*MCR-NART  ��ֹ�����Զ��ش� DISABLE-�Զ��ش�*/			   
    CAN_InitStructure.CAN_NART = DISABLE;

    /*MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���*/
    CAN_InitStructure.CAN_RFLM = DISABLE;

	/*MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ��*/
    CAN_InitStructure.CAN_TXFP = DISABLE;

    /*Mode  ����ģʽ*/
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	  

    /*��ʱ�������ã���Ƶ�����ã�������ʱ�䵥Ԫ��ʱ�䳤�� 45/(1+3+5)/5=1 Mbps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 5;
    
    CAN_Init(CAN1, &CAN_InitStructure);


    /*************************CANɸѡ����ʼ��*************************/
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
  * @brief   ͨ��CAN����ָ���Ӧ��ID��
  * @param   CAN_TypeDef* CANx,   ��Ӧ��CAN
  *          uint8_t id_type,     ��Ӧ��IDģʽ
  *          uint32_t id,         ��Ӧ��ID
  *          uint8_t data[8]      ���������
  * @retval  void
  */
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8])
{ 
    CanTxMsg TxMessage;

    /*ID��*/
    if(id_type == CAN_Id_Standard) 
		{
        TxMessage.StdId = id;
    }
    else 
		{
        TxMessage.ExtId = id;					 
    }

    /*ID����*/
    TxMessage.IDE = id_type;

    /*���͵�����*/					 
    TxMessage.RTR = CAN_RTR_DATA;	

    /*���ݳ����ֽ�Ϊ8*/
    TxMessage.DLC = 0x08;						 

    /*����Ҫ���͵����ݣ�������ṹ����*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    /*��������*/
    CAN_Transmit(CANx, &TxMessage);
}


 



 


