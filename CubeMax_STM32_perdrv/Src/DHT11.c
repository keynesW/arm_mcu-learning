#include "tim.h"
#include "gpio.h"
#include "dht11.h"

//温湿度定义

uint8_t ucharT_data_H=0,ucharT_data_L=0,ucharRH_data_H=0,ucharRH_data_L=0,ucharcheckdata=0;

void HAL_Delay_1us(uint8_t Delay)
{
	uint8_t i,j;
    for(i=0;i<Delay;i++)
		{
			for(j=0;j<7;j++)
			{
		  
				
			}
		}
}
void D2_OUT_GPIO_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;  
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void D2_IN_GPIO_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void DHT11_TEST(void)   //温湿传感启动
{
  uint8_t ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_humidity,ucharRH_data_L_humidity,ucharcheckdata_temp;
  volatile uint8_t ucharFLAG = 0,uchartemp=0;
  volatile uint8_t ucharcomdata;
  uint8_t i;         

  D2_OUT_GPIO_Init(); 
 // HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
		//for(i=0;i<100;i++)	
  HAL_Delay_1us(30);
	
  //send start bit
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_Delay(28);

  //pull up and waiting
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_Delay_1us(30);
//  HAL_Delay_1us(20);
//	HAL_Delay_1us(30);
//	HAL_Delay_1us(30);
 
  //set pin mode as input mode
  D2_IN_GPIO_Init();
	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_Delay_1us(20);

    //DHT1x Respone 
    if(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)) 
         {
            ucharFLAG=2; 
			//wait for DH1x pull up for sending data
            while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++)
				;
            ucharFLAG=2;
			//wait for pull up end
            while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)&&ucharFLAG++)
				; 
			
			//data transport
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
				 //waiting for data bit
                 while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++)
					 ;
				 uchartemp=0;
                 HAL_Delay_1us(35);
                 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))
					 uchartemp=1;
				 
                 ucharFLAG=2;
				 //waiting for data 1 bit end
                 while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)&&ucharFLAG++)
					 ;   
                 if(ucharFLAG==1)
					 break;    
                 ucharcomdata<<=1;
                 ucharcomdata|=uchartemp; 
               }
            ucharRH_data_H_humidity = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);
               HAL_Delay_1us(35);
                 uchartemp=0;
                 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))uchartemp=1;
                 ucharFLAG=2;
                 while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)&&ucharFLAG++);   
                 if(ucharFLAG==1)break;    
                 ucharcomdata<<=1;
                 ucharcomdata|=uchartemp; 
               }
            ucharRH_data_L_humidity = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);
                 HAL_Delay_1us(35);
                 uchartemp=0;
                 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))uchartemp=1;
                 ucharFLAG=2;
                 while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);   
                 if(ucharFLAG==1)break;    
                 ucharcomdata<<=1;
                 ucharcomdata|=uchartemp; 
               }
            ucharT_data_H_temp = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);
                HAL_Delay_1us(35);
                 uchartemp=0;
                 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))uchartemp=1;
                 ucharFLAG=2;
                 while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);   
                 if(ucharFLAG==1)break;    
                 ucharcomdata<<=1;
                 ucharcomdata|=uchartemp; 
               }
            ucharT_data_L_temp      = ucharcomdata;
            for(i=0;i<8;i++)    
              {
                 ucharFLAG=2; 
                 while((!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);
                HAL_Delay_1us(30);
                 uchartemp=0;
                 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))uchartemp=1;
                 ucharFLAG=2;
                 while((HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))&&ucharFLAG++);   
                 if(ucharFLAG==1)break;    
                 ucharcomdata<<=1;
                 ucharcomdata|=uchartemp; 
               }
            ucharcheckdata_temp     = ucharcomdata;
//            humiture=1; 
            uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_humidity+ucharRH_data_L_humidity);
             
          if(uchartemp==ucharcheckdata_temp)
          {          
              ucharT_data_H  = ucharT_data_H_temp;
              ucharT_data_L  = ucharT_data_L_temp;
              ucharRH_data_H = ucharRH_data_H_humidity;
              ucharRH_data_L = ucharRH_data_L_humidity;
              ucharcheckdata = ucharcheckdata_temp;      
              printf("---ucharT_data_H = %d\n",ucharT_data_H);	
							printf("---ucharRH_data_H = %d\n",ucharRH_data_H);						
          } 
       } 
    else //没用成功读取，返回0
       {
          ucharT_data_H  = 0;
          ucharT_data_L  = 0;
          ucharRH_data_H = 0;
          ucharRH_data_L = 0; 
       } 
}











