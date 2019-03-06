#include "BSP_INIT.h"
#include "delay.h"
#include "Config.h"

u8 DBUS_DataBuf[Rc_BuffSIZE];
u8 GYIMU_RxBuff[GYIMU_BuffSIZE];
u8 Judge_DataBuff[Judge_BuffSIZE];

void BSP_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(180);			//初始化滴答时钟
	CAN1_Init();					//can结构初始化
	BEEP_Init(89, 2000);	//蜂鸣器初始化
	LED_Init();						//led灯初始化
	FrictBSP_init();			//摩擦轮电机pwm初始化
	IMUBSP_Init();				//陀螺仪初始化
	Dr16BSP_Init();				//遥控器初始化
	USART2_Init(115200);	//串口2初始化
	JudgeBSP_Init();			//裁判系统初始化
	ServoBSP_Init();			//舵机初始化
}


void IMUBSP_Init(void)
{
//陀螺仪gy955配置
#if IMUGY955_BSP_CONFIG == 3
	USART3_Init(115200);
	USART3_RXDMA_Config((uint32_t)GYIMU_RxBuff,GYIMU_BuffSIZE);	
#elif IMUGY955_BSP_CONFIG == 6
	USART6_Init(115200);	
	USART6_RXDMA_Config((uint32_t)GYIMU_RxBuff,GYIMU_BuffSIZE);	
#elif IMUGY955_BSP_CONFIG == 7
	UART7_Init(115200);
	UART7_RXDMA_Config((uint32_t)GYIMU_RxBuff,GYIMU_BuffSIZE);	
#elif IMUGY955_BSP_CONFIG == 8
	UART8_Init(115200);	
	UART8_RXDMA_Config((uint32_t)GYIMU_RxBuff,GYIMU_BuffSIZE);	
#endif
	
}


void FrictBSP_init(void)
{	
#if FRICT_BSP_CONFIG == 1
	TIM1_PWM_Init(179, 19999,1000);		//摩擦轮180M/180/20000=50HZ
#elif FRICT_BSP_CONFIG == 12
	TIM12_PWM_Init(89, 19999,1000);		//摩擦轮180M/180/20000=50HZ
#elif FRICT_BSP_CONFIG == 5
	TIM5_PWM_Init(89, 19999,1000);		//摩擦轮180M/180/20000=50HZ	
#elif FRICT_BSP_CONFIG == 8
	TIM8_PWM_Init(179, 19999,1000);		//摩擦轮180M/180/20000=50HZ
#endif	
}

void Dr16BSP_Init(void)
{
#if DR16_BSP_CONFIG == 1
	USART1_Init(100000);
	USART1_RXDMA_Config((uint32_t)DBUS_DataBuf,Rc_BuffSIZE);	
#else
	
#endif
}


void JudgeBSP_Init(void)
{
#if JUDGE_BSP_CONFIG ==6
	USART6_Init(115200);
	USART6_RXDMA_Config((uint32_t)Judge_DataBuff,Judge_BuffSIZE);	
#elif JUDGE_BSP_CONFIG == 7
	UART7_Init(115200);
	UART7_RXDMA_Config((uint32_t)Judge_DataBuff,Judge_BuffSIZE);	
#endif
}


void ServoBSP_Init(void)
{
#if LIDSERVO_BSP_CONFIG == 5
	TIM5_PWM_Init(89, 19999,1000);		//摩擦轮180M/180/20000=50HZ
#endif
}


