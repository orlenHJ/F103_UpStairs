#include "mode_GO.h"
int32_t dist1 = 0;
int32_t dist2 = 0;
int32_t dist3 = 0;
uint32_t Stairlenth;

//��Ϊ����
//		dist1 = GetSR04Range_ECHO1();   //ǰ��
//		dist2 = GetSR04Range_ECHO2();		//��
//		dist3 = GetSR04Range_ECHO3();		//�ҷ�

int32_t CalcuDist(int32_t dist)//��֤��ֹʱ���ȶ�
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

/////////////////////�ŵ�While��ִ��

int32_t UpStairs_DDD2UUD(void)
{
	/*
			װ��������һ��ʼΪ DDD   �� �����������Ϊ  UUD��ǰ������̧��
	*/
	
	uint8_t flag = 0; //����
	int32_t tempDist = 0; //��ģʽ�£�װ��ǰ��Ĭ���Ѿ�����̨��

	//��֤��ʱ�����λ
	if(flag == 0)
	{
		SteeingEngCtrl(Back);
		HAL_Delay (1000);
		flag++;
	}	
	if(flag == 1)
	{
		uln2003_MotorRotation_2(FORWARD2);  //ǰ�������������
		klick_up_cmd = 1; //����������ʱ
		dist1 = GetSR04Range_ECHO1();
		tempDist = CalcuDist(dist1);
		if(tempDist > 25) //������һ̨��ʱ
		{	
			Stairlenth = tempDist;
			timeRecordcmd = 1; //klick��ʼ��ʱ
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
	
	//��Ϊ��ǰ��
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
	if(flag == 3) //̧���в�
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
	//��Ϊ��ǰ��
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


int32_t Side2Side(void)   //¥�ݵ�һ��ƽ�Ƶ���һ��
{
	uint8_t flag = 0;
	//��Ӧ�������߾���
	int32_t tempDist2 = 0;
	int32_t tempDist3 = 0;
	if(flag == 0)
	{	
		SteeingEngCtrl(Turn); //����������ӷ���
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
	{flag = 2;}//������
	if(tempDist3 <= 3)
	{flag = 3;}//���ҵ���
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

int32_t UUD2UUU(void)//̧��β��
{
		uln2003_MotorRotation_1(FORWARD1);//β������
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
	̧����β��֮��
	��������DDD to UUD ����
	


*/














