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
  |--FileName    : BSP_TIM.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-24             
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
#include "BSP_TIM.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-24 16:24
  * @brief   摩擦轮初始化
  * @param   void
  * @retval  static void
  */
static void TIM5_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(TIM5_CH1_GPIO_CLK | TIM5_CH2_GPIO_CLK,ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_InitStructure.GPIO_Pin = TIM5_CH1_Pin;
    GPIO_Init(TIM5_CH1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(TIM5_CH1_GPIO_PORT,TIM5_CH1_PINSOURCE, GPIO_AF_TIM5);

    GPIO_InitStructure.GPIO_Pin = TIM5_CH2_Pin;
    GPIO_Init(TIM5_CH2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(TIM5_CH2_GPIO_PORT,TIM5_CH2_PINSOURCE,GPIO_AF_TIM5);
}

/**
  * @Data    2019-02-24 16:33
  * @brief   摩擦轮输出
  * @param   uint16_t prescaler, uint16_t period, uint16_t Pulse
  * @retval  void
  */
void TIM5_PWMOutput(uint16_t prescaler, uint16_t period, uint16_t Pulse)
{
    TIM5_GPIOInit();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    //配置定时器时钟分频
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
    //配置自动重装载寄存器的值
    TIM_TimeBaseStructure.TIM_Period = period;
    //配置死区时间与采样滤波分频，不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //配置计数模式，向上计数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef  TIM_OCInitStructure;
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
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);

    TIM_Cmd(TIM5, ENABLE);
}



