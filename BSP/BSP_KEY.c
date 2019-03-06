/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_KEY.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
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
#include "BSP_KEY.h" 
    
/*-----------------------------------file of end------------------------------*/
/**
  * @Data    2019-02-21 11:35
  * @brief   DR16�����ж�ͨ���жϺ���
  * @param   uint16_t KeyStatus, Key_st *key
  * @retval  void
  */
void DR16_KeyState(uint16_t KeyStatus, Key_st *key)
{
	key->key_up_point = 0;
	key->key_dowm_point = 0;
	
	/*��ȡ��λ��ֵ*/
	key->key_Status = KeyStatus;

	
	if(key->key_Status != key->last_key_Status)
	{
		if(key->key_Status)//�а�����ֵ����Ϊ0��
		{
			key->key_up_point = key->key_Status;
		}
		else
		{
			key->key_dowm_point = key->last_key_Status;
			key->key_longpress_point = 0;
			key->pointing_time = 0;
		}
	}
	
	/*��������ֵ*/
	if(key->key_Status)
	{
		key->pointing_time++;
		if(key->pointing_time > 50)
		{
			key->key_longpress_point = key->key_Status;
			key->pointing_time = 0;
		}
	}
	
	key->last_key_Status = key->key_Status;
	
}
