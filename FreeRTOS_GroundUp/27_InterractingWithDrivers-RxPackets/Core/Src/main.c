#include <stdio.h>
#include "main.h"
#include "cmsis_os.h"
#include "uart.h"
#include "exti.h"
#include "adc.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
int __io_putchar(int ch);
void HandlerTask(void *pvParameters);
int32_t start_rx_interrupt(uint8_t* Buffer, uint_fast16_t Len);

#define STACK_SIZE 				128
#define EXPECTED_PKT_LEN		5
static QueueHandle_t  			uart2_BytesReceived = NULL;
static int rxInProgress;
static uint16_t rxLen = 0;
static uint8_t* rxBuff = NULL;
static uint16_t rxItr = 0;

static SemaphoreHandle_t rxDone = NULL;


int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  USART2_UART_TX_Init();

  rxDone = xSemaphoreCreateBinary();

  xTaskCreate(HandlerTask,
		  	  "uartPrintTask",
			  STACK_SIZE,
			  NULL,
			  tskIDLE_PRIORITY + 3,
			  NULL);

  uart2_BytesReceived = xQueueCreate(10, sizeof(char));

  vTaskStartScheduler();

  while (1)
  {

  }

}

int32_t start_rx_interrupt(uint8_t* Buffer, uint_fast16_t Len)
{
	if(!rxInProgress && (Buffer != NULL))
	{
		rxInProgress = 1;
		rxLen = Len;
		rxBuff = Buffer;
		rxItr = 0;
		USART2 -> CR1 |= 0x0020;
		NVIC_SetPriority(USART2_IRQn, 6);
		NVIC_EnableIRQ(USART2_IRQn);
		return 0;
	}
	return -1;
}

void USART2_IRQHandler(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(USART2 -> SR & 0x0020)
	{
		uint8_t tempVal = (uint8_t) USART2 -> DR;

		if(rxInProgress)
		{
			rxBuff[rxItr++] = tempVal;
			if(rxItr == rxLen)
			{
				rxInProgress = 0;
				xSemaphoreGiveFromISR(rxDone, &xHigherPriorityTaskWoken);
			}
		}
	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


uint8_t rxData[EXPECTED_PKT_LEN];
char rxCode[50] = {0};

void HandlerTask(void *pvParameters)
{
	USART2_UART_RX_Init();

	for(int i = 0; i < EXPECTED_PKT_LEN; i++)
	{
		rxData[i] = 0;
	}

	const TickType_t timeout = pdMS_TO_TICKS(5000);

	while(1)
	{
		start_rx_interrupt(rxData, EXPECTED_PKT_LEN);

		if(xSemaphoreTake(rxDone, timeout) == pdPASS)
		{
			if(EXPECTED_PKT_LEN == rxItr)
			{
				sprintf(rxCode, "received");
			}
			else
			{
				sprintf(rxCode, "Length mismatch");
			}
		}
		else
		{
			sprintf(rxCode, "Timeout");
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
