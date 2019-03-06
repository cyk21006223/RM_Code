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
  |--FileName    : Task_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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
/*֡��ˢ�¿��ƾ��*/
static TaskHandle_t Device_FlashHandler = NULL;

/*֡��ˢ�¿��ƺ���*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== LED_FLASHING of begin =========================== */
 /*��ˮ�ƿ��ƾ��*/ 
static TaskHandle_t LED_LightHandler = NULL;

/*��ˮ��ˢ�¿��ƺ���*/
void LED_LightTask(void *pvParameters);
/* =========================== LED_FLASHING of end =========================== */

/* =========================== Chassis of begin =========================== */
/*���̿���������*/  
static TaskHandle_t Chassical_Handler = NULL;

/*����������ƺ���*/
void Chassical_Task(void *pvParameters);
/* =========================== Chassis of end =========================== */

/* =========================== Cloud of begin =========================== */
/*��̨����������*/
static TaskHandle_t Cloud_Handler = NULL;  

/*��̨������ƺ���*/
void Cloud_Task(void *pvParameters);
/* =========================== Cloud of end =========================== */




/**
  * @Data    2019-02-20 19:46
  * @brief   �������񴴽�
  * @param   void
  * @retval  void
  */
void Control_TaskCreate(void)
{
    xTaskCreate(Devices_Task,           /* ������  */        
				        "Devices_Task",         /* ������    */      
				        128,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        2,       			        /* �������ȼ�*/
				        &Device_FlashHandler);   /* ������  */

    xTaskCreate(LED_LightTask,           /* ������  */        
								"LED_LightTask",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&LED_LightHandler);   /* ������  */

    xTaskCreate(Chassical_Task,           /* ������  */        
								"Chassical_Task",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&Chassical_Handler);   /* ������  */

    xTaskCreate(Cloud_Task,           /* ������  */        
								"Cloud_Task",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&Cloud_Handler);   /* ������  */

    
}

/**
  * @Data    2019-02-20 19:49
  * @brief   ֡��ˢ������
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
    /*����ʱ��Ƭ�������*/
    portTickType CurrentControlTick = 0;
	while(1)
	{
    /*�豸ˢ���ж�*/
		DeviceFlash();
		vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
	}
}


/**
  * @Data    2019-03-01 17:04
  * @brief   ��ˮ��ˢ�¿��ƺ���
  * @param   void *pvParameters
  * @retval  void
  */
void LED_LightTask(void *pvParameters)
{
  /*����ʱ��Ƭ�������*/
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
  * @brief   ����������ƺ���
  * @param   void *pvParameters
  * @retval  void
  */
void Chassical_Task(void *pvParameters)
{
  /*����ʱ��Ƭ�������*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
    /*���̴����ж�*/
    Chassis_Judgement(Chassis.RCmodeswitch);
    GPIO_ToggleBits(GPIOE,GPIO_Pin_13);
    vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
  }
}

/**
  * @Data    2019-03-06 20:27
  * @brief   ��̨������ƺ���
  * @param   void *pvParameters
  * @retval  void
  */
void Cloud_Task(void *pvParameters)
{
  /*����ʱ��Ƭ�������*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
		Cloud_Judgement(Chassis.RCmodeswitch);
    GPIO_ToggleBits(GPIOE,GPIO_Pin_14);
    vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
  }
}
