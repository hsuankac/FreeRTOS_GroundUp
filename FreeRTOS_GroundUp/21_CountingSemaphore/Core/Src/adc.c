#include "stm32f4xx_hal.h"

void adc_init(void)
{
	//Enable the GPIOA clock
	RCC -> AHB1ENR |= (1U << 0);

	//Enable clock for ADC1
	RCC -> APB2ENR |= (1U << 8);

	//Set PA1 to analog mode
	GPIOA -> MODER |= 0xC;

	ADC1 -> CR2 = 0;	// SW trigger
	ADC1 -> SQR3 = 1;	// conversion sequence starts at channel 1
	ADC1 -> SQR1 = 0;	// conversion sequence length 1
	ADC1 -> CR2 |= 1;	// enable ADC1
}

uint32_t read_analog_sensor(void)
{
	ADC1 -> CR2 |= (1U << 30); // Start conversion

	while(!(ADC1 -> SR & 2)){} // Wait for conversion to complete

	return ADC1 -> DR;
}
