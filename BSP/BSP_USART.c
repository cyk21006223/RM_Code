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
  |--FileName    : BSP_USART.c                                              
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
#include "BSP_USART.h" 

/*-----------------------------------file of end------------------------------*/
/**
  * @Data    2019-02-21 10:36
  * @brief   USART1(DR16)初始化
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART1_QuickInit(uint32_t USART_BaudRate)
{
    /*使能结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* 使能 GPIO 时钟 */
    /*USART1_TX -> PB6*/
    /*USART1_RX -> PB7*/
    RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK,ENABLE);

    /* 使能 USART1 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /* 配置Tx引脚  */
    GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

    /* 配置Rx引脚 */
    GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

    /*映射接口复用*/
    /* 连接 PXx 到 USARTx_Tx，其实就是IO口复用*/
    GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

    /*  连接 PXx 到 USARTx_Rx，其实就是IO口复用*/
    GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

    /* 配置串USART 模式 */
    /* 波特率设置：USART_BAUDRATE */
    USART_InitStructure.USART_BaudRate = USART_BaudRate;

    /* 数据长度(数据位+校验位)：8 */
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    /* 停止位：1个停止位 */
    USART_InitStructure.USART_StopBits = USART_StopBits_1;

    /* 校验位选择：不使用校验 */
    USART_InitStructure.USART_Parity = USART_Parity_No;

    /* 硬件流控制：不使用硬件流 */
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    /* USART模式控制：同时使能接收和发送 */
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* 完成USART初始化配置 */
    USART_Init(USART1, &USART_InitStructure);

    /* 串口中断优先级配置 */
    NVIC_Config(USART1_IRQn, 7, 0);

    /* 使能串口空闲中断 */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    /* 使能串口 */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @Data    2019-02-21 10:37
  * @brief   USART1_DMA初始化
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*开启DMA2时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /*这里USART1的DMA通道对应的是DMA2的通道4，数据流2，这个可以通过查DMA外设通道查的*/
    DMA_DeInit(USART1_RX_DMA_STREAM);

    /* 确保DMA数据流复位完成 */
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE)
    {
        /*如果没有复位完成会无限的卡着while这里*/
    }

    /*usart1 rx对应dma2，通道4，数据流2*/
    DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;

    /*设置DMA源：串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;//(uint32_t)(&USART1->DR)	//串口1数据寄存器地址

    /*内存地址(要传输的变量的指针)*/
    /*USART1_DMABuff_addr ->参数*/
    /*参数，可自己设定*/
    DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;

    /*方向：从外设到内存*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

    /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/
    /*buffsize ->参数*/
    DMA_InitStructure.DMA_BufferSize = buffsize;

    /*外设地址不增*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /*外设数据单位*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /*DMA模式：不断循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

    /*优先级：中*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*禁用FIFO*/
    /*查清楚这里是什么意思的*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    /*存储器突发传输 16 个节拍*/
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;

    /*外设突发传输 1 个节拍*/
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /*配置DMA2的数据流*/
    DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);

    /*使能DMA*/
    DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);

    /* 等待DMA数据流有效*/
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE)
    {

    }

    /*使能DMA接收请求*/
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}



/**
  * @Data    2019-02-24 18:14
  * @brief   USART2串口通道初始化
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART2_QuickInit(uint32_t USART_BaudRate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);

	/* 使能 USART2 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART2, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART2_IRQn, 8, 0);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART2, ENABLE);
}

/**
  * @Data    2019-02-24 18:17
  * @brief   USART2通道和自瞄
  * @param   uint32_t USART2_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
{

  DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA1时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART2_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != DISABLE)
	{
		
	}

	/*usart2 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = USART2_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART2_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != ENABLE)
	{
    
	}
  
	//使能DMA接收  
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
}
/**
  * @Data    2019-02-22 11:28
  * @brief   USART6初始化(IMU初始化)
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART6_QuickInit(uint32_t USART_BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK | USART6_RX_GPIO_CLK,ENABLE);

	/* 使能 USART6 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;  
	GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;
	GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART6, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART6_IRQn, 8, 0);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART6, ENABLE);
}

/**
  * @Data    2019-02-22 11:30
  * @brief   USART6_DMA初始化
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
  DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA2时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(USART6_RX_DMA_STREAM);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != DISABLE)
	{
		
	}

	/*usart6 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = USART6_RX_DMA_CHANNEL;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART6_RX_ADDR;	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(USART6_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != ENABLE){
	}
  
	//使能DMA接收  
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE); 
}




/* =========================== USART_PRINTF of begin =========================== */

/**
  * @Data    2019-02-22 11:47
  * @brief   USART使用printf，scanf端口设置（一整套）
  * @param   USART_TypeDef* USARTx
  * @retval  void
  */
/*正常的定义方式*/
// static USART_TypeDef* Using_USART;

/*可以使用便捷的方式来定义串口*/
static USART_TypeDef* Using_USART = USART2;

/*更改定义函数*/
void USART_setPort(USART_TypeDef* USARTx)
{
    Using_USART = USARTx;
}

/**
  * @Data    2019-02-22 11:44
  * @brief   printf重定向函数（需要配合端口设置）
  * @param   int ch, FILE *f 
  * @retval  int
  */
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(Using_USART, (uint8_t) ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);

    return (ch);
}

/**
  * @Data    2019-02-22 11:52
  * @brief   scanf重定向函数（需要配合端口设置）
  * @param   FILE* f
  * @retval  int
  */
int fgetc(FILE* f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(Using_USART);
}

/*ANO发送*/

/* =========================== USART_PRINTF of end =========================== */




