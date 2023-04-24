
#include "STM32F4_RTOS_BSP.h"
void drawaxes(void);
void drawInfoBar(void);
#define YMAX 5000
#define YMIN 0

int freq;
int32_t sensorValue;
void plotData(void);

int main(void)
{ 	
	
	SystemClock_Config80Mhz();
  HAL_Init();
	Probe_Init();
	 ST7735_Init();
	ADC1_Init();
	drawaxes();
	while(1)
	{
		Probe_CH0();
		 HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		 sensorValue = HAL_ADC_GetValue(&hadc1);
   drawInfoBar();
		
		 plotData();


	}
}


void plotData(void)
{
	ST7735_PlotPoint(sensorValue,GREEN);
	ST7735_PlotIncrement();
	
	
}
void drawaxes(void){
    ST7735_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "ADC", LIGHTCOLOR, "", 0, YMAX, YMIN);
}

void drawInfoBar(void)
{
    ST7735_DrawString(1, 0, "CPU =", GREEN);

	    ST7735_DrawString(7, 0, "75%", BLUE );
    ST7735_DrawString(11, 0, "Temp =", GREEN);
   	    ST7735_DrawString(18, 0, "30", BLUE );



}

