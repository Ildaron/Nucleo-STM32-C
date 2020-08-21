
#include "main.h"


SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  int r = 0;

	  /* USER CODE END WHILE */
	  		     /* USER CODE END WHILE */
	  		  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);


	  		  HAL_Delay (200);
	  		  unsigned int a,b;
	  		     // HAL_SPI_TransmitReceive(&hspi1, &address, &data, sizeof(data), 0x1000);
	  		   	 // b0=HAL_SPI_TransmitReceive(&hspi1, 0, 768, 10, 0x1000);
	  		  unsigned int data = 0;//0b01100000;
	  		  //HAL_SPI_TransmitReceive(&hspi1,data,a,8,1000);
	  		  //HAL_SPI_TransmitReceive(&hspi1,data,b,8,1000);   // 0x1000
	  		 // HAL_SPI_Transmit(&hspi1,txData,4,TIMEOUTVALUE);

	  		  uint8_t c = 0;



	  	  ///	   HAL_SPI_Receive(&hspi1,a,8,1000);
	  	 ///	   HAL_SPI_Receive(&hspi1,b,8,1000);

	  	//	  HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) (src_buf+i), (uint8_t *) (dst_buf+i), 128);

	  		  uint8_t received_byte;
	  		  uint8_t Byte=0;
	  		  HAL_SPI_TransmitReceive(&hspi1,(uint8_t*)&Byte,(uint8_t*)&received_byte,1,0x1000);



	  		//  int b3;
	    	//	  b3=(a<<8)|b;    //???????? ??? ????? ? ???????????? ????????
	    	//	  b3=b3&16368;

	  		//  int c =1;
	       		   //  char c1 = "1";
	  		    // HAL_UART_Transmit(&huart1, (uint8_t*)"c", 1, 1000);
	  		   // HAL_UART_Transmit(&huart1, (uint8_t*)c1, 1, 1000);
	  		   //  uint8_t str[5];
	  		     char str[6];
	  		     char str1[6];
	  		     int adc = 72324;
	  		  //   int adc = received_byte;
	  		   //  adc= b;
	  		     sprintf (str1, "%d\n", adc);

	  		        // uint8_t c1[1];
	  			    //   c1[0] = 7 + '0';
	  			    // HAL_UART_Transmit_IT(&huart1, c1, 32);
	  			    //    HAL_UART_Transmit(&huart1, c1, 1, 1000);


	  		     for (r; r<10; r=r+1) {
	  		     	    if (str1[r]!= 0)
	  		     	     {
	  		           str[0] = str1[r];
	  		     	   HAL_UART_Transmit(&huart1, str, 1, 1000);
	  		     	 //  HAL_UART_Transmit(&huart1, (uint8_t*)"0", 1, 1000);
	  		     		 }
	  		   //  else
	  		   //          {
	  		          //  HAL_UART_Transmit(&huart1, (uint8_t*)"0", 1, 1000);

	  		              }
	  		  //   	                      }
	  		     						  r=0;

	  		  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);






	  		    // c1[0] = 7 + '0';
	  		    // HAL_UART_Transmit_IT(&huart1, c1, 32);
	  		    // HAL_UART_Transmit(&huart1, c1, 1, 1000);








	  		// HAL_UART_Transmit(&huart1, (uint8_t*)"Hello World\n", 12, 1000);
	  		// b1=SPI_ChangeByte(0);        // first byte
	  		// b2=SPI_ChangeByte(0);        // second byte
	  		// b3=(b1<<8)|b2;//???????? ??? ????? ? ???????????? ????????
	  		// b3=b3&16368;



	  		    //    HAL_SPI_TransmitReceive(&hspi1,&adcTransmitData,&adcReceiveData,1,1);
	  		    //    transmitBuffer[0] = adcReceiveData;
	  		      /* USER CODE BEGIN 3 */
	  	    /* USER CODE BEGIN 3 */

	//    }
	    /* USER CODE END 3 */
	//  }




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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{


  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }


}


static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_Pin */
  GPIO_InitStruct.Pin = CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
