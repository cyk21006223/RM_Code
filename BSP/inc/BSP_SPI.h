#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "stm32f4xx.h"

/****************************************  SPI1_Pin_define  ****************************************/

#define SPI1_MISO_GPIO_PORT         	GPIOA
#define SPI1_MISO_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI1_MISO_Pin          	 	GPIO_Pin_8
#define SPI1_MISO_PINSOURCE			GPIO_PinSource8

#define SPI1_MOSI_GPIO_PORT         	GPIOA
#define SPI1_MOSI_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI1_MOSI_Pin          	 	GPIO_Pin_9
#define SPI1_MOSI_PINSOURCE			GPIO_PinSource9

#define SPI1_SCK_GPIO_PORT         	GPIOA
#define SPI1_SCK_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI1_SCK_Pin          	 	GPIO_Pin_9
#define SPI1_SCK_PINSOURCE			GPIO_PinSource9

/****************************************  SPI1_Pin_define  ****************************************/

/****************************************  SPI4_Pin_define  ****************************************/

#define SPI4_MISO_GPIO_PORT         	GPIOA
#define SPI4_MISO_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI4_MISO_Pin          	 	GPIO_Pin_8
#define SPI4_MISO_PINSOURCE			GPIO_PinSource8

#define SPI4_MOSI_GPIO_PORT         	GPIOA
#define SPI4_MOSI_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI4_MOSI_Pin          	 	GPIO_Pin_9
#define SPI4_MOSI_PINSOURCE			GPIO_PinSource9

#define SPI4_SCK_GPIO_PORT         	GPIOA
#define SPI4_SCK_GPIO_CLK          	RCC_AHB1Periph_GPIOA
#define SPI4_SCK_Pin          	 	GPIO_Pin_9
#define SPI4_SCK_PINSOURCE			GPIO_PinSource9

/****************************************  SPI4_Pin_define  ****************************************/






void SPI_SetSpeed(SPI_TypeDef* SPIx, u8 SPI_BaudRatePrescaler);
u8 SPI_ReadWriteByte(SPI_TypeDef* SPIx, u8 TxData);



#endif
