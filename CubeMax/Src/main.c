/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define SIZE 100
unsigned char dma_buff[SIZE] = {0};
unsigned char recv_buff[10] = {0}; 

extern int ADC_DMA_Value[ADC_NUM];

int get_key(int a,int *parr)
{
	int i = 0;
	for( i = 0; i < 5; i++)
		if( a < parr[i])
			break;
	//int array[] = {300,1140,1195,2015,2300,3300}; 		
	printf("%d\n",i);
	return i;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM17_Init();
  MX_ADC_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
  HAL_UART_Receive_IT(&huart1,recv_buff,1);
  uint8_t rec_buff[10] = {0};
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
  HAL_UART_Receive_IT(&huart2,rec_buff,1);
  //__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
  //__HAL_UART_CLEAR_IDLEFLAG(&huart1);
  
  /*****************************************************
   *
   * HAL_UART_Receive_DMA(&huart1,dma_buff,SIZE);
   *
   ****************************************************/
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  Lcd_Init();
//  Lcd_Clear(BLUE);
//  //showimage(1600,39,39,gImage_qq_logo,10,10,49,49);
//  Gui_DrawFont_GBK16(12,64,BLACK,YELLOW,"HELLO");

  //HAL_TIMEx_PWMN_Start(&htim17,TIM_CHANNEL_1);
  char temp = recv_buff[0];
  //HAL_ADC_Start_DMA(&hadc, (uint32_t*)ADC_DMA_Value, 3);
  
  UNUSED(temp);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 // printf("helloword\n");
	  HAL_Delay(1000);
	  /*
	if(temp != recv_buff[0])
	{
		printf(" char : %c ,integer : %d ",recv_buff[0],recv_buff[0]);
		temp = *recv_buff;
		switch(recv_buff[0])
		{
			case '0':
				MX_TIM17_Set(4800-1, 100, 10);
				break;	
			case '1':
				MX_TIM17_Set(4800-1, 100, 20);
				break;	
			case '2':
				MX_TIM17_Set(4800-1, 100, 30);
				break;	
			case '3':
				MX_TIM17_Set(4800-1, 100, 40);
				break;	
			case '4':
				MX_TIM17_Set(4800-1, 100, 50);
				break;	
			case '5':
				MX_TIM17_Set(4800-1, 100, 60);
				break;	
			case '6':
				MX_TIM17_Set(4800-1, 100, 70);
				break;	
			case '7':
				MX_TIM17_Set(4800-1, 100, 80);
				break;	
			case '8':
				MX_TIM17_Set(4800-1, 100, 90);
				break;	
			default:
				MX_TIM17_Set(4800-1, 100, 100);
				break;	
		}
	    HAL_TIMEx_PWMN_Start(&htim17,TIM_CHANNEL_1);
	}	
	
	int a = ((uint16_t)ADC_DMA_Value[0] *3300)/4096-30;
	printf("a : %d\n",a);
	//printf("BAT : %d,  module :%d\n",ADC_DMA_Value[1],ADC_DMA_Value[2]);
	int array[] = {300,1100,1560,1925,1990,3300};  // down, left, up, push,none

	switch( get_key(a,array) )
	{
	        case 1:
				MX_TIM17_Set(4800-1, 100, 0);
				break;	
			case 2:
				MX_TIM17_Set(4800-1, 100, 20);
				break;	
			case 3:
				MX_TIM17_Set(4800-1, 100, 40);
				break;	
			case 4:
				MX_TIM17_Set(4800-1, 100, 60);
				break;	
			case 5:
				MX_TIM17_Set(4800-1, 100, 80);
				break;	
			default:	
				MX_TIM17_Set(4800-1, 100, 100);
				break;	
	}
	HAL_TIMEx_PWMN_Start(&htim17,TIM_CHANNEL_1);
	*/	
  //DHT11_TEST();
  //HAL_Delay(2000);	
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
