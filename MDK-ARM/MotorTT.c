#include "MotorTT.h"

////////////////马达控制要放到循环里
// cnt 的值可以调控

//这里再要写一个PID控制
fp32 PID_PWM_MOTORTT[3]	={1	,0.5,0.5}; 
PidTypeDef Pid_1PWM;
PidTypeDef Pid_2PWM;
PidTypeDef Pid_3PWM;
PidTypeDef Pid_4PWM;


//12.16:PID控制待完成


void MotorTT_F(TTmode mode)
{
	uint16_t cnt;
	if(mode == Fow){	__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_1,cnt);	}
	if(mode == Bk){	__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_2,cnt);	}
	if(mode == Stop){	
		__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_1,1000);
		__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_2,1000);
	}

}

void MotorTT_L(TTmode mode)
{
	uint16_t cnt = 300;
	if(mode == Fow){	__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_1,cnt);	}
	if(mode == Bk){	__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_2,cnt);	}
	if(mode == Stop){	
		__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_1,1000);
		__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_2,1000);
	}
}

void MotorTT_R(TTmode mode)
{
	
	uint16_t cnt = 300;
	if(mode == Fow){	__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_3,cnt);	}
	if(mode == Bk){	__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_4,cnt);	}
	if(mode == Stop){	
		__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_3,1000);
		__HAL_TIM_SetCompare (&htim4,TIM_CHANNEL_4,1000);
	}

}

void MotorTT_B(TTmode mode)
{
	uint16_t cnt = 300;
	if(mode == Fow){	__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_3,cnt);	}
	if(mode == Bk){	__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_4,cnt);	}
	if(mode == Stop){	
		__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_3,1000);
		__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_4,1000);
	}

}



////////////////下面为舵机控制

void SteeingEngCtrl(SteeingEng cmd)
{
	if(cmd == Turn){__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,250);} //2.5ms高脉冲	正90度
	if(cmd == Back){__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,150);}	//1.5ms高脉冲 0度

}








