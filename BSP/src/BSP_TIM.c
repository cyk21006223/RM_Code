#include "BSP_TIM.h"

//TIM1的PWM初始化
void TIM1_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

#if TIM1_CH1_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM1_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM1_CH1_Pin;
	GPIO_Init(TIM1_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH1_GPIO_PORT,TIM1_CH1_PINSOURCE, GPIO_AF_TIM1);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
#endif	

#if TIM1_CH2_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM1_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM1_CH2_Pin;
	GPIO_Init(TIM1_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH2_GPIO_PORT,TIM1_CH2_PINSOURCE, GPIO_AF_TIM1);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
#endif	

#if TIM1_CH3_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM1_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM1_CH3_Pin;
	GPIO_Init(TIM1_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH3_GPIO_PORT,TIM1_CH3_PINSOURCE, GPIO_AF_TIM1);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
#endif	

#if TIM1_CH4_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM1_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM1_CH4_Pin;
	GPIO_Init(TIM1_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM1_CH4_GPIO_PORT,TIM1_CH4_PINSOURCE, GPIO_AF_TIM1);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
#endif	

	//使能定时器
	TIM_Cmd(TIM1, ENABLE);
	
	/* 高级定时器需要使能PWM输出 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


void TIM2_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
#if TIM2_CH1_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM2_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM2_CH1_Pin;
	GPIO_Init(TIM2_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM2_CH1_GPIO_PORT,TIM2_CH1_PINSOURCE, GPIO_AF_TIM2);
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
#endif	

#if TIM2_CH2_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM2_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM2_CH2_Pin;
	GPIO_Init(TIM2_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM2_CH2_GPIO_PORT,TIM2_CH2_PINSOURCE, GPIO_AF_TIM2);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
#endif	

#if TIM2_CH3_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM2_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM2_CH3_Pin;
	GPIO_Init(TIM2_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM2_CH3_GPIO_PORT,TIM2_CH3_PINSOURCE, GPIO_AF_TIM2);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
#endif	

#if TIM2_CH4_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM2_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM2_CH4_Pin;
	GPIO_Init(TIM2_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM2_CH4_GPIO_PORT,TIM2_CH4_PINSOURCE, GPIO_AF_TIM2);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
#endif	

	//使能定时器
	TIM_Cmd(TIM2, ENABLE);
}

void TIM4_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	

#if TIM4_CH1_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM4_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM4_CH1_Pin;
	GPIO_Init(TIM4_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM4_CH1_GPIO_PORT,TIM4_CH1_PINSOURCE, GPIO_AF_TIM4);
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
#endif	

#if TIM4_CH2_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM4_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM4_CH2_Pin;
	GPIO_Init(TIM4_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM4_CH2_GPIO_PORT,TIM4_CH2_PINSOURCE, GPIO_AF_TIM4);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
#endif	

#if TIM4_CH3_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM4_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM4_CH3_Pin;
	GPIO_Init(TIM4_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM4_CH3_GPIO_PORT,TIM4_CH3_PINSOURCE, GPIO_AF_TIM4);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
#endif	

#if TIM4_CH4_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM4_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM4_CH4_Pin;
	GPIO_Init(TIM4_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM4_CH4_GPIO_PORT,TIM4_CH4_PINSOURCE, GPIO_AF_TIM4);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
#endif	

	//使能定时器
	TIM_Cmd(TIM4, ENABLE);
}


void TIM5_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	

#if TIM5_CH1_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM5_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM5_CH1_Pin;
	GPIO_Init(TIM5_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM5_CH1_GPIO_PORT,TIM5_CH1_PINSOURCE, GPIO_AF_TIM5);
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
#endif	

#if TIM5_CH2_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM5_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM5_CH2_Pin;
	GPIO_Init(TIM5_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM5_CH2_GPIO_PORT,TIM5_CH2_PINSOURCE, GPIO_AF_TIM5);
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
#endif	

#if TIM5_CH3_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM5_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM5_CH3_Pin;
	GPIO_Init(TIM5_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM5_CH3_GPIO_PORT,TIM5_CH3_PINSOURCE, GPIO_AF_TIM5);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
#endif	

#if TIM5_CH4_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM5_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM5_CH4_Pin;
	GPIO_Init(TIM5_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM5_CH4_GPIO_PORT,TIM5_CH4_PINSOURCE, GPIO_AF_TIM5);
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
#endif	

	//使能定时器
	TIM_Cmd(TIM5, ENABLE);

}



void TIM8_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	

#if TIM8_CH1_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM8_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH1_Pin;
	GPIO_Init(TIM8_CH1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM8_CH1_GPIO_PORT,TIM8_CH1_PINSOURCE, GPIO_AF_TIM8);
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
#endif	

#if TIM8_CH2_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM8_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH2_Pin;
	GPIO_Init(TIM8_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM8_CH2_GPIO_PORT,TIM8_CH2_PINSOURCE, GPIO_AF_TIM8);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
#endif	

#if TIM8_CH3_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM8_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH3_Pin;
	GPIO_Init(TIM8_CH3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM8_CH3_GPIO_PORT,TIM8_CH3_PINSOURCE, GPIO_AF_TIM8);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
#endif	

#if TIM8_CH4_ENABLE == 1
	//初始化为对应通道的输出，通道1
	RCC_AHB1PeriphClockCmd(TIM8_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH4_Pin;
	GPIO_Init(TIM8_CH4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM8_CH4_GPIO_PORT,TIM8_CH4_PINSOURCE, GPIO_AF_TIM8);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
#endif	

	//使能定时器
	TIM_Cmd(TIM8, ENABLE);

	/* 高级定时器需要使能PWM输出 */
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}




//两个摩擦轮对应tim12的通道1,2 
void TIM12_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOH,GPIO_PinSource6, GPIO_AF_TIM12);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOH,GPIO_PinSource9, GPIO_AF_TIM12);

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	//初始化为对应通道的输出，通道1
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);

	//初始化为对应通道的输出，通道1
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);

	//使能定时器
	TIM_Cmd(TIM12, ENABLE);

}

