#include "main.h"
#include "cmsis_os.h"
#include "ssd1351_driver.h"
#include "gt_521fx_driver.h"
#include "keypad.h"
#include "flash_access.h"
#include "serial_com.h"
#include "board_init.h"

// locally global variables
SPI_HandleTypeDef g_hspi2;
UART_HandleTypeDef g_huart1;
DMA_HandleTypeDef g_hdma_usart1_rx;
DMA_HandleTypeDef g_hdma_usart1_tx;

// local prototypes
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_SPI2_Init(void);
void MX_USART1_UART_Init(void);
void Error_Handler(void);
void board_wakeup(void);
void port_wakeup(void);


void board_wakeup(void)
{
	SystemClock_Config();
	HAL_Init();
}


void port_wakeup(void)
{
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SPI2_Init();
	MX_USART1_UART_Init();
}


void board_init(void)
{
	board_wakeup();
	port_wakeup();
	flash_init();
	ssd1351_init();
	keypad_init();
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

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) Error_Handler();

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) Error_Handler();

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) Error_Handler();
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
void MX_SPI2_Init(void)
{
  g_hspi2.Instance = SPI2;
  g_hspi2.Init.Mode = SPI_MODE_MASTER;
  g_hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  g_hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  g_hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  g_hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  g_hspi2.Init.NSS = SPI_NSS_SOFT;
  g_hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  g_hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  g_hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  g_hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  g_hspi2.Init.CRCPolynomial = 7;
  g_hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  g_hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&g_hspi2) != HAL_OK) Error_Handler();
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{
  g_huart1.Instance = USART1;
  g_huart1.Init.BaudRate = 9600;
  g_huart1.Init.WordLength = UART_WORDLENGTH_8B;
  g_huart1.Init.StopBits = UART_STOPBITS_1;
  g_huart1.Init.Parity = UART_PARITY_NONE;
  g_huart1.Init.Mode = UART_MODE_TX_RX;
  g_huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  g_huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  g_huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  g_huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&g_huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8
                          |GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA8
                           PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8
                          |GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB5 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC8 PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}


void board_init_set_wkup_src(void)
{
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1_LOW);
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	__HAL_PWR_CLEAR_FLAG(PWR_WAKEUP_PIN1_LOW);
}


void board_init_activate_garage_door(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
}


void board_init_deactivate_garage_door(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	// no bueno
	while(1);
}





