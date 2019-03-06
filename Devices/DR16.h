/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : DR16.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无                                                       
  |--Date        : 2019-02-21               
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
#ifndef __DR16_H 
#define __DR16_H 

/*允许使用匿名共用体*/
#pragma anon_unions

#include "Chassis_Control.h"
#include "Cloud_Control.h"

#include "BSP_USART.h"
#include "BSP_KEY.h"
#include "stdbool.h"

/*using the PI of BSP and the form of arm_math...*/
#include "BSP_MATH.h"
#include "arm_math.h"

/*遥控器结构体*/
typedef struct
{
		/*遥控器变量*/
    struct 
		{
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;
        int16_t ch5_wheel;
        uint8_t s_left;
        uint8_t s_right;
    } rc;
		
		/*电脑变量*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*键盘变量*/
    union
    {
        uint16_t key_code;
        struct 
				{
					
					 
			
            bool press_W:1;
            bool press_S:1;
            bool press_A:1;
            bool press_D:1;
			      bool press_Shift:1;
            bool press_Ctrl:1;
            bool press_Q:1;
            bool press_E:1;
   
			
            bool press_R:1;
            bool press_F:1;
            bool press_G:1;
            bool press_Z:1;
            bool press_X:1;
            bool press_C:1;
            bool press_V:1;
            bool press_B:1;
           
        };
    } keyBoard;
		
	/*帧率控制（判断是否离线）*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_t;

/*遥控器摇杆模型*/
typedef struct 
{   
    float Left_x;
    float Left_y;
    float Left_radian;
    float Left_degrees;
    float Left_distance;

    float Right_x;
    float Right_y;
    float Right_radian;
    float Right_degrees;
    float Right_distance;

    float FlatWheel;
}RCRocket_t;

/*电脑按键模型*/
typedef struct 
{
    float PC_x;
    float PC_y;
    float PC_radian;
    float PC_degrees;
    float PC_distance;
    
}PCRocket_t;

/*遥控器右面遥感状态*/
typedef enum
{
 PC_Controling = 1,
 RC_Controling = 3,
 None_Controling = 2,
}RightMode_e;

/*遥控器左边摇杆状态*/
typedef enum
{
 Left_switchup = 1,
 Left_switchmiddle = 3,
 Left_switchdown = 2,
}LeftMode_e;

/*PC电脑控制状态*/
typedef enum
{
  PC_NoneHead = 1,
  PC_CloudPlatfrom = 2,
  PC_Sevrel = 3,
  
}PCControl_Mode;

/* =========================== DR16_Struct of begin =========================== */
/*DR16储存体*/
extern uint8_t DR16_Buff[18u+2];

/*DR16遥控器储存体*/
extern DR16_t DR16;

/*遥控器赋值*/
extern RCRocket_t RCRocket;

/*按键通用结构体*/
extern Key_st keyBorad;
extern Key_st MouseKeyLeft;
extern Key_st MouseKeyRight;
/* =========================== DR16_Struct of end =========================== */



/*DR16遥控器初始化*/
void DR16_Init(void);

/*DR16遥控器解码*/
void DR16_Process(uint8_t *pData);

/*DR16数据滤抖处理*/
int Data_Suppers(int16_t data);

/*摇杆模型赋值*/
void Rocket_transport(float POSLeft_x, float POSLeft_y,float POSRight_x,\
float POSRight_y,float Flatwheel,RCRocket_t *rocket);

#endif	// __DR16_H
/*-----------------------------------file of end------------------------------*/


