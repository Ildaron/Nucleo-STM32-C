
#include "main.h"
I2C_HandleTypeDef hi2c3;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART5_Init(void);
static void MX_SPI3_Init(void);
static void MX_SPI2_Init(void);
static void MX_UART4_Init(void);
static void MX_I2C3_Init(void);
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_UART5_Init();
  MX_SPI3_Init();
  MX_SPI2_Init();
  MX_UART4_Init();
  MX_I2C3_Init();
  void send_data_by_uart (received_byte)
  	  	  {
	  if (received_byte=="X"||received_byte=="Y"||received_byte=="Z")
	  {
		  HAL_UART_Transmit(&huart5, received_byte, 1, 1000);
	  }
	  else
	  {
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
  	  	   }
  	  	  }




  uint16_t  buf_x;
  uint16_t  buf_y;
  uint16_t  buf_z;
  uint8_t adress_write = 0x3C;
  uint8_t adress_read = 0x3D;
  uint8_t CTRL_REG4 = 0x20;
  uint8_t CTRL_REG5 = 0x24;

  HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET);
  uint8_t data=0x0F;

  uint8_t data_reg4 = 0x87;
  HAL_I2C_Mem_Write(&hi2c3, adress_write, CTRL_REG4, 1, (uint8_t*)&data_reg4, 1, 1000);
  uint8_t data_reg5 = 0x20;
  HAL_I2C_Mem_Write(&hi2c3, adress_write, CTRL_REG5,1,  (uint8_t*)&data_reg5, 1,  1000);

 // HAL_I2C_Mem_Write(&hi2c3, adress_write, CTRL_REG1, data, 2, 2, 1000);
  uint8_t test = 0x00;

  uint8_t buf_xyz [6];
  uint8_t status = 0x27;
  uint8_t status_check= 0xF7;
  uint8_t status_ready= 0xFF;
  uint8_t status_readed;
  uint8_t status_comp;

  uint8_t OUT_X1= 0x28;
  uint8_t OUT_X2= 0x29;
  uint8_t OUT_X1_data;
  uint8_t OUT_X2_data;
  uint16_t OUT_X_result;

  uint8_t OUT_Y1= 0x2A;
  uint8_t OUT_Y2= 0x2B;
  uint8_t OUT_Y1_data;
  uint8_t OUT_Y2_data;
  uint16_t OUT_Y_result;

  uint8_t OUT_Z1= 0x2C;
  uint8_t OUT_Z2= 0x2D;
  uint8_t OUT_Z1_data;
  uint8_t OUT_Z2_data;
  uint16_t OUT_Z_result;


  int check = 11;

  while (1)
  {       HAL_GPIO_TogglePin(GPIOA, LED2_Pin);


	  HAL_I2C_Mem_Read(&hi2c3, adress_read, status, 1, (uint8_t*)&status_readed, 1, 1000);
	  status_comp=status_readed|status_check;
	  if (status_comp == status_ready) {

	      HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_X1, 1, (uint8_t*)&OUT_X1_data, 1, 1000);
	  	  HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_X2, 1, (uint8_t*)&OUT_X2_data, 1, 1000);
		  OUT_X_result=OUT_X2_data;
		  OUT_X_result=(OUT_X_result<<8)|OUT_X1_data;

	              HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_Y1, 1, (uint8_t*)&OUT_Y1_data, 1, 1000);
	     	  	  HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_Y2, 1, (uint8_t*)&OUT_Y2_data, 1, 1000);
	     		  OUT_Y_result=OUT_Y2_data;
	     		  OUT_Y_result=(OUT_Y_result<<8)|OUT_Y1_data;

	     	              HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_Z1, 1, (uint8_t*)&OUT_Z1_data, 1, 1000);
	     	    	  	  HAL_I2C_Mem_Read(&hi2c3, adress_read, OUT_Z2, 1, (uint8_t*)&OUT_Z2_data, 1, 1000);
	     	    		  OUT_Z_result=OUT_Z2_data;
	     	    		  OUT_Z_result=(OUT_Z_result<<8)|OUT_Z1_data;

	 send_data_by_uart ("X");
	 send_data_by_uart (OUT_X_result);
	 send_data_by_uart ("Y");
	 send_data_by_uart (OUT_Y_result);
	 send_data_by_uart ("Z");
	 send_data_by_uart (OUT_Z_result);

	//  HAL_I2C_Master_Receive(&hi2c3,adress_read,&buf_xyz,6, 0x1000);
	//	HAL_I2C_Master_Transmit(&hi2c1,dev_adr,(uint8_t*)data,1,200);

	 }
	   HAL_Delay(1000);
  }


  }



void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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


static void MX_I2C3_Init(void)
{


  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }


}


static void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }


}

static void MX_SPI3_Init(void)
{


  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
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
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LED1_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, START_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|LED1_Pin|LED2_Pin;
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
