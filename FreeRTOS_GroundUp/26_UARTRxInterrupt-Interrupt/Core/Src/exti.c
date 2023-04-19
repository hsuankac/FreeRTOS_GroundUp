#include "stm32f4xx_hal.h"

void p13_interrupt_init(void)
{
	//Enable GPIOC clock
	RCC -> AHB1ENR |= 4;

	//Enable SYSCFG clock
	RCC -> APB2ENR |= 0x4000;

	//Configure PC13 for push button interrupt
	GPIOC -> MODER &= ~0x0C000000;

	//Clear port selection for EXTI13
	SYSCFG -> EXTICR[3] &= ~0x00F0;

	//Select port C for EXTI13
	SYSCFG -> EXTICR[3] |= 0x0020;

	//Unmasked EXTI13
	EXTI -> IMR |= 0x2000;

	//Select falling edge trigger
	EXTI -> FTSR |= 0x2000;

	NVIC_SetPriority(EXTI15_10_IRQn, 6);

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void goio_init(void)
{
	//Enable GPIOC clock
	RCC -> AHB1ENR |= 4;
}

uint8_t read_digital_sensor(void)
{
	if(GPIOC -> IDR & 0x2000)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
