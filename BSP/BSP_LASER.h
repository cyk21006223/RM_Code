/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_LASER.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
  |--Date        : 2019-02-20               
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
#ifndef __BSP_LASER_H 
#define __BSP_LASER_H 

#include "stm32f4xx.h"

#define LASER_GPIO_CLK              RCC_AHB1Periph_GPIOG
#define LASER_PIN                   GPIO_Pin_13
#define LASER_GPIO_PORT           	GPIOG

#define LASER_ON()			GPIO_SetBits(LASER_GPIO_PORT, LASER_PIN)
#define LASER_OFF()			GPIO_ResetBits(LASER_GPIO_PORT, LASER_PIN)
#define LASER(isOn) 		GPIO_WriteBit(LASER_GPIO_PORT,LASER_PIN, (BitAction)isOn)
#define LASER_TOGGLE() 		GPIO_ToggleBits(LASER_GPIO_PORT, LASER_PIN)

/*激光初始化*/
void LASER_Init(void);

#endif	// __BSP_LASER_H
/*-----------------------------------file of end------------------------------*/


