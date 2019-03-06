#ifndef _BSP_BEEP_H
#define _BSP_BEEP_H


#include "stm32f4xx.h"



void BEEP_Init(u32 psc, u32 arr);
void SetCompareValue(uint16_t value);
void SetBeepSignal(uint8_t mode);


#endif 

