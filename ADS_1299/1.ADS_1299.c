
#include "main.h"

SPI_HandleTypeDef hspi3;
UART_HandleTypeDef huart5;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART5_Init(void);
static void MX_SPI3_Init(void);

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_UART5_Init();
  MX_SPI3_Init();

   int received_byte;
   uint8_t SDATAC = 0x11;
   uint8_t RESET = 0x06;

   uint8_t WAKEUP = 0x02;


   uint8_t CONFIG1 = 0x01;
   uint8_t CONFIG2 = 0x02;
   uint8_t CONFIG3 = 0x03;
//   uint8_t START = 0x08;
   uint8_t test = 0x00;
 //  uint8_t RDATAC = 0x10;


#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR *(volatile unsigned long *)0xE000EDFC
  	  void DWT_Init(void)
  	  {
  	      SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  	      DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;
  	  }
  	void delay_us(uint32_t us)
  	{
  	    uint32_t us_count_tic =  us * (SystemCoreClock / 1000000);
  	    DWT->CYCCNT = 0U;
  	    while(DWT->CYCCNT < us_count_tic);
  	}
  	DWT_Init();



  void send_command(uint8_t cmd)
  	    {
  	  		    HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
  	  	     	delay_us(20);
  	  	        HAL_SPI_Transmit(&hspi3, (uint8_t*)&cmd,1, 0x1000);
  	  	        delay_us(20);
  	  	        HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	  	       delay_us(3);
  	  	  }


  	  void send_data_by_uart (received_byte)
  	  	  {
  	  	  // step 1 - convert dataset
  	  	  char buffer[16];
  	  	  char buffer1[16];
  	  	  sprintf(buffer1, "%d\n", received_byte);
  	        int a=0;
  	  	  for (a; a<strlen(buffer1); a=a+1) //
  	  	         {
  	  		   if (buffer1[a]!= 0)
  	  		   	        	      {
  	  		   buffer[0] = buffer1[a];
  	  		   HAL_UART_Transmit(&huart5, buffer, 1, 1000);
  	  	                          }
  	  	          }
  	             a=0;
  	          // step 2 - send by uart UART
  	  	       HAL_UART_Transmit(&huart5, "amigos", 6, 1000);  //"amigo\r\n\0"

  	  	  }


  	    void write_byte(uint8_t reg_addr, uint8_t val_hex)
  	    {
  	     HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
  	    // delay_us(5);
  	   //  HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	   //  HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
  	     uint8_t adress = 0x40|reg_addr;
  	     HAL_SPI_Transmit(&hspi3, (uint8_t*)&adress, 1, 0x1000);
  	  //   delay_us(5);
  	     HAL_SPI_Transmit(&hspi3, (uint8_t*)&test, 1, 0x1000);
  	 //    delay_us(5);
  	     HAL_SPI_Transmit(&hspi3, (uint8_t*)&val_hex, 1, 0x1000);
  	     delay_us(50);
    	// delay_us(2);
    	 HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	    }



  	    uint8_t read_byte(uint8_t reg_addr)
  	    {
  	      uint8_t out;

  	      HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
  	      delay_us(20);
  	  //    HAL_SPI_Transmit(&hspi3, (uint8_t*)&SDATAC, 1, 0x1000);
  	 //   HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	   //  	 HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
  	      uint8_t adress = 0x20 | reg_addr ;  //
  	//      delay_us(50);
  	      HAL_SPI_Transmit(&hspi3, (uint8_t*) &adress, 1 ,0x1000);
  	 //
  	      HAL_SPI_Transmit(&hspi3, (uint8_t*)&test, 1, 0x1000);
  	//      delay_us(5);
  	     // HAL_SPI_Receive(&hspi3, (uint8_t*)&out,1, 0x1000);
  	      HAL_SPI_TransmitReceive(&hspi3,(uint8_t*)&test,(uint8_t*)&out,1,0x1000);

  	//      delay_us(1);
  //	      delay_us(1);
  	      HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
    	  return(out);

  	    }

  	    void live_bits ()
  	    {
  	      HAL_Delay(100);
  	      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
  	      HAL_Delay(100);
  	    }


  //	    HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	    //reset communication, see datasheet

  //	     delay_us(10);
  //	    HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
 // 	    HAL_SPI_Transmit(&hspi3, (uint8_t*)&RESET, 1, 0x1000);
  //	    delay_us(40);
 // 	    HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);

  	   HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
  	   delay_us(100);

   //      send_command(RESET);
   //       delay_us(10);
       //   int chSet = read_byte(0x00);
        //  send_data_by_uart (chSet);
       //   delay_us(10);
  	                          send_command(SDATAC);
  	                          delay_us(200);
  	                                HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);

  	   	    	 	    	  	   // HAL_SPI_Transmit(&hspi3, (uint8_t*)&place, 1, 0x1000);
  	   	    	 	  	            HAL_SPI_Transmit(&hspi3, (uint8_t*)&RESET, 1, 0x1000);
  	   	    	 	    	  	    delay_us(72);
  	   	    	 	    	 	    HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);

  	   	    	//
  	   	    	 	    	// 	//   send_command(START);
  	   	    	 	    	  delay_us(200);

  	   	    	 	      	  send_command(SDATAC);


  	   	    	 	    	   	   //  delay_us(100);


//
  	   	    	 	    	 	      write_byte(CONFIG1, 0xD6); // 96
  	   	    	 	    	 	      delay_us(10);
  	   	    	 	   	 	          write_byte(CONFIG2, 0xD1);
  	   	    	 	    	 	      delay_us(10);
  	   	    	 	    	 	      write_byte(CONFIG3, 0xE0);
  	   	    	 	    	 	      delay_us(10);


 	      while (1)
  {


//	      live_bits ();
	//      HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
//	      HAL_Delay(500);

	      // HAL_Delay(10);
//  Step.2 - Write configuarations bits
	     // HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_RESET);
	     // HAL_Delay(1);


 	  //   HAL_GPIO_WritePin(GPIOD, CS_Pin, GPIO_PIN_SET);
 	  //   HAL_Delay(1);
 	   //  delay_us(100);

// Step.3 - Read configuarations bits

 	   	   //           int chSet = read_byte(0x00);
 	    	//          send_data_by_uart (chSet);
 	    	//          delay_us(1000);

 	     int Read_con = read_byte(CONFIG2);
  	     send_data_by_uart(Read_con);

   	 //   HAL_GPIO_WritePin(GPIOD, START_Pin, GPIO_PIN_RESET);
    	delay_us(50);

   }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;     // 2edje - bad
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;//64 almost a good   4
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;    // ok
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, START_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : START_Pin CS_Pin */
  GPIO_InitStruct.Pin = START_Pin|CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
