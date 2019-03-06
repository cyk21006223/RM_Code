#include "BSP_BEEP.h"
#include "Config.h"

void BEEP_Init(u32 psc, u32 arr)
{ 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	
#if BOARDTYPE == 0	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOF9复用为定时器12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF14	
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB14
#else
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOH,GPIO_PinSource6,GPIO_AF_TIM12); //GPIOF9复用为定时器12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF14	
	GPIO_Init(GPIOH,&GPIO_InitStructure);              //初始化PB14

#endif
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//初始化定时器12
	
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
		//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM12, ENABLE);  //使能TIM14
 
	TIM12->CCR1 = 0;											

}










