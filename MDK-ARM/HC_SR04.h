#ifndef _HC_SR04_H
#define _HC_SR04_H
#include "stdint.h"


extern uint8_t  TIM2CH1_CAPTURE_STA;
extern uint16_t	TIM2CH1_CAPTURE_VAL;
extern uint8_t  TIM2CH2_CAPTURE_STA;
extern uint16_t	TIM2CH2_CAPTURE_VAL;
extern uint8_t  TIM2CH3_CAPTURE_STA;
extern uint16_t	TIM2CH3_CAPTURE_VAL;


#define TRIG_H()	    TRIG_GPIO_Port->BSRR = TRIG_Pin //置高电平
#define TRIG_L()	    TRIG_GPIO_Port->BRR = TRIG_Pin  //置低电平

extern int32_t klick;
extern int32_t klick_up;
extern int32_t klick_up_cmd;
extern int32_t timeRecordcmd;



extern int32_t GetSR04Range_ECHO1(void);
extern int32_t GetSR04Range_ECHO2(void);
extern int32_t GetSR04Range_ECHO3(void);
#endif

