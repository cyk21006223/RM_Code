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
  |--FileName    : Task_Control.c                                              
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
#include "Task_Control.h" 
    
/*-----------------------------------file of end------------------------------*/

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
static TaskHandle_t Device_FlashHandler = NULL;

/*帧率刷新控制函数*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== LED_FLASHING of begin =========================== */
 /*流水灯控制句柄*/ 
static TaskHandle_t LED_LightHandler = NULL;

/*流水灯刷新控制函数*/
void LED_LightTask(void *pvParameters);
/* =========================== LED_FLASHING of end =========================== */

/* =========================== Chassis of begin =========================== */
/*底盘控制任务句柄*/  
static TaskHandle_t Chassical_Handler = NULL;

/*底盘任务控制函数*/
void Chassical_Task(void *pvParameters);
/* =========================== Chassis of end =========================== */

/* =========================== Cloud of begin =========================== */
/*云台控制任务句柄*/
static TaskHandle_t Cloud_Handler = NULL;  

/*云台任务控制函数*/
void Cloud_Task(void *pvParameters);
/* =========================== Cloud of end =========================== */




/**
  * @Data    2019-02-20 19:46
  * @brief   控制任务创建
  * @param   void
  * @retval  void
  */
void Control_TaskCreate(void)
{
    xTaskCreate(Devices_Task,           /* 任务函数  */        
				        "Devices_Task",         /* 任务名    */      
				        128,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        2,       			        /* 任务优先级*/
				        &Device_FlashHandler);   /* 任务句柄  */

    xTaskCreate(LED_LightTask,           /* 任务函数  */        
								"LED_LightTask",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&LED_LightHandler);   /* 任务句柄  */

    xTaskCreate(Chassical_Task,           /* 任务函数  */        
								"Chassical_Task",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&Chassical_Handler);   /* 任务句柄  */

    xTaskCreate(Cloud_Task,           /* 任务函数  */        
								"Cloud_Task",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&Cloud_Handler);   /* 任务句柄  */

    
}

/**
  * @Data    2019-02-20 19:49
  * @brief   帧率刷新任务
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
    /*创建时间片计算变量*/
    portTickType CurrentControlTick = 0;
	while(1)
	{
    /*设备刷新中断*/
		DeviceFlash();
		vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
	}
}


/**
  * @Data    2019-03-01 17:04
  * @brief   流水灯刷新控制函数
  * @param   void *pvParameters
  * @retval  void
  */
void LED_LightTask(void *pvParameters)
{
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
    GPIO_ResetBits(GPIOE,GPIO_Pin_9);
		vTaskDelayUntil(&CurrentControlTick,5 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
		vTaskDelayUntil(&CurrentControlTick,15 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_12);
		vTaskDelayUntil(&CurrentControlTick,20 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		vTaskDelayUntil(&CurrentControlTick,25 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		vTaskDelayUntil(&CurrentControlTick,30 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
    vTaskDelayUntil(&CurrentControlTick,35 / portTICK_RATE_MS);

    GPIO_SetBits(GPIOE,GPIO_Pin_9);
		vTaskDelayUntil(&CurrentControlTick,5 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_10);
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
		vTaskDelayUntil(&CurrentControlTick,15 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		vTaskDelayUntil(&CurrentControlTick,20 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_13);
		vTaskDelayUntil(&CurrentControlTick,25 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_14);
		vTaskDelayUntil(&CurrentControlTick,30 / portTICK_RATE_MS);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
    vTaskDelayUntil(&CurrentControlTick,35 / portTICK_RATE_MS);

    vTaskDelayUntil(&CurrentControlTick,1100 / portTICK_RATE_MS);
  }
}

/**
  * @Data    2019-03-01 17:05
  * @brief   底盘任务控制函数
  * @param   void *pvParameters
  * @retval  void
  */
void Chassical_Task(void *pvParameters)
{
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
    /*底盘处理中断*/
    Chassis_Judgement(Chassis.RCmodeswitch);
    GPIO_ToggleBits(GPIOE,GPIO_Pin_13);
    vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
  }
}

/**
  * @Data    2019-03-06 20:27
  * @brief   云台任务控制函数
  * @param   void *pvParameters
  * @retval  void
  */
void Cloud_Task(void *pvParameters)
{
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
		Cloud_Judgement(Chassis.RCmodeswitch);
    GPIO_ToggleBits(GPIOE,GPIO_Pin_14);
    vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
  }
}
