#ifndef BSP_USART_H
#define BSP_USART_H

#include "stm32f4xx.h" 
#include "stdio.h"	


/****************************************  USART1_Pin_define  ****************************************/

#define USART1_RX_GPIO_PORT         	GPIOB
#define USART1_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART1_RX_Pin          	 	GPIO_Pin_6
#define USART1_RX_PINSOURCE			GPIO_PinSource7
#define USART1_RX_ENABLE				1

#define USART1_TX_GPIO_PORT         	GPIOB
#define USART1_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART1_TX_Pin          	 	GPIO_Pin_7
#define USART1_TX_PINSOURCE			GPIO_PinSource7
#define USART1_TX_ENABLE				1

/****************************************  USART1_Pin_define  ****************************************/


/****************************************  USART2_Pin_define  ****************************************/

#define USART2_RX_GPIO_PORT         	GPIOA
#define USART2_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART2_RX_Pin          	 	GPIO_Pin_8
#define USART2_RX_PINSOURCE			GPIO_PinSource8
#define USART2_RX_ENABLE				1

#define USART2_TX_GPIO_PORT         	GPIOA
#define USART2_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART2_TX_Pin          	 	GPIO_Pin_9
#define USART2_TX_PINSOURCE			GPIO_PinSource9
#define USART2_TX_ENABLE				1

/****************************************  USART2_Pin_define  ****************************************/


/****************************************  USART3_Pin_define  ****************************************/

#define USART3_RX_GPIO_PORT         	GPIOA
#define USART3_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART3_RX_Pin          	 	GPIO_Pin_8
#define USART3_RX_PINSOURCE			GPIO_PinSource8
#define USART3_RX_ENABLE				1

#define USART3_TX_GPIO_PORT         	GPIOA
#define USART3_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART3_TX_Pin          	 	GPIO_Pin_9
#define USART3_TX_PINSOURCE			GPIO_PinSource9
#define USART3_TX_ENABLE				1

/****************************************  USART3_Pin_define  ****************************************/



/****************************************  USART6_Pin_define  ****************************************/

#define USART6_RX_GPIO_PORT         	GPIOA
#define USART6_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART6_RX_Pin          	 	GPIO_Pin_8
#define USART6_RX_PINSOURCE			GPIO_PinSource8
#define USART6_RX_ENABLE				1

#define USART6_TX_GPIO_PORT         	GPIOA
#define USART6_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define USART6_TX_Pin          	 	GPIO_Pin_9
#define USART6_TX_PINSOURCE			GPIO_PinSource9
#define USART6_TX_ENABLE				1

/****************************************  USART6_Pin_define  ****************************************/


/****************************************  UART7_Pin_define  ****************************************/

#define UART7_RX_GPIO_PORT         	GPIOA
#define UART7_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define UART7_RX_Pin          	 	GPIO_Pin_8
#define UART7_RX_PINSOURCE			GPIO_PinSource8
#define UART7_RX_ENABLE				1

#define UART7_TX_GPIO_PORT         	GPIOA
#define UART7_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define UART7_TX_Pin          	 	GPIO_Pin_9
#define UART7_TX_PINSOURCE			GPIO_PinSource9
#define UART7_TX_ENABLE				1

/****************************************  UART7_Pin_define  ****************************************/


/****************************************  UART8_Pin_define  ****************************************/

#define UART8_RX_GPIO_PORT         	GPIOA
#define UART8_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define UART8_RX_Pin          	 	GPIO_Pin_8
#define UART8_RX_PINSOURCE			GPIO_PinSource8
#define UART8_RX_ENABLE				1

#define UART8_TX_GPIO_PORT         	GPIOA
#define UART8_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define UART8_TX_Pin          	 	GPIO_Pin_9
#define UART8_TX_PINSOURCE			GPIO_PinSource9
#define UART8_TX_ENABLE				1

/****************************************  UART8_Pin_define  ****************************************/






void USART2_Init(u32 bound);
void USART1_Init(u32 bound);
void USART3_Init(u32 bound);
void USART6_Init(u32 bound);
void UART7_Init(u32 bound);
void UART8_Init(u32 bound);
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
void USART3_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
void UART7_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
void UART8_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
void USART_sendChar(USART_TypeDef* USARTx, char ch);

#endif


