#include "mode_GO.h"
int32_t dist1 = 0;
int32_t dist2 = 0;
int32_t dist3 = 0;
uint32_t Stairlenth;

//均为整数
//		dist1 = GetSR04Range_ECHO1();   //前方
//		dist2 = GetSR04Range_ECHO2();		//左方
//		dist3 = GetSR04Range_ECHO3();		//右方

int32_t CalcuDist(int32_t dist)//保证静止时的稳定
{
	int32_t old_dist1,old_dist2,old_dist3;
	int32_t Err;
	int32_t OutDist = 0;
	old_dist3 = old_dist2;
	old_dist2 = old_dist1;
	old_dist1 = dist;
	Err = (abs(old_dist3 - old_dist2) + abs(old_dist2 - old_dist1) + abs(old_dist1 - dist)) / 3;
	if(0 <= Err && Err < 3)   
	{
		OutDist = (dist + old_dist1 + old_dist2) / 3;
	}else{OutDist = dist; }
	return OutDist;
	
}

/////////////////////放到While里执行

int32_t UpStairs_DDD2UUD(void)
{
	/*
			装置三部分一开始为 DDD   ， 程序结束过后为  UUD即前两部分抬起
	*/
	
	uint8_t flag = 0; //步骤
	int32_t tempDist = 0; //该模式下，装置前方默认已经贴紧台阶

	//保证此时舵机归位
	if(flag == 0)
	{
		SteeingEngCtrl(Back);
		HAL_Delay (1000);
		flag++;
	}	
	if(flag == 1)
	{
		uln2003_MotorRotation_2(FORWARD2);  //前方步进电机上升
		klick_up_cmd = 1; //开启爬升计时
		dist1 = GetSR04Range_ECHO1();
		tempDist = CalcuDist(dist1);
		if(tempDist > 25) //爬到另一台阶时
		{	
			Stairlenth = tempDist;
			timeRecordcmd = 1; //klick开始计时
		} 
		else{
			timeRecordcmd = 0;
		}
		if(klick >= 15)
		{
			uln2003_MotorRotation_2(BRAKE2); 
			uln2003_MotorRotation_2(STOP_IT2); 
			klick_up_cmd = 0 ;
			timeRecordcmd = 0;
			flag++;
			klick = 0;
		}	
	}	
	
	//均为向前移
	if(flag == 2)
	{
		MotorTT_F(Fow);
		MotorTT_L(Fow);
		MotorTT_R(Fow);
		MotorTT_B(Fow);
		dist1 = GetSR04Range_ECHO1();
		tempDist = CalcuDist(dist1);
		if(tempDist < (Stairlenth - 8))
		{
			MotorTT_F(Stop);
			MotorTT_L(Stop);
			MotorTT_R(Stop);
			MotorTT_B(Stop);
			flag++;
		}
	}
	if(flag == 3) //抬升中部
	{
		uln2003_MotorRotation_2(REVERSE2);
		uln2003_MotorRotation_1(REVERSE1);
		timeRecordcmd = 1;
		if(klick >= klick_up)
		{
			uln2003_MotorRotation_2(BRAKE2); 
			uln2003_MotorRotation_2(STOP_IT2); 
			uln2003_MotorRotation_1(BRAKE1); 
			uln2003_MotorRotation_1(STOP_IT1); 
			timeRecordcmd = 0;
			flag++;
		}
	
	}
	//均为向前移
	if(flag == 4)
	{
		MotorTT_F(Fow);
		MotorTT_L(Fow);
		MotorTT_R(Fow);
		MotorTT_B(Fow);
		dist1 = GetSR04Range_ECHO1();
		tempDist = CalcuDist(dist1);
		if(tempDist < (Stairlenth - 20))
		{
			MotorTT_F(Stop);
			MotorTT_L(Stop);
			MotorTT_R(Stop);
			MotorTT_B(Stop);
			flag = 5;
			return DONE;
		}
	}
	
	
	return 0;
}


int32_t Side2Side(void)   //楼梯的一边平移到另一边
{
	uint8_t flag = 0;
	//对应左右两边距离
	int32_t tempDist2 = 0;
	int32_t tempDist3 = 0;
	if(flag == 0)
	{	
		SteeingEngCtrl(Turn); //舵机调节轮子方向
		HAL_Delay(1000);
		flag = 1;
	}
	
	if(flag == 1)
	{
	dist2 = GetSR04Range_ECHO2();
	tempDist2 = CalcuDist(dist2);
	dist3 = GetSR04Range_ECHO3();
	tempDist3 = CalcuDist(dist3);
	if(tempDist2 <= 3)
	{flag = 2;}//从左到右
	if(tempDist3 <= 3)
	{flag = 3;}//从右到左
	}
	if(!(tempDist3 <= 3) && !(tempDist2 <= 3))
	{
		flag = 3;
	}
	if(flag == 2){
		MotorTT_F(Fow);
		MotorTT_L(Fow);
		MotorTT_R(Fow);
		MotorTT_B(Fow);	
		dist3 = GetSR04Range_ECHO3();
		tempDist3 = CalcuDist(dist3);
		if(tempDist3<=3)
		{
			MotorTT_F(Stop);
			MotorTT_L(Stop);
			MotorTT_R(Stop);
			MotorTT_B(Stop);	
			flag++;
		}
	}
	if(flag == 3){
		MotorTT_F(Bk);
		MotorTT_L(Bk);
		MotorTT_R(Bk);
		MotorTT_B(Bk);	
		dist2 = GetSR04Range_ECHO2();
		tempDist2 = CalcuDist(dist2);
		if(tempDist2<=3)
		{
			MotorTT_F(Stop);
			MotorTT_L(Stop);
			MotorTT_R(Stop);
			MotorTT_B(Stop);	
			
			flag++;
			return DONE;
		}
	}
	return 0;

}

int32_t UUD2UUU(void)//抬升尾部
{
		uln2003_MotorRotation_1(FORWARD1);//尾部上升
		timeRecordcmd = 1;
		if(klick >= klick_up)
		{
			uln2003_MotorRotation_1(BRAKE1); 
			uln2003_MotorRotation_1(STOP_IT1); 
			timeRecordcmd = 0;		
			return DONE;
		}
	return 0;
}

/*
	抬升完尾部之后
	重新视作DDD to UUD 进行
	


*/














