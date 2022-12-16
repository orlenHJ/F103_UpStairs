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


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//更新中断（溢出）发生时执行
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
		if(htim == (&htim3))//每一秒加一次
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

//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	if((TIM2CH1_CAPTURE_STA&0X80)==0)				//还未成功捕获
	{
		if(TIM2CH1_CAPTURE_STA&0X40)				//捕获到一个下降沿 		
		{	  			
			TIM2CH1_CAPTURE_STA|=0X80;				//标记成功捕获到一次高电平脉宽
      TIM2CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);//获取当前的捕获值.
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
            TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
		}else  										//还未开始,第一次捕获上升沿
		{
			TIM2CH1_CAPTURE_STA=0;					//清空
			TIM2CH1_CAPTURE_VAL=0;
			TIM2CH1_CAPTURE_STA|=0X40;				//标记捕获到了上升沿
			__HAL_TIM_DISABLE(&htim2);      	//关闭定时器2
			__HAL_TIM_SET_COUNTER(&htim2,0);
			TIM_RESET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//定时器2通道1设置为下降沿捕获
			__HAL_TIM_ENABLE(&htim2);		//使能定时器5
		}		    
	}		
	/////////////////////////////////////以下均为上边的复制
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




int32_t GetSR04Range_ECHO1(void)  //前方
{
	
		int32_t temp=0,Distance=0;
	  
		//TRig
		TRIG_L();
		HAL_Delay(1);
		TRIG_H();
		HAL_Delay(10);
		TRIG_L();

		//计算距离
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

		//计算距离
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

		//计算距离
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


