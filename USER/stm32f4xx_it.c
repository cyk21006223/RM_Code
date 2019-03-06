/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
 

/** @addtogroup Template_Project
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
  * @brief  This function handles NMI exception.
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
void SVC_Handler(void)
{
}

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
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
 
}



/**
  * @brief  串口1接收dbus的18个字节中断
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
	{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA2_Stream2, DISABLE);
		
		//Rc_DataProcess(DBUS_DataBuf);
		
    //DMA_SetCurrDataCounter(DMA2_Stream2,Rc_BuffSIZE);
		//打开DMA
		DMA_Cmd(DMA2_Stream2, ENABLE);
		
		//清除空闲中断标志位
		(void)USART1->DR;
		(void)USART1->SR;
	}
}


/**
  * @brief  串口3接收dbus的18个字节中断
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
	{
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA1_Stream1, DISABLE);
		
		//Rc_DataProcess(DBUS_DataBuf);
		
    //DMA_SetCurrDataCounter(DMA1_Stream1,Rc_BuffSIZE);
		//打开DMA
		DMA_Cmd(DMA1_Stream1, ENABLE);
		
		//清除空闲中断标志位
		(void)USART3->DR;
		(void)USART3->SR;
	}
}
	
/**
  * @brief  串口1接收dbus的18个字节中断
  * @param  None
  * @retval None
  */
void USART6_IRQHandler(void)
	{
	if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA2_Stream1, DISABLE);
		
		//Rc_DataProcess(DBUS_DataBuf);
		
    //DMA_SetCurrDataCounter(DMA2_Stream1,Rc_BuffSIZE);
		//打开DMA
		DMA_Cmd(DMA2_Stream1, ENABLE);
		
		//清除空闲中断标志位
		(void)USART6->DR;
		(void)USART6->SR;
	}
}
	
/**
  * @brief  串口1接收dbus的18个字节中断
  * @param  None
  * @retval None
  */
void UART7_IRQHandler(void)
	{
	if(USART_GetITStatus(UART7, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA1_Stream3, DISABLE);
		
		//Rc_DataProcess(DBUS_DataBuf);
		
    //DMA_SetCurrDataCounter(DMA1_Stream3,Rc_BuffSIZE);
		//打开DMA
		DMA_Cmd(DMA1_Stream3, ENABLE);
		
		//清除空闲中断标志位
		(void)UART7->DR;
		(void)UART7->SR;
	}
}
	
/**
  * @brief  串口1接收dbus的18个字节中断
  * @param  None
  * @retval None
  */
void UART8_IRQHandler(void)
	{
	if(USART_GetITStatus(UART8, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA1_Stream6, DISABLE);
		
		//Rc_DataProcess(DBUS_DataBuf);
		
    //DMA_SetCurrDataCounter(DMA1_Stream6,Rc_BuffSIZE);
		//打开DMA
		DMA_Cmd(DMA1_Stream6, ENABLE);
		
		//清除空闲中断标志位
		(void)UART8->DR;
		(void)UART8->SR;
	}
}
	


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
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
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
