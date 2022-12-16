#include "HC_SR04.h"
#include "tim.h"




extern TIM_HandleTypeDef htim2;
int32_t timeRecordcmd = 0;
int32_t klick = 0;
int32_t klick_up = 0;
int32_t klick_up_cmd = 0;


uint8_t  TIM2CH1_CAPTURE_STA=0;							 				
uint16_t	TIM2CH1_CAPTURE_VAL;						
uint8_t  TIM2CH2_CAPTURE_STA=0;
uint16_t	TIM2CH2_CAPTURE_VAL;
uint8_t  TIM2CH3_CAPTURE_STA=0;
uint16_t	TIM2CH3_CAPTURE_VAL;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
	  if(htim==(&htim2))
    {
			if((TIM2CH1_CAPTURE_STA&0X80)==0)				
			{
				
				if(TIM2CH1_CAPTURE_STA&0X40)				
				{
					if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)	
					{
						TIM2CH1_CAPTURE_STA|=0X80;			
						TIM2CH1_CAPTURE_VAL=0XFFFF;
					}else TIM2CH1_CAPTURE_STA++;
				}	 
			}	
    }
		//////////////////////////
		if(htim==(&htim2))
    {
			if((TIM2CH2_CAPTURE_STA&0X80)==0)				
			{
				
				if(TIM2CH2_CAPTURE_STA&0X40)				
				{
					if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)	
					{
						TIM2CH2_CAPTURE_STA|=0X80;			
						TIM2CH2_CAPTURE_VAL=0XFFFF;
					}else TIM2CH2_CAPTURE_STA++;
				}	 
			}	
    }
		//////////////////////////
		if(htim==(&htim2))
    {
			if((TIM2CH3_CAPTURE_STA&0X80)==0)				
			{
				
				if(TIM2CH3_CAPTURE_STA&0X40)				
				{
					if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)	
					{
						TIM2CH3_CAPTURE_STA|=0X80;			
						TIM2CH3_CAPTURE_VAL=0XFFFF;
					}else TIM2CH3_CAPTURE_STA++;
				}	 
			}	
    }
		if(htim == (&htim3))//ÿһ���һ��
		{
			timKeper++;   
			if(timeRecordcmd == 1)
			{
				klick++;
			}
			else if(timeRecordcmd == 0)
			{
				klick = 0;
			}
			if(klick_up_cmd == 1)
			{
				klick_up++;
			}
			
			
		}

}

//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	if((TIM2CH1_CAPTURE_STA&0X80)==0)				//��δ�ɹ�����
	{
		if(TIM2CH1_CAPTURE_STA&0X40)				//����һ���½��� 		
		{	  			
			TIM2CH1_CAPTURE_STA|=0X80;				//��ǳɹ�����һ�θߵ�ƽ����
      TIM2CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
            TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
		}else  										//��δ��ʼ,��һ�β���������
		{
			TIM2CH1_CAPTURE_STA=0;					//���
			TIM2CH1_CAPTURE_VAL=0;
			TIM2CH1_CAPTURE_STA|=0X40;				//��ǲ�����������
			__HAL_TIM_DISABLE(&htim2);      	//�رն�ʱ��2
			__HAL_TIM_SET_COUNTER(&htim2,0);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��2ͨ��1����Ϊ�½��ز���
			__HAL_TIM_ENABLE(&htim2);		//ʹ�ܶ�ʱ��5
		}		    
	}		
	/////////////////////////////////////���¾�Ϊ�ϱߵĸ���
	if((TIM2CH2_CAPTURE_STA&0X80)==0)				
	{
		if(TIM2CH2_CAPTURE_STA&0X40)				
		{	  			
			TIM2CH2_CAPTURE_STA|=0X80;				
      TIM2CH2_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2);  
            TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
		}else  									
		{
			TIM2CH2_CAPTURE_STA=0;				
			TIM2CH2_CAPTURE_VAL=0;
			TIM2CH2_CAPTURE_STA|=0X40;				
			__HAL_TIM_DISABLE(&htim2);      	
			__HAL_TIM_SET_COUNTER(&htim2,0);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2);   
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);
			__HAL_TIM_ENABLE(&htim2);		
		}		    
	}		
	//////////////////////////////////////
	if((TIM2CH3_CAPTURE_STA&0X80)==0)				
	{
		if(TIM2CH3_CAPTURE_STA&0X40)				
		{	  			
			TIM2CH3_CAPTURE_STA|=0X80;				
      TIM2CH3_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3);  
            TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);
		}else  									
		{
			TIM2CH3_CAPTURE_STA=0;				
			TIM2CH3_CAPTURE_VAL=0;
			TIM2CH3_CAPTURE_STA|=0X40;				
			__HAL_TIM_DISABLE(&htim2);      	
			__HAL_TIM_SET_COUNTER(&htim2,0);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3);   
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);
			__HAL_TIM_ENABLE(&htim2);		
		}		    
	}	
	
	

	
	
	
}




int32_t GetSR04Range_ECHO1(void)  //ǰ��
{
	
		int32_t temp=0,Distance=0;
	  
		//TRig
		TRIG_L();
		HAL_Delay(1);
		TRIG_H();
		HAL_Delay(10);
		TRIG_L();

		//�������
     if(TIM2CH1_CAPTURE_STA&0X80)        
		{
			temp=TIM2CH1_CAPTURE_STA&0X3F; 
			temp*=65536;		 	    	
			temp+=TIM2CH1_CAPTURE_VAL;      
			Distance=(temp/58);
			//printf("Distance:%d cm\r\n",Distance);  
			

			
			TIM2CH1_CAPTURE_STA=0;          
			
			return Distance;
		}	
		
		return 0;
	
}

int32_t GetSR04Range_ECHO2(void)
{
	
		int32_t temp=0,Distance=0;
	  
		//TRig
		TRIG_L();
		HAL_Delay(1);
		TRIG_H();
		HAL_Delay(10);
		TRIG_L();

		//�������
     if(TIM2CH2_CAPTURE_STA&0X80)        
		{
			temp=TIM2CH2_CAPTURE_STA&0X3F; 
			temp*=65536;		 	    	
			temp+=TIM2CH2_CAPTURE_VAL;     
			Distance=(temp/58);
			//printf("Distance:%d cm\r\n",Distance);  
			

			
			TIM2CH2_CAPTURE_STA=0;         
			
			return Distance;
		}	
		
		return 0;
	
}


int32_t GetSR04Range_ECHO3(void)
{
	
		int32_t temp=0,Distance=0;
	  
		//TRig
		TRIG_L();
		HAL_Delay(1);
		TRIG_H();
		HAL_Delay(10);
		TRIG_L();

		//�������
     if(TIM2CH3_CAPTURE_STA&0X80)        
		{
			temp=TIM2CH3_CAPTURE_STA&0X3F; 
			temp*=65536;		 	    	
			temp+=TIM2CH3_CAPTURE_VAL;      
			Distance=(temp/58);
			//printf("Distance:%d cm\r\n",Distance);  
			

			
			TIM2CH3_CAPTURE_STA=0;       
			
			return Distance;
		}	
		
		return 0;
	
}


