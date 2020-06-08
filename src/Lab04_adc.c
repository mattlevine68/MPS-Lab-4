//--------------------------------
// Lab 4 - Sample - Lab04_sample.c
//--------------------------------
//
//

#include "init.h"

void configureADC();
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
GPIO_InitTypeDef gpio;
uint16_t rawValue;
volatile float voltage;
volatile float highestVoltage=0;
volatile float lowestVoltage=0;
volatile float averageVoltage;
volatile int count=0;

// Main Execution Loop
int main(void)
{
	//Initialize the system
	Sys_Init();
	configureADC();
	printf("Push the pushbutton to get values\r\n");
	while(1){
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 1000);
		if(HAL_GPIO_ReadPin(GPIOJ, GPIO_PIN_4)){
			rawValue = HAL_ADC_GetValue(&hadc);
			voltage = rawValue*(3.25/4095);
			if(count == 0){
				lowestVoltage = voltage;
			}
			highestVoltage = (voltage > highestVoltage) ? voltage : highestVoltage;
			lowestVoltage = (voltage < lowestVoltage) ? voltage : lowestVoltage;
			averageVoltage += voltage;
			count++;
			averageVoltage = averageVoltage/count;
			printf("\033[2H Hex Value: %X\r\n", rawValue);
			printf("\033[3H Max Value: %.6f\r\n", highestVoltage);
			printf("\033[4H Average Value: %.6f\r\n", averageVoltage);
			printf("\033[5H Min Value: %.6f\r\n", lowestVoltage);
			printf("\033[6H Value now: %.6f\r\n", voltage);
		}
	}

	// Code goes here
}

void configureADC()
{
	// Enable the ADC Clock.
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	hadc.Instance = ADC1;
	hadc.NbrOfCurrentConversionRank = 1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ScanConvMode = DISABLE;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion =1;


	HAL_ADC_Init(&hadc); // Initialize the ADC

	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	/* Available sampling times:

		ADC_SAMPLETIME_3CYCLES
	  ADC_SAMPLETIME_15CYCLES
		ADC_SAMPLETIME_28CYCLES
		ADC_SAMPLETIME_56CYCLES
		ADC_SAMPLETIME_84CYCLES
		ADC_SAMPLETIME_112CYCLES
		ADC_SAMPLETIME_144CYCLES
		ADC_SAMPLETIME_480CYCLES

	*/

	// Configure the ADC channel

	HAL_ADC_ConfigChannel(&hadc, &sConfig);
}


void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();

	//PA6
	gpio.Pin = GPIO_PIN_6;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA,&gpio);

	//PJ4
	gpio.Pin = GPIO_PIN_4;
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOJ,&gpio);



// GPIO init

}

