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
  |--FileName    : BSP_TIM.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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
  * @brief   Ħ���ֳ�ʼ��
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
  * @brief   Ħ�������
  * @param   uint16_t prescaler, uint16_t period, uint16_t Pulse
  * @retval  void
  */
void TIM5_PWMOutput(uint16_t prescaler, uint16_t period, uint16_t Pulse)
{
    TIM5_GPIOInit();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    //���ö�ʱ��ʱ�ӷ�Ƶ
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
    //�����Զ���װ�ؼĴ�����ֵ
    TIM_TimeBaseStructure.TIM_Period = period;
    //��������ʱ��������˲���Ƶ������Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //���ü���ģʽ�����ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //�������ģʽ��PWM1ģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    //ʹ�����
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //��ʹ�ܻ������
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    //���ó�ʼռ�ձ�
    TIM_OCInitStructure.TIM_Pulse = Pulse;
    //����PWM���ԣ���ʼ��ƽΪ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    //���ÿ���ʱ�����ƽ
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

    //���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    //���û����������ʱ�����ƽ(����ҲҪ���ã�����������ܳ���)
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;


    //��ʼ��Ϊ��Ӧͨ���������ͨ��1
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);

    TIM_Cmd(TIM5, ENABLE);
}



