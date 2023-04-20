#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

void GPIO_Init(void);
void blueLedControllerTask(void *pvParameters);
void redLedControllerTask(void *pvParameters);

#define GREEN  GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED    GPIO_PIN_14
#define BLUE   GPIO_PIN_15

int main()
{
	GPIO_Init();
	int i;
	xTaskCreate(blueLedControllerTask, "Bue Led Controller", 100, NULL, 1, NULL); 
	xTaskCreate(redLedControllerTask, "Red Led Controller", 100, NULL, 1, NULL);
	
	vTaskStartScheduler();
	
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GREEN|BLUE|RED|ORANGE);
		for(i = 0; i < 500000; i ++){}
	}	
}

void redLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, RED);
		for(i = 0; i < 500000; i ++){}
	}
}

void blueLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, BLUE);
		for(i = 0; i < 500000; i ++){}
	}
}

void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*GPIO Ports Clock Enable*/
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	
	/*Configure GPIO pins : PD12 PD13 PD14 PD15 */
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
}
