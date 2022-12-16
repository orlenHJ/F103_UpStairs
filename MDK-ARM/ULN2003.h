#ifndef __ULN2003_H_
#define __ULN2003_H_


typedef enum
{
	STOP_IT1	=	0	,	//停止
	BRAKE1		,	//刹车
	FORWARD1			,	//正转
	REVERSE1				//反转
}RotationSTATE_1;


typedef enum
{
	STOP_IT2	=	0	,	//停止
	BRAKE2			,	//刹车
	FORWARD2			,	//正转
	REVERSE2				//反转
}RotationSTATE_2;



//控制电机停止、刹车、正转、反转
//通过 RotationSTATE 枚举变量赋值
//注意这个函数是需要放到循环里面的，不断轮询运行
void uln2003_MotorRotation_1(RotationSTATE_1 rotationControl);
void uln2003_MotorRotation_2(RotationSTATE_2 rotationControl);

/*	使用示例 

	uln2003_MotorRotation(STOP_IT);	//停止

*/

#endif /*__ULN2003_H_*/

