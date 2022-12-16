#include "MotorTT.h"

////////////////������Ҫ�ŵ�ѭ����
// cnt ��ֵ���Ե���

//������Ҫдһ��PID����
fp32 PID_PWM_MOTORTT[3]	={1	,0.5,0.5}; 
PidTypeDef Pid_1PWM;
PidTypeDef Pid_2PWM;
PidTypeDef Pid_3PWM;
PidTypeDef Pid_4PWM;


//12.16:PID���ƴ����


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



////////////////����Ϊ�������

void SteeingEngCtrl(SteeingEng cmd)
{
	if(cmd == Turn){__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,250);} //2.5ms������	��90��
	if(cmd == Back){__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,150);}	//1.5ms������ 0��

}








