#include "BSP_USART.h"	

//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((UART7->SR&0X40)==0);//循环发送,直到发送完毕   
	UART7->DR = (u8) ch;      
	return ch;
}

//串口1初始化
void USART1_Init(u32 bound){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

#if USART1_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART1_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;  
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);
#endif
	
#if USART1_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);
#endif
 
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//USART_ITConfig(USART1, USART_IT_PE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
	
	USART_Cmd(USART1, ENABLE);
}




//初始化IO 串口2
//bound:波特率
void USART2_Init(u32 bound){
	
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	
#if USART2_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART2_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;  
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);
#endif

#if	USART2_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);
#endif

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

//	//Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

}




//串口3初始化---
void USART3_Init(u32 bound){
		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
#if USART3_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART3_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;  
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
#endif

#if	USART3_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);
#endif


	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure); 

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART3, USART_IT_PE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//空闲中断
	
	USART_Cmd(USART3, ENABLE);
}



//串口1DMA配置函数
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//开启DMA2时钟
	  
	DMA_DeInit(DMA2_Stream2);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart1 rx对应dma2，通道4，数据流2 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA2_Stream2, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA2_Stream2, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA2_Stream2) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
}



void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
	  
	DMA_DeInit(DMA1_Stream1);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart3 rx对应dma1，通道4，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA1_Stream1, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA1_Stream1, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream1) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
}



//串口6初始化---接收陀螺仪数据
void USART6_Init(u32 bound)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
#if USART6_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART6_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;  
	GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);
#endif

#if	USART6_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;
	GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);
#endif

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure); 

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART3, USART_IT_PE, ENABLE);
	USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);//空闲中断
	
	USART_Cmd(USART6, ENABLE);
}



void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//开启DMA1时钟
	  
	DMA_DeInit(DMA2_Stream1);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx对应dma1，通道5，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART6->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA2_Stream1, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA2_Stream1) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
}


//初始化IO 串口7
//bound:波特率
void UART7_Init(u32 bound)
{
	
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,ENABLE);//使能USART2时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	
	
#if UART7_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(UART7_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = UART7_RX_Pin;  
	GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART7_RX_GPIO_PORT, UART7_RX_PINSOURCE, GPIO_AF_UART7);
#endif

#if	UART7_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(UART7_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = UART7_TX_Pin;
	GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART7_TX_GPIO_PORT, UART7_TX_PINSOURCE, GPIO_AF_UART7);
#endif

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART7, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(UART7, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(UART7, USART_IT_IDLE, ENABLE);//空闲中断
	//USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=5;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

}



void UART7_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
	  
	DMA_DeInit(DMA1_Stream3);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx对应dma1，通道5，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART7->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA1_Stream3, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream3) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(UART7,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
}



//初始化IO 串口78
//bound:波特率
void UART8_Init(u32 bound)
{
	
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE);//使能USART2时钟
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	
#if UART8_RX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(UART8_RX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = UART8_RX_Pin;  
	GPIO_Init(UART8_RX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART8_RX_GPIO_PORT, UART8_RX_PINSOURCE, GPIO_AF_UART8);
#endif

#if	UART8_TX_ENABLE == 1
	RCC_AHB1PeriphClockCmd(UART8_TX_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = UART8_TX_Pin;
	GPIO_Init(UART8_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(UART8_TX_GPIO_PORT, UART8_TX_PINSOURCE, GPIO_AF_UART8);
#endif

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART8, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(UART8, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(UART8, USART_FLAG_TC);
	
	USART_ITConfig(UART8, USART_IT_IDLE, ENABLE);//空闲中断
	//USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=5;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

}



void UART8_RXDMA_Config(uint32_t UART8_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
	  
	DMA_DeInit(DMA1_Stream6);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx对应dma1，通道5，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART8->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = UART8_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA1_Stream6, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream6) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(UART8,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
}


/**
  * @brief  USART发送一个字符
  * @param  USARTx 	USART外设
  *			ch 		字符
  * @retval None
  */
void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USARTx, (uint8_t) ch);
	
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}


















