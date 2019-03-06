/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Device_Flash.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-20             
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
#include "Device_Flash.h" 
    
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-20 19:54
  * @brief   帧率刷新
  * @param   void
  * @retval  void
  */
void DeviceFlash(void)
{
    /* =========================== RM3508 of begin =========================== */
    for(int i =0;i<4;i++)
	{
		if(RM3508s[i].UpdateFrame < 5)
		{
			RM3508s[i].OFFLINE_SET = 1;
		}
		else
		{
			RM3508s[i].OFFLINE_SET = 0;
		}
		RM3508s[i].UpdateFrame = 0;
	}    
    /* =========================== RM3508 of end =========================== */
    
	/* =========================== RM6623 of begin =========================== */
    for(int j = 0;j<2;j++)
	{
		if(RM6623s[j].UpdateFrame < 5)
		{
			RM6623s[j].OFFLINE_SET = 1;
		}
		else
		{
			RM6623s[j].OFFLINE_SET = 0;
		}
		RM6623s[j].UpdateFrame = 0;
	}
    /* =========================== RM6623 of end =========================== */
    
    /* =========================== RM2006 of begin =========================== */
    for(int k = 0;k < 1;k++)
	{
		if(RM2006s[k].UpdateFrame < 5)
		{
			RM2006s[k].OFFLINE_SET = 1;
		}
		else
		{
			RM2006s[k].OFFLINE_SET = 0;
		}
		RM2006s[k].UpdateFrame =0;
	}
    /* =========================== RM2006 of end =========================== */
    
    /* =========================== DR16 of begin =========================== */
    if(DR16.UpdateFrame < 5)
	{
		DR16.OFFLINE_SET = 1;
	}
	else
	{
		DR16.OFFLINE_SET = 0;
	}
	DR16.UpdateFrame = 0;
    /* =========================== DR16 of end =========================== */
    
    /* =========================== IMU of begin =========================== */
    /*陀螺仪*/
	if(Cloud_IMU.UpdateFrame < 5)
	{
		Cloud_IMU.OFFLINE_SET = 1;
	}
	else
	{
		Cloud_IMU.OFFLINE_SET = 0;
	}
	Cloud_IMU.UpdateFrame = 0;
    /* =========================== IMU of end =========================== */

}
