/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "Task_Init.h"
#include "Task_CAN.h"
#include "Task_USART.h"
#include "Task_Control.h"
#include "Aiming_Control.h" 
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


extern void xPortSysTickHandler( void );
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{

}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
} 

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)
	{
		xPortSysTickHandler();
	}
}



		



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  USART1中断，遥控器收发中断
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
  /*储存判断是否有最高优先级的任务的状态位*/
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	  {
		/*关闭DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		  /*获取DMAbuff剩余大小，是否匹配*/
    if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
      {
        /*从队列里面发送数据*/
        xQueueSendFromISR(xUsart1RxQueue,&DR16_Buff,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
      }
		
		/*打开DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		/*清除空闲中断标志位*/
		(void)USART1->DR;
		(void)USART1->SR;
    }
}


/**
  * @brief  USART2自瞄发送接收终端
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
  /*储存判断是否有最高优先级的任务的状态位*/
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  if(USART_GetITStatus(USART2,USART_IT_IDLE) != RESET)
  {
    DMA_Cmd(USART2_RX_DMA_STREAM, DISABLE);
    /*加快中断速度，把判断都移动到任务里面去*/
    xQueueSendFromISR(xUsart2RxQueue,&CV_RXBUFF,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    DMA_SetCurrDataCounter(USART2_RX_DMA_STREAM,8);
		DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);

    /*清楚USART2的中断标志位*/
    (void)USART2->DR;
	  (void)USART2->SR;
  }
}


//uint16_t s_U3dataLength = 0;
void USART3_IRQHandler(void)
  {

  }


/**
* @name USART6云台陀螺仪中断
* @brief 陀螺仪中断
* @param None
* @retval       必要说明
*/
uint16_t s_U6dataLength = 0;
void USART6_IRQHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if(USART_GetITStatus(USART6,USART_IT_IDLE)!= RESET)
	{
		DMA_Cmd(USART6_RX_DMA_STREAM,DISABLE);
		uint16_t DMA_Counter = DMA_GetCurrDataCounter(USART6_RX_DMA_STREAM);
		s_U6dataLength = GY_IMU_BUFFSIZE - DMA_Counter;
		xQueueSendFromISR(xUsart6RxQueue,&Cloud_GY_IMU_RXBUFF, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
		DMA_SetCurrDataCounter(USART6_RX_DMA_STREAM,GY_IMU_BUFFSIZE);
		DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
		
		(void)USART6->DR;
	  (void)USART6->SR;
	}	
}


/**
  * @brief  CAN1 FIFO0 中断判断
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
	{
      CanRxMsg CAN1Feedback_Msg;	
	    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
      if(CAN_GetITStatus(CAN1,CAN_IT_FMP0))
      {
          CAN_Receive(CAN1,CAN_FIFO0,&CAN1Feedback_Msg);

          /*队列传输和是否存在最高优先级*/
          xQueueSendFromISR(xCan1RxQueue,&CAN1Feedback_Msg,&xHigherPriorityTaskWoken);
          portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
          CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
      }
	}


/**
  * @brief  TIM6 DAC 涓?鏂?鏈嶅姟鍑芥暟
  * @param  None
  * @retval None
  */
void TIM6_DAC_IRQHandler(void)//鍚勭?嶆ā寮忓?瑰簲鐨勯�熷害妯″瀷澶勭悊
{
	
}


/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
