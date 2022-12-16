#include "ULN2003.h"
#include "gpio.h"




void Delay_us(uint16_t time)//Delay_us(0) = 10.2us
{
	HAL_SYSTICK_Config(72);
	HAL_Delay(time);
	HAL_SYSTICK_Config(72000);
}

//延时
#define ULN_delay	Delay_us
#define ULN_Delay_	1000   //这里可以改


//	port B   GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
// 	port B   GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3   port A GPIO_PIN_15
//IN0引脚


//GPIO输出电平，lv只能输入0或1，没有错误检测，使用小心
#define IN0_LEVEL1(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_12))	| (GPIO_PIN_12 * (lv)))
#define IN1_LEVEL1(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_13))	| (GPIO_PIN_13 * (lv)))
#define IN2_LEVEL1(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_14))	| (GPIO_PIN_14 * (lv)))
#define IN3_LEVEL1(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_15))	| (GPIO_PIN_15 * (lv)))

#define IN0_LEVEL2(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_5))	| (GPIO_PIN_5 * (lv)))
#define IN1_LEVEL2(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_4))	| (GPIO_PIN_4 * (lv)))
#define IN2_LEVEL2(lv)	GPIOB->ODR = ((GPIOB->ODR & (~GPIO_PIN_3))	| (GPIO_PIN_3 * (lv)))
#define IN3_LEVEL2(lv)	GPIOA->ODR = ((GPIOA->ODR & (~GPIO_PIN_15))	| (GPIO_PIN_15 * (lv)))



//电机状态控制
#define AHighLevel1	IN0_LEVEL1(1),IN1_LEVEL1(0),IN2_LEVEL1(0),IN3_LEVEL1(0)
#define BHighLevel1	IN0_LEVEL1(0),IN1_LEVEL1(1),IN2_LEVEL1(0),IN3_LEVEL1(0)
#define CHighLevel1	IN0_LEVEL1(0),IN1_LEVEL1(0),IN2_LEVEL1(1),IN3_LEVEL1(0)
#define DHighLevel1	IN0_LEVEL1(0),IN1_LEVEL1(0),IN2_LEVEL1(0),IN3_LEVEL1(1)

#define ABHighLevel1	IN0_LEVEL1(1),IN1_LEVEL1(1),IN2_LEVEL1(0),IN3_LEVEL1(0)
#define BCHighLevel1	IN0_LEVEL1(0),IN1_LEVEL1(1),IN2_LEVEL1(1),IN3_LEVEL1(0)
#define CDHighLevel1	IN0_LEVEL1(0),IN1_LEVEL1(0),IN2_LEVEL1(1),IN3_LEVEL1(1)
#define DAHighLevel1	IN0_LEVEL1(1),IN1_LEVEL1(0),IN2_LEVEL1(0),IN3_LEVEL1(1)



#define AHighLevel2	IN0_LEVEL2(1),IN1_LEVEL2(0),IN2_LEVEL2(0),IN3_LEVEL2(0)
#define BHighLevel2	IN0_LEVEL2(0),IN1_LEVEL2(1),IN2_LEVEL2(0),IN3_LEVEL2(0)
#define CHighLevel2	IN0_LEVEL2(0),IN1_LEVEL2(0),IN2_LEVEL2(1),IN3_LEVEL2(0)
#define DHighLevel2	IN0_LEVEL2(0),IN1_LEVEL2(0),IN2_LEVEL2(0),IN3_LEVEL2(1)

#define ABHighLevel2	IN0_LEVEL2(1),IN1_LEVEL2(1),IN2_LEVEL2(0),IN3_LEVEL2(0)
#define BCHighLevel2	IN0_LEVEL2(0),IN1_LEVEL2(1),IN2_LEVEL2(1),IN3_LEVEL2(0)
#define CDHighLevel2	IN0_LEVEL2(0),IN1_LEVEL2(0),IN2_LEVEL2(1),IN3_LEVEL2(1)
#define DAHighLevel2	IN0_LEVEL2(1),IN1_LEVEL2(0),IN2_LEVEL2(0),IN3_LEVEL2(1)





//电机控制
#define StopIt1		IN0_LEVEL1(0),IN1_LEVEL1(0),IN2_LEVEL1(0),IN3_LEVEL1(0)	//停止
#define Brake1		IN0_LEVEL1(1),IN1_LEVEL1(1),IN2_LEVEL1(1),IN3_LEVEL1(1)	//刹车

#define StopIt2		IN0_LEVEL2(0),IN1_LEVEL2(0),IN2_LEVEL2(0),IN3_LEVEL2(0)	//停止
#define Brake2		IN0_LEVEL2(1),IN1_LEVEL2(1),IN2_LEVEL2(1),IN3_LEVEL2(1)	//刹车


//半步驱动
#define Forward1		do{								\
						AHighLevel1;ULN_delay(ULN_Delay_);	\
						ABHighLevel1;ULN_delay(ULN_Delay_);	\
						BHighLevel1;ULN_delay(ULN_Delay_);	\
						BCHighLevel1;ULN_delay(ULN_Delay_);	\
						CHighLevel1;ULN_delay(ULN_Delay_);	\
						CDHighLevel1;ULN_delay(ULN_Delay_);	\
						DHighLevel1;ULN_delay(ULN_Delay_);	\
						DAHighLevel1;ULN_delay(ULN_Delay_);	\
						}while(0)

#define Reverse1		do{								\
						DHighLevel1;ULN_delay(ULN_Delay_);	\
						CDHighLevel1;ULN_delay(ULN_Delay_);	\
						CHighLevel1;ULN_delay(ULN_Delay_);	\
						BCHighLevel1;ULN_delay(ULN_Delay_);	\
						BHighLevel1;ULN_delay(ULN_Delay_);	\
						ABHighLevel1;ULN_delay(ULN_Delay_);	\
						AHighLevel1;ULN_delay(ULN_Delay_);	\
						DAHighLevel1;ULN_delay(ULN_Delay_);	\
						}while(0)

#define Forward2		do{								\
						AHighLevel2;ULN_delay(ULN_Delay_);	\
						ABHighLevel2;ULN_delay(ULN_Delay_);	\
						BHighLevel2;ULN_delay(ULN_Delay_);	\
						BCHighLevel2;ULN_delay(ULN_Delay_);	\
						CHighLevel2;ULN_delay(ULN_Delay_);	\
						CDHighLevel2;ULN_delay(ULN_Delay_);	\
						DHighLevel2;ULN_delay(ULN_Delay_);	\
						DAHighLevel2;ULN_delay(ULN_Delay_);	\
						}while(0)

#define Reverse2		do{								\
						DHighLevel2;ULN_delay(ULN_Delay_);	\
						CDHighLevel2;ULN_delay(ULN_Delay_);	\
						CHighLevel2;ULN_delay(ULN_Delay_);	\
						BCHighLevel2;ULN_delay(ULN_Delay_);	\
						BHighLevel2;ULN_delay(ULN_Delay_);	\
						ABHighLevel2;ULN_delay(ULN_Delay_);	\
						AHighLevel2;ULN_delay(ULN_Delay_);	\
						DAHighLevel2;ULN_delay(ULN_Delay_);	\
						}while(0)




//输出一次步进电机的运动
void uln2003_MotorRotation_1(RotationSTATE_1 rotationControl)
{
	switch(rotationControl)
	{
		case STOP_IT1:
			StopIt1;
			break;
		case BRAKE1:
			Brake1;
			break;
		case FORWARD1:
			Forward1;
			break;
		case REVERSE1:
			Reverse1;
			break;
		default:
			StopIt1;
			break;
	}
}


void uln2003_MotorRotation_2(RotationSTATE_2 rotationControl)
{
	switch(rotationControl)
	{
		case STOP_IT2:
			StopIt2;
			break;
		case BRAKE2:
			Brake2;
			break;
		case FORWARD2:
			Forward2;
			break;
		case REVERSE2:
			Reverse2;
			break;
		default:
			StopIt2;
			break;
	}
}


















