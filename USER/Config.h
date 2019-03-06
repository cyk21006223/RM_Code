#ifndef _CONFIG_H
#define _CONFIG_H

#define BOARDTYPE 0										// 1 旧板子					0 彬哥的板子

#define MODE 0

#define CLOUD_YAW_LIMIT_SWITCH	  1		// 1 云台yaw限位  						0 不限位
#define CLOUD_PITCH_LIMIT_SWITCH 	1		// 1 云台pitch限位 					  0 不限位
#define CLOUD_YAW_ZERO_PLACE			0		// 1 YAW零点在限位区间内      0 不在区间内
#define CLOUD_PITCH_ZERO_PLACE 		0		// 1 PITCH零点在限位区间内    0 不在区间内



/************************************** BSP ****************************************************/

#define FRICT_BSP_CONFIG 			8		// 0 关闭				i	定时器i 
#define LIDSERVO_BSP_CONFIG   5		// 0 关闭				i	定时器i 

#define IMUGY955_BSP_CONFIG		8		// 0 关闭				i	串口i 
#define DR16_BSP_CONFIG 			1		// 0 关闭				i	串口i 
#define JUDGE_BSP_CONFIG  		7		// 0 关闭				i	串口i 


#define MPU6050_SWITCH 1   		//0关闭 	1打开




#endif


