#ifndef __MOTORTT_H__
#define __MOTORTT_H__
#endif



#include "tim.h"
#include "PID.h"
#include "HC_SR04.h"

typedef enum
{
	Fow = 0,
	Bk = 1,
	Stop
}TTmode;

typedef enum
{
	Turn = 0,
	Back = 1
}SteeingEng;



void MotorTT_F(TTmode mode);
void MotorTT_L(TTmode mode);
void MotorTT_R(TTmode mode);
void MotorTT_B(TTmode mode);
void SteeingEngCtrl(SteeingEng cmd);
void MotorTT_Init(void);






