

/*********************************INCLUDES******************************************/
#include "BSP/led_gpio.h"
#include "BSP/timers.h"

#include "tim.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/
void led_gpio_set(led_t led, led_state_t status)
{
	if(led == RED)
	{
		if(status == LED_ON)
		{
			HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, LED_ON);
		}
		else
		{
			HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, LED_OFF);
		}
	}
	else if(led == GREEN)
	{
		if(status == LED_ON)
		{
			HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, LED_ON);
		}
		else
		{
			HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, LED_OFF);
		}
	}
	else if(led == BLUE)
	{
		if(status == LED_ON)
		{
			HAL_GPIO_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, LED_ON);
		}
		else
		{
			HAL_GPIO_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, LED_OFF);
		}
	}
	else
	{
		if(status == LED_ON)
		{
			HAL_GPIO_WritePin(LED_WHITE_PORT, LED_WHITE_PIN, LED_ON);
		}
		else
		{
			HAL_GPIO_WritePin(LED_WHITE_PORT, LED_WHITE_PIN, LED_OFF);
		}
	}
}


void led_gpio_all_off(void)
{
	//turn off led array
	timer_off(&htim7);


	HAL_GPIO_WritePin(LED_RED_PORT, LED_RED_PIN, LED_OFF);
	HAL_GPIO_WritePin(LED_GREEN_PORT, LED_GREEN_PIN, LED_OFF);
	HAL_GPIO_WritePin(LED_BLUE_PORT, LED_BLUE_PIN, LED_OFF);
	HAL_GPIO_WritePin(LED_WHITE_PORT, LED_WHITE_PIN, LED_OFF);
}


