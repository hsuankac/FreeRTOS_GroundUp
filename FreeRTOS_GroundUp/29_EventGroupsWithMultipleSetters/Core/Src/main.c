#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "uart.h"
#include "exti.h"
#include "adc.h"

#define TASK1_BIT		(1UL << 0UL)
#define TASK2_BIT		(1UL << 1UL)
#define TASK3_BIT		(1UL << 2UL)

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void InputTask1(void *pvParameters);
void InputTask2(void *pvParameters);
void InputTask3(void *pvParameters);
void OutputTask(void *pvParameters);

EventGroupHandle_t xEventGroup;

const TickType_t xDelay500ms = pdMS_TO_TICKS(500UL);

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  USART2_UART_TX_Init();
  printf("system initializing....\r\n");

  xEventGroup = xEventGroupCreate();
  xTaskCreate(InputTask1, "InputTask 1", 100, NULL, 1, NULL);
  xTaskCreate(InputTask2, "InputTask 2", 100, NULL, 1, NULL);
  xTaskCreate(InputTask3, "InputTask 3", 100, NULL, 1, NULL);

  xTaskCreate(OutputTask, "OutputTask", 100, NULL, 1, NULL);

  vTaskStartScheduler();

  while (1)
  {

  }
}

void InputTask1(void *pvParameters)
{
	while(1)
	{
		//Do something....
		xEventGroupSetBits(xEventGroup, TASK1_BIT);
	}
}

void InputTask2(void *pvParameters)
{
	while(1)
	{
		//Do something....
		xEventGroupSetBits(xEventGroup, TASK2_BIT);
	}
}

void InputTask3(void *pvParameters)
{
	while(1)
	{
		//Do something....
		xEventGroupSetBits(xEventGroup, TASK3_BIT);
	}
}

void OutputTask(void *pvParameters)
{
	const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT);
	EventBits_t xEventGroupValue;

	while(1)
	{
		xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitsToWaitFor, pdTRUE, pdFALSE, portMAX_DELAY);

		if((xEventGroupValue & TASK1_BIT) != 0)
		{
			printf("BIT READING TASK : EVENT BIT 0 SET - TASK 1 \r\n");
		}

		if((xEventGroupValue & TASK2_BIT) != 0)
		{
			printf("BIT READING TASK : EVENT BIT 1 SET - TASK 2 \r\n");
		}

		if((xEventGroupValue & TASK3_BIT) != 0)
		{
			printf("BIT READING TASK : EVENT BIT 2 SET - TASK 3 \r\n");
		}
	}
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }

}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
