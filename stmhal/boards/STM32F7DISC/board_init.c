#include STM32_HAL_H

//*
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  //Enable Power Control clock 
  __HAL_RCC_PWR_CLK_ENABLE();

  // The voltage scaling allows optimizing the power consumption when the device is
  //   clocked below the maximum system frequency, to update the voltage scaling value
  //   regarding system frequency refer to product datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Enable HSE Oscillator and activate PLL with HSE as source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // activate the OverDrive to reach the 180 Mhz Frequency
  HAL_PWREx_ActivateOverDrive();


  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  // clocks dividers 
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

}//*/

void STM32F7DISC_board_early_init(void) {
	HAL_Init();
	SystemClock_Config();
    GPIO_InitTypeDef GPIO_InitStructure;

    __GPIOK_CLK_ENABLE();

    // Turn off the backlight. LCD_BL_CTRL = PK3
    GPIO_InitStructure.Pin = GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);
}
