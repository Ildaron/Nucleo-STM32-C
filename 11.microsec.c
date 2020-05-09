https://istarik.ru/blog/stm32/121.html


/* USER CODE BEGIN PD */
#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR *(volatile unsigned long *)0xE000EDFC
/* USER CODE END PD */


int main(void)
{
/* USER CODE BEGIN 0 */
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

}


/* USER CODE BEGIN Init */
DWT_Init();
/* USER CODE END Init */

while (1)
  {
HAL_GPIO_WritePin(pa5_GPIO_Port, pa5_Pin, GPIO_PIN_SET);
          delay_us(31420); 
          HAL_GPIO_WritePin(pa5_GPIO_Port, pa5_Pin, GPIO_PIN_RESET);
          HAL_Delay(30);
}
