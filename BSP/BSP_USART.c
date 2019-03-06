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
  |--FileName    : BSP_USART.c                                              
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
#include "BSP_USART.h" 

/*-----------------------------------file of end------------------------------*/
/**
  * @Data    2019-02-21 10:36
  * @brief   USART1(DR16)��ʼ��
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART1_QuickInit(uint32_t USART_BaudRate)
{
    /*ʹ�ܽṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* ʹ�� GPIO ʱ�� */
    /*USART1_TX -> PB6*/
    /*USART1_RX -> PB7*/
    RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK,ENABLE);

    /* ʹ�� USART1 ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /* ����Tx����  */
    GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

    /* ����Rx���� */
    GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

    /*ӳ��ӿڸ���*/
    /* ���� PXx �� USARTx_Tx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

    /*  ���� PXx �� USARTx_Rx����ʵ����IO�ڸ���*/
    GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

    /* ���ô�USART ģʽ */
    /* ���������ã�USART_BAUDRATE */
    USART_InitStructure.USART_BaudRate = USART_BaudRate;

    /* ���ݳ���(����λ+У��λ)��8 */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    /* ֹͣλ��1��ֹͣλ */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;

    /* У��λѡ�񣺲�ʹ��У�� */
    USART_InitStructure.USART_Parity = USART_Parity_No;

    /* Ӳ�������ƣ���ʹ��Ӳ���� */
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    /* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* ���USART��ʼ������ */
    USART_Init(USART1, &USART_InitStructure);

    /* �����ж����ȼ����� */
    NVIC_Config(USART1_IRQn, 7, 0);

    /* ʹ�ܴ��ڿ����ж� */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    /* ʹ�ܴ��� */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @Data    2019-02-21 10:37
  * @brief   USART1_DMA��ʼ��
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*����DMA2ʱ��*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /*����USART1��DMAͨ����Ӧ����DMA2��ͨ��4��������2���������ͨ����DMA����ͨ�����*/
    DMA_DeInit(USART1_RX_DMA_STREAM);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE)
    {
        /*���û�и�λ��ɻ����޵Ŀ���while����*/
    }

    /*usart1 rx��Ӧdma2��ͨ��4��������2*/
    DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;

    /*����DMAԴ���������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;//(uint32_t)(&USART1->DR)	//����1���ݼĴ�����ַ

    /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    /*USART1_DMABuff_addr ->����*/
    /*���������Լ��趨*/
    DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;

    /*���򣺴����赽�ڴ�*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
    /*buffsize ->����*/
    DMA_InitStructure.DMA_BufferSize = buffsize;

    /*�����ַ����*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /*�������ݵ�λ*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /*DMAģʽ������ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

    /*���ȼ�����*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*����FIFO*/
    /*�����������ʲô��˼��*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    /*�洢��ͻ������ 16 ������*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;

    /*����ͻ������ 1 ������*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /*����DMA2��������*/
    DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);

    /*ʹ��DMA*/
    DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);

    /* �ȴ�DMA��������Ч*/
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE)
    {

    }

    /*ʹ��DMA��������*/
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}



/**
  * @Data    2019-02-24 18:14
  * @brief   USART2����ͨ����ʼ��
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART2_QuickInit(uint32_t USART_BaudRate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* ʹ�� GPIO ʱ�� */
	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);

	/* ʹ�� USART2 ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

	/*  ���� PXx �� USARTx_Rx*/
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);
  
	/* ���ô�USART ģʽ */
	/* ���������ã�USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* ���ݳ���(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(USART2, &USART_InitStructure); 
	
	/* �����ж����ȼ����� */
	NVIC_Config(USART2_IRQn, 8, 0);
  
	/* ʹ�ܴ��ڽ����ж� */
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	
	/* ʹ�ܴ��� */
	USART_Cmd(USART2, ENABLE);
}

/**
  * @Data    2019-02-24 18:17
  * @brief   USART2ͨ��������
  * @param   uint32_t USART2_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
{

  DMA_InitTypeDef DMA_InitStructure;

	/*����DMA1ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	  
	/* ��λ��ʼ��DMA������ */
	DMA_DeInit(USART2_RX_DMA_STREAM);

	/* ȷ��DMA��������λ��� */
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != DISABLE)
	{
		
	}

	/*usart2 rx��Ӧdma1��ͨ��4��������5*/	
	DMA_InitStructure.DMA_Channel = USART2_RX_DMA_CHANNEL;  
	/*����DMAԴ���������ݼĴ�����ַ*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RX_ADDR;	 
	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;
	/*���򣺴����赽�ڴ�*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*�����ַ����*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*�ڴ��ַ����*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*�������ݵ�λ*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMAģʽ������ѭ��*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*���ȼ�����*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*����FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*�洢��ͻ������ 16 ������*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*����ͻ������ 1 ������*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*����DMA2��������*/		   
	DMA_Init(USART2_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*ʹ��DMA*/
	DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
  
	/* �ȴ�DMA��������Ч*/
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != ENABLE)
	{
    
	}
  
	//ʹ��DMA����  
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
}
/**
  * @Data    2019-02-22 11:28
  * @brief   USART6��ʼ��(IMU��ʼ��)
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART6_QuickInit(uint32_t USART_BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* ʹ�� GPIO ʱ�� */
	RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK | USART6_RX_GPIO_CLK,ENABLE);

	/* ʹ�� USART6 ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;  
	GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;
	GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);

	/*  ���� PXx �� USARTx_Rx*/
	GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);
  
	/* ���ô�USART ģʽ */
	/* ���������ã�USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* ���ݳ���(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(USART6, &USART_InitStructure); 
	
	/* �����ж����ȼ����� */
	NVIC_Config(USART6_IRQn, 8, 0);
  
	/* ʹ�ܴ��ڽ����ж� */
	//USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
	
	/* ʹ�ܴ��� */
	USART_Cmd(USART6, ENABLE);
}

/**
  * @Data    2019-02-22 11:30
  * @brief   USART6_DMA��ʼ��
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
  DMA_InitTypeDef DMA_InitStructure;

	/*����DMA2ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* ��λ��ʼ��DMA������ */
	DMA_DeInit(USART6_RX_DMA_STREAM);

	/* ȷ��DMA��������λ��� */
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != DISABLE)
	{
		
	}

	/*usart6 rx��Ӧdma1��ͨ��4��������5*/	
	DMA_InitStructure.DMA_Channel = USART6_RX_DMA_CHANNEL;  
	/*����DMAԴ���������ݼĴ�����ַ*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART6_RX_ADDR;	 
	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;
	/*���򣺴����赽�ڴ�*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*�����ַ����*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*�ڴ��ַ����*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*�������ݵ�λ*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMAģʽ������ѭ��*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*���ȼ�����*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*����FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*�洢��ͻ������ 16 ������*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*����ͻ������ 1 ������*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*����DMA2��������*/		   
	DMA_Init(USART6_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*ʹ��DMA*/
	DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
  
	/* �ȴ�DMA��������Ч*/
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != ENABLE){
	}
  
	//ʹ��DMA����  
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE); 
}




/* =========================== USART_PRINTF of begin =========================== */

/**
  * @Data    2019-02-22 11:47
  * @brief   USARTʹ��printf��scanf�˿����ã�һ���ף�
  * @param   USART_TypeDef* USARTx
  * @retval  void
  */
/*�����Ķ��巽ʽ*/
// static USART_TypeDef* Using_USART;

/*����ʹ�ñ�ݵķ�ʽ�����崮��*/
static USART_TypeDef* Using_USART = USART2;

/*���Ķ��庯��*/
void USART_setPort(USART_TypeDef* USARTx)
{
    Using_USART = USARTx;
}

/**
  * @Data    2019-02-22 11:44
  * @brief   printf�ض���������Ҫ��϶˿����ã�
  * @param   int ch, FILE *f 
  * @retval  int
  */
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ����� */
    USART_SendData(Using_USART, (uint8_t) ch);

    /* �ȴ�������� */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);

    return (ch);
}

/**
  * @Data    2019-02-22 11:52
  * @brief   scanf�ض���������Ҫ��϶˿����ã�
  * @param   FILE* f
  * @retval  int
  */
int fgetc(FILE* f)
{
    /* �ȴ������������� */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(Using_USART);
}

/*ANO����*/

/* =========================== USART_PRINTF of end =========================== */




