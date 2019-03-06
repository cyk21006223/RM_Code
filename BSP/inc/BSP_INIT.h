#ifndef _BSP_INIT_H
#define _BSP_INIT_H


#include "BSP_TIM.h"
#include "BSP_CAN.h"
#include "BSP_LASER.h"
#include "BSP_LED.h"
#include "BSP_TIM.h"
#include "BSP_USART.h"
#include "BSP_BEEP.h"


#define Rc_BuffSIZE   (18+2) //DBUS缓冲区长度
#define GYIMU_BuffSIZE   (18+2) //陀螺仪缓冲区长度
#define Judge_BuffSIZE 150u			//裁判系统缓冲区长度

extern u8 DBUS_DataBuf[Rc_BuffSIZE];
extern u8 GYIMU_RxBuff[GYIMU_BuffSIZE];
extern u8 Judge_DataBuff[Judge_BuffSIZE];

void BSP_Init(void);
void IMUBSP_Init(void);
void FrictBSP_init(void);
void Dr16BSP_Init(void);
void JudgeBSP_Init(void);
void ServoBSP_Init(void);

#endif



