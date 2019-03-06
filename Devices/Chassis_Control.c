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
  |--FileName    : Chassis_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
  |--Date        : 2019-02-25             
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
#include "Chassis_Control.h" 

/*�������ݴ���ṹ��*/
Chassis_t Chassis;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-25 18:59
  * @brief   ���̳�ʼ��
  * @param   void
  * @retval  void
  */

void Chassis_Init(void)
{
  /* =========================== FilterSetting of begin =========================== */
  /*�����˲�������ʼ��*/
  Chassis.Filter_LPFfactor = Fif_Factor;
  /* =========================== FilterSetting of end =========================== */
  
  
  /* =========================== RM3508 of begin =========================== */
  /*���ӳ�ʼ��*/
  IncrementalPID_Init(&RM3508s[0].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[1].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[2].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[3].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  /* =========================== RM3508 of end =========================== */
  /* =========================== Fellow of begin =========================== */
  /*�����ʼ��*/
  PositionPID_Init(&Chassis.Fowllow_Attitude_pid,3.1f, 0.0f, 13.5f, 4500, 500);
  /* =========================== Fellow of end =========================== */
   
   
}

/**
  * @Data    2019-02-27 19:40
  * @brief   �������ݸ�ֵ����
  * @param   uint8_t switchmode
  * @retval  void
  */
void Chassis_Judgement(uint8_t switchmode)
{
  float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;

  /*ѡ��ֵģʽ*/
  switch(switchmode)
  {
    case PC_Controling:

    break;

    case RC_Controling:
      /*��ң�п���ң��ң��*/
      Chassis_Vx = (RCRocket.Left_x / 660 * Chassis_MaxSpeed_X);
      Chassis_Vy = (RCRocket.Left_y / 660 * Chassis_MaxSpeed_Y);
      
    break;

    case None_Controling:
    /*ֹͣģʽ��ֱ�Ӹ�ֵΪ0*/
      Chassis_Vx = 0;
      Chassis_Vy = 0;
      Chassis_VOmega = 0;
    break;

    default:
    break;
  }

  /*�������ݴ���*/
  Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,switchmode);
}


/**
  * @Data    2019-02-28 20:49
  * @brief   ���̴�����
  * @param   float Vx,float Vy,float VOmega,uint8_t switchmode
  * @retval  void
  */
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode)
{
  /*�ĸ������ٶȷֽ�*/
  int16_t speed[4];

  /*��ת�ٶȻ���*/
  float tempVOmega = 0.0f;

  /*�˲�����*/
  Filter_IIRLPF(&Input_Vx,&Chassis.xLPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_Vy,&Chassis.yLPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_VOmega,&Chassis.zLPF,Chassis.Filter_LPFfactor);

  /*ѡ��ջ���ʽ*/
  switch(switchmode)
  {
    case PC_Controling:
    /*���������ж�ģʽ*/
    

    break;

    case RC_Controling:

    /*����ң��������ģʽ��׷��ģʽ��*/
   Chassis.FollowYawRaw = 0.0f;
		if(abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 20 || \
    (abs(Input_Vy)+abs(Input_Vx) )> 5.0f)
		{
			/*�������̨��Ҫ�ĸ���ĽǶ�*/
			Chassis.FollowYawRaw = PositionPID_Calculation(&Chassis.Fowllow_Attitude_pid, \
			Cloud_Yaw_Center, RM6623s[0].totalAngle);
		}
		Filter_IIRLPF(&Chassis.FollowYawRaw, &Chassis.FollowYawLPF, 0.1);
		tempVOmega = Chassis.zLPF + Chassis.FollowYawLPF;
		
    MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,speed);

    break;

    case None_Controling:
    /*��һ���жϷ���ը*/
    break;

    default:
    break;
  }

  /*���ֽ���*/
  for(int i = 0; i<4; i++)
  {
    if(RM3508s[i].UpdateFlag == 1)
    {
        RM3508s[i].targetSpeed = speed[i];

        RM3508s[i].outCurrent = IncrementalPID_Calculation(&RM3508s[i].pid_wheel, \
        RM3508s[i].targetSpeed, RM3508s[i].realSpeed);


        RM3508s[i].UpdateFlag = 0;
    }
  }

  /*��е�����趨*/
    Chassis_CurrentSetting(RM3508s[0].outCurrent, RM3508s[1].outCurrent, \
    RM3508s[2].outCurrent, RM3508s[3].outCurrent);

}


/**
  * @Data    2019-02-28 21:27
  * @brief   ���ֽ���
  * @param   float Vx, float Vy, float VOmega, int16_t *Speed
  * @retval  void
  */
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed)
{
		float tempSpeed[4];
    float Param = 1;
    float MaxSpeed = 0;

    VAL_LIMIT(Vx, -Chassis_MaxSpeed_X, Chassis_MaxSpeed_X);
    VAL_LIMIT(Vy, -Chassis_MaxSpeed_Y, Chassis_MaxSpeed_Y);
    VAL_LIMIT(VOmega, -Chassis_MaxSpeed_W, Chassis_MaxSpeed_W);

    tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = Vx + Vy + VOmega;
    tempSpeed[2] = -Vx + Vy + VOmega;
    tempSpeed[3] = -Vx - Vy + VOmega;

    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//�����ĸ������ٶȵ����ֵ
    {
        if(abs(tempSpeed[i]) > MaxSpeed)//abs()Ϊ����ֵ����
        {
            MaxSpeed = abs(tempSpeed[i]);
        }
    }

    /*�ٶȷ���*/
    /*�е����������ٶȵ����ã����ٶ�������3500*/
    if(MaxSpeed > 3500/*WheelMaxSpeed*/)//WheelMaxSpeed ��������ٶ�
    {
        Param = (float)3500 / MaxSpeed;
    }

    Speed[0] = tempSpeed[0] * Param;
    Speed[1] = tempSpeed[1] * Param;
    Speed[2] = tempSpeed[2] * Param;
    Speed[3] = tempSpeed[3] * Param;
}

/**
  * @Data    2019-02-28 21:28
  * @brief   ��������
  * @param   RM3508_t *p_M3508s, float CurrentLimit
  * @retval  void
  */
void Chassis_powerLimit(RM3508_t *p_M3508s, float CurrentLimit)
{
  float Param = 1;
    float MaxCurrent = 0;

    //����������
    for(uint8_t i = 0; i < 4; i++)
    {
        if(abs(p_M3508s[i].outCurrent) > MaxCurrent)
        {
            MaxCurrent = abs(p_M3508s[i].outCurrent);
        }
    }

    //��������
    if(MaxCurrent > CurrentLimit)
    {
        Param = CurrentLimit / MaxCurrent;
    }

    p_M3508s[0].outCurrent *= Param;
    p_M3508s[1].outCurrent *= Param;
    p_M3508s[2].outCurrent *= Param;
    p_M3508s[3].outCurrent *= Param;
}
