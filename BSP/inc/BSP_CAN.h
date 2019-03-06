#ifndef _CAN_H
#define _CAN_H

#include "stm32f4xx.h" 

/****************************************  CAN1_Pin_define  ****************************************/
#define CAN1_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_RX_GPIO_PORT           GPIOD
#define CAN1_RX_Pin           		GPIO_Pin_0
#define CAN1_RX_PINSOURCE			GPIO_PinSource0

#define CAN1_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_TX_GPIO_PORT           GPIOD
#define CAN1_TX_Pin          	 	GPIO_Pin_1
#define CAN1_TX_PINSOURCE			GPIO_PinSource1

#define CAN1_SJW		CAN_SJW_1tq
#define CAN1_BS1		CAN_BS1_3tq
#define CAN1_BS2		CAN_BS2_5tq
#define CAN1_Prescaler	5
/****************************************  CAN1_Pin_define  ****************************************/


/****************************************  CAN2_Pin_define  ****************************************/
#define CAN2_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_RX_GPIO_PORT           GPIOB
#define CAN2_RX_Pin           		GPIO_Pin_12
#define CAN2_RX_PINSOURCE			GPIO_PinSource12

#define CAN2_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_TX_GPIO_PORT           GPIOB
#define CAN2_TX_Pin          	 	GPIO_Pin_13
#define CAN2_TX_PINSOURCE			GPIO_PinSource13

#define CAN2_SJW		CAN_SJW_1tq
#define CAN2_BS1		CAN_BS1_3tq
#define CAN2_BS2		CAN_BS2_5tq
#define CAN2_Prescaler	5
/****************************************  CAN2_Pin_define  ****************************************/

void CAN1_Init(void);
void CAN2_Init(void);

#endif


