#include "BSP_LASER.h"

#include "Config.h"

/**
  * @brief  激光初始化
  * @param  None
  * @retval None
  */
void Laser_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//浮空
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz

#if BOARDTYPE == 1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOG,&GPIO_InitStructure);//初始化io
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//浮空
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOH,&GPIO_InitStructure);//初始化io
	
	GPIO_SetBits(GPIOH, GPIO_Pin_2);
	GPIO_SetBits(GPIOH, GPIO_Pin_3);
	GPIO_SetBits(GPIOH, GPIO_Pin_4);
	GPIO_SetBits(GPIOH, GPIO_Pin_5);
#else
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA ,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化io
#endif

}





