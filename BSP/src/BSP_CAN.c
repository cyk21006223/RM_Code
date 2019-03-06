#include "BSP_CAN.h"
#include "BSP_USART.h"

void CAN1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef FilterStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(CAN1_RX_GPIO_CLK | CAN1_TX_GPIO_CLK, ENABLE);
	//使能CAN2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = CAN1_TX_Pin;  
	GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = CAN1_RX_Pin;
	GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(CAN1_TX_GPIO_PORT, CAN1_TX_PINSOURCE, GPIO_AF_CAN1);
	GPIO_PinAFConfig(CAN1_RX_GPIO_PORT, CAN1_RX_PINSOURCE, GPIO_AF_CAN1);
	
	//配置can1
	CAN_InitStructure.CAN_TTCM = DISABLE;//禁止时间触发通讯模式
	CAN_InitStructure.CAN_ABOM = ENABLE;//禁止自动离线管理
	CAN_InitStructure.CAN_AWUM = ENABLE;//禁止自动唤醒
	CAN_InitStructure.CAN_NART = DISABLE;//禁止自动重发传输
	CAN_InitStructure.CAN_RFLM = DISABLE;//fifo不锁定，新覆盖旧
	CAN_InitStructure.CAN_TXFP = DISABLE;//不使用fifo优先级
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//设置can1的工作模式-正常模式
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;//设置重新同步跳跃宽度2
	CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;//设置时间段1时间
	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;//设置时间段2时间
	CAN_InitStructure.CAN_Prescaler = 5;//设定一个时间单位长度
	CAN_Init(CAN1,&CAN_InitStructure);//初始化can1
	
	//配置过滤器
	FilterStructure.CAN_FilterNumber = 0;//指定待初始化过滤器0、
	FilterStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//设置初始化后模式为标识符屏蔽为模式
	FilterStructure.CAN_FilterScale = CAN_FilterScale_32bit;//过滤器位宽为32bit
	FilterStructure.CAN_FilterIdHigh = 0x0000;//设置32位过滤器标识符高16位
	FilterStructure.CAN_FilterIdLow = 0x0000;//设置32位过滤器标识符低16位
	FilterStructure.CAN_FilterMaskIdHigh = 0x0000;//过滤器屏蔽标识符
	FilterStructure.CAN_FilterMaskIdLow = 0x0000;//过滤器屏蔽标识符
	FilterStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;//设置过滤器关联到fifo0
	FilterStructure.CAN_FilterActivation = ENABLE;//使能过滤器0
	CAN_FilterInit(&FilterStructure);//初始化过滤器0
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}


void CAN2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(CAN2_RX_GPIO_CLK | CAN2_TX_GPIO_CLK, ENABLE);
	//使能CAN2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = CAN2_TX_Pin;  
	GPIO_Init(CAN2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = CAN2_RX_Pin;
	GPIO_Init(CAN2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(CAN2_TX_GPIO_PORT, CAN2_TX_PINSOURCE, GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN2_RX_GPIO_PORT, CAN2_RX_PINSOURCE, GPIO_AF_CAN2);
	
	/************************CAN 模式配置*********************************************/
	CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  时间触发通信模式
	CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  自动离线管理 
	CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  使用自动唤醒模式
	CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
	CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
	CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  工作模式
	
	CAN_InitStructure.CAN_SJW = CAN2_SJW;		   	   //BTR-SJW 重新同步跳跃宽度 2个时间单元
	
	/* ss=1 bs1=5 bs2=3 位时间宽度为(1+9+4) 波特率即为时钟周期tq*(1+9+4)  */
	CAN_InitStructure.CAN_BS1 = CAN2_BS1;		   //BTR-TS1 时间段1 占用了6个时间单元
	CAN_InitStructure.CAN_BS2 = CAN2_BS2;		   //BTR-TS1 时间段2 占用了3个时间单元	
	
	/* CAN Baudrate = 1 MBps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB 1 = 42 MHz) */
	CAN_InitStructure.CAN_Prescaler = CAN2_Prescaler;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 42/(1+9+4)/3=1 Mbps
	CAN_Init(CAN2, &CAN_InitStructure);
	

	/*********************CAN筛选器初始化***********************************************/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;									//筛选器组0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//工作在ID掩码模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//筛选器位宽为单个32位。
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;			//筛选器被关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//使能筛选器
	
	//不过滤
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//要筛选的ID高位 
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//要筛选的ID低位 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//筛选器高16位每位不须匹配
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//筛选器低16位每位不须匹配
	
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	/* FIFO0 message pending interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}




