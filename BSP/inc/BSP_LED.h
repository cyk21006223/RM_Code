#ifndef __LED_H
#define __LED_H

#include "sys.h"
#include "Config.h"

#if BOARDTYPE == 1
//LED端口定义
#define LEDa PFout(14)	// DS0
#define LEDb PEout(11)	// DS1	 
#define LED1 PGout(1)	// DS1	
#define LED2 PGout(2)	// DS1	
#define LED3 PGout(3)	// DS1	
#define LED4 PGout(4)	// DS1	
#define LED5 PGout(5)	// DS1	
#define LED6 PGout(6)	// DS1	
#define LED7 PGout(7)	// DS1	
#define LED8 PGout(8)	// DS1	

#else

#define LEDa PBout(4)	// DS0
#define LEDb PBout(5)	// DS1
#define LED1 PEout(9)
#define LED2 PEout(10)
#define LED3 PEout(11)
#define LED4 PEout(12)
#define LED5 PEout(13)
#define LED6 PEout(14)
#define LED7 PEout(15)
#define LED8 PEout(15)
#endif

void LED_Init(void);//初始化		
void SetSignal(u8 num, u8 sta);

#endif
