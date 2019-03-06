#include "BSP_SPI.h"

//这里针是对SPI1的初始化
void SPI1_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//使能SPI1时钟

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
	RCC_AHB1PeriphClockCmd(SPI1_MISO_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI1_MISO_Pin;//复用功能输出	
  GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI1_MISO_GPIO_PORT,SPI1_MISO_PINSOURCE,GPIO_AF_SPI1); //复用为 SPI1

	RCC_AHB1PeriphClockCmd(SPI1_MOSI_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_Pin;//复用功能输出	
  GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI1_MOSI_GPIO_PORT,SPI1_MOSI_PINSOURCE,GPIO_AF_SPI1); //复用为 SPI1
 
	RCC_AHB1PeriphClockCmd(SPI1_SCK_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI1_SCK_Pin;//复用功能输出	
  GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI1_SCK_GPIO_PORT,SPI1_SCK_PINSOURCE,GPIO_AF_SPI1); //复用为 SPI1
	
	//这里只针对SPI口初始化
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//复位SPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//停止复位SPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//定义波特率预分频的值:波特率预分频值为2
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设

	SPI_ReadWriteByte(SPI1, 0xff);//启动传输		 
}   

void SPI4_Init(void)
{	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);//使能SPI4时钟

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
	RCC_AHB1PeriphClockCmd(SPI4_MISO_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI4_MISO_Pin;//复用功能输出	
  GPIO_Init(SPI4_MISO_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI4_MISO_GPIO_PORT,SPI4_MISO_PINSOURCE,GPIO_AF_SPI4); //复用为 SPI4

	RCC_AHB1PeriphClockCmd(SPI4_MOSI_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI4_MOSI_Pin;//复用功能输出	
  GPIO_Init(SPI4_MOSI_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI4_MOSI_GPIO_PORT,SPI4_MOSI_PINSOURCE,GPIO_AF_SPI4); //复用为 SPI4
 
	RCC_AHB1PeriphClockCmd(SPI4_SCK_GPIO_CLK, ENABLE);//使能GPIO时钟 
  GPIO_InitStructure.GPIO_Pin = SPI4_SCK_Pin;//复用功能输出	
  GPIO_Init(SPI4_SCK_GPIO_PORT, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(SPI4_SCK_GPIO_PORT,SPI4_SCK_PINSOURCE,GPIO_AF_SPI4); //复用为 SPI4
	
	//这里只针对SPI口初始化
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4,ENABLE);//复位SPI4
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4,DISABLE);//停止复位SPI4

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//定义波特率预分频的值:波特率预分频值为2
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI4, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI4, ENABLE); //使能SPI外设

	SPI_ReadWriteByte(SPI1,0xff);//启动传输		 
}   



//SPI速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI_SetSpeed(SPI_TypeDef* SPIx, u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPIx->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPIx->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPIx,ENABLE); //使能SPI1
} 

//SPI 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI_ReadWriteByte(SPI_TypeDef* SPIx, u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
	SPI_I2S_SendData(SPIx, TxData); //通过外设SPIx发送一个byte  数据
		
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPIx); //返回通过SPIx最近接收的数据	
 		    
}





