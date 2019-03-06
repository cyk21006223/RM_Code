#include "BSP_LED.h" 
#include "sys.h"


//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOB , ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
	
#if BOARDTYPE == 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;  
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOF,GPIO_Pin_14);//GPIOF9,F10设置高，灯灭
	GPIO_SetBits(GPIOE,GPIO_Pin_11);//GPIOF9,F10设置高，灯灭
	GPIO_SetBits(GPIOG,GPIO_Pin_1);
	GPIO_SetBits(GPIOG,GPIO_Pin_2);
	GPIO_SetBits(GPIOG,GPIO_Pin_3);
	GPIO_SetBits(GPIOG,GPIO_Pin_4);
	GPIO_SetBits(GPIOG,GPIO_Pin_5);
	GPIO_SetBits(GPIOG,GPIO_Pin_6);
	GPIO_SetBits(GPIOG,GPIO_Pin_7);
	GPIO_SetBits(GPIOG,GPIO_Pin_8);
	#else
		//PB4默认用作调试口，这里我们需要用于普通io，所以需要禁止jtag
//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

		LEDa = 1;
		LEDb = 1;
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;
		LED5 = 1;
		LED6 = 1;
		LED7 = 1;


#endif	
}



/**
	* @brief  设置信号灯
  * @param	灯号  状态：0 亮  1灭
  * @retval None
  */
void SetSignal(u8 num, u8 sta)
{
	switch (num)
	{
		case 0:
			LEDa = sta;
			break;
		case 1:
			LEDb = sta;
			break;
		case 2:
			LED1 = sta;
			break;
		case 3:
			LED2 = sta;
			break;
		case 4:
			LED3 = sta;
			break;
		case 5:
			LED4 = sta;
			break;
		case 6:
			LED5 = sta;
			break;
		case 7:
			LED6 = sta;
			break;		
		case 8:
			LED7 = sta;
			break;			
		case 9:
			LED8 = sta;
			break;		
		default:
			break;
	}

}


