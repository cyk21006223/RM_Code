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
  |--FileName    : Chassis_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
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

/*底盘数据储存结构体*/
Chassis_t Chassis;
/*-----------------------------------file of end------------------------------*/

/**
  * @Data    2019-02-25 18:59
  * @brief   底盘初始化
  * @param   void
  * @retval  void
  */

void Chassis_Init(void)
{
  /* =========================== FilterSetting of begin =========================== */
  /*底盘滤波函数初始化*/
  Chassis.Filter_LPFfactor = Fif_Factor;
  /* =========================== FilterSetting of end =========================== */
  
  
  /* =========================== RM3508 of begin =========================== */
  /*轮子初始化*/
  IncrementalPID_Init(&RM3508s[0].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[1].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[2].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  IncrementalPID_Init(&RM3508s[3].pid_wheel,2.5f, 1.5f, 0.0f, 8000, 1000);
  /* =========================== RM3508 of end =========================== */
  /* =========================== Fellow of begin =========================== */
  /*跟随初始化*/
  PositionPID_Init(&Chassis.Fowllow_Attitude_pid,3.1f, 0.0f, 13.5f, 4500, 500);
  /* =========================== Fellow of end =========================== */
   
   
}

/**
  * @Data    2019-02-27 19:40
  * @brief   底盘数据赋值处理
  * @param   uint8_t switchmode
  * @retval  void
  */
void Chassis_Judgement(uint8_t switchmode)
{
  float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;

  /*选择赋值模式*/
  switch(switchmode)
  {
    case PC_Controling:

    break;

    case RC_Controling:
      /*左遥感控制遥感遥控*/
      Chassis_Vx = (RCRocket.Left_x / 660 * Chassis_MaxSpeed_X);
      Chassis_Vy = (RCRocket.Left_y / 660 * Chassis_MaxSpeed_Y);
      
    break;

    case None_Controling:
    /*停止模式，直接赋值为0*/
      Chassis_Vx = 0;
      Chassis_Vy = 0;
      Chassis_VOmega = 0;
    break;

    default:
    break;
  }

  /*底盘数据处理*/
  Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,switchmode);
}


/**
  * @Data    2019-02-28 20:49
  * @brief   底盘处理函数
  * @param   float Vx,float Vy,float VOmega,uint8_t switchmode
  * @retval  void
  */
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode)
{
  /*四个轮子速度分解*/
  int16_t speed[4];

  /*自转速度缓存*/
  float tempVOmega = 0.0f;

  /*滤波处理*/
  Filter_IIRLPF(&Input_Vx,&Chassis.xLPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_Vy,&Chassis.yLPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_VOmega,&Chassis.zLPF,Chassis.Filter_LPFfactor);

  /*选择闭环方式*/
  switch(switchmode)
  {
    case PC_Controling:
    /*正常电脑判断模式*/
    

    break;

    case RC_Controling:

    /*正常遥控器控制模式（追随模式）*/
   Chassis.FollowYawRaw = 0.0f;
		if(abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 20 || \
    (abs(Input_Vy)+abs(Input_Vx) )> 5.0f)
		{
			/*相对于云台需要的跟随的角度*/
			Chassis.FollowYawRaw = PositionPID_Calculation(&Chassis.Fowllow_Attitude_pid, \
			Cloud_Yaw_Center, RM6623s[0].totalAngle);
		}
		Filter_IIRLPF(&Chassis.FollowYawRaw, &Chassis.FollowYawLPF, 0.1);
		tempVOmega = Chassis.zLPF + Chassis.FollowYawLPF;
		
    MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,speed);

    break;

    case None_Controling:
    /*多一个判断法防炸*/
    break;

    default:
    break;
  }

  /*麦轮解算*/
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

  /*机械电流设定*/
    Chassis_CurrentSetting(RM3508s[0].outCurrent, RM3508s[1].outCurrent, \
    RM3508s[2].outCurrent, RM3508s[3].outCurrent);

}


/**
  * @Data    2019-02-28 21:27
  * @brief   麦轮解算
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

    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//计算四个轮子速度的最大值
    {
        if(abs(tempSpeed[i]) > MaxSpeed)//abs()为绝对值函数
        {
            MaxSpeed = abs(tempSpeed[i]);
        }
    }

    /*速度分配*/
    /*有点类似限制速度的作用，把速度限制在3500*/
    if(MaxSpeed > 3500/*WheelMaxSpeed*/)//WheelMaxSpeed 单轮最大速度
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
  * @brief   功率限制
  * @param   RM3508_t *p_M3508s, float CurrentLimit
  * @retval  void
  */
void Chassis_powerLimit(RM3508_t *p_M3508s, float CurrentLimit)
{
  float Param = 1;
    float MaxCurrent = 0;

    //计算最大电流
    for(uint8_t i = 0; i < 4; i++)
    {
        if(abs(p_M3508s[i].outCurrent) > MaxCurrent)
        {
            MaxCurrent = abs(p_M3508s[i].outCurrent);
        }
    }

    //电流分配
    if(MaxCurrent > CurrentLimit)
    {
        Param = CurrentLimit / MaxCurrent;
    }

    p_M3508s[0].outCurrent *= Param;
    p_M3508s[1].outCurrent *= Param;
    p_M3508s[2].outCurrent *= Param;
    p_M3508s[3].outCurrent *= Param;
}
