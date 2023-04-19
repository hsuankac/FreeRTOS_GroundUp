#include "stm32f4xx_hal.h"

int USART2_write(int ch);
int __io_putchar(int ch);

UART_HandleTypeDef huart2;

void USART2_UART_TX_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
  }
}

void USART2_UART_RX_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
  }
}

int USART2_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	while(!(USART2->SR & USART_SR_TXE)){}

	/*Write to transmit data register*/
	USART2->DR	=  (ch & 0xFF);
	return ch;
}

int USART2_read(void)
{
	while(!(USART2->SR & 0x0020)){}
	return USART2 -> DR;
}

int __io_putchar(int ch)
{
	USART2_write(ch);
	return ch;
}
