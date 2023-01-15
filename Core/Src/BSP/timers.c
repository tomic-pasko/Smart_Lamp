

/*********************************INCLUDES******************************************/
#include "BSP/timers.h"
#include "math.h"

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/
void timer_on(TIM_HandleTypeDef* tim, uint8_t interval_s)
{
	uint32_t counter_value = 0;
	uint32_t counter_max_value = 0;

	counter_max_value = interval_s / TIM_FREQ;

	__HAL_TIM_CLEAR_IT(tim, TIM_IT_UPDATE);
	__HAL_TIM_SET_COUNTER(tim, counter_value);
	// set counter_max_value as value until the counter counts
	__HAL_TIM_SET_AUTORELOAD(tim, counter_max_value);

	// start timer
	HAL_TIM_Base_Start_IT(tim);
}


void timer_off(TIM_HandleTypeDef* tim)
{
	HAL_TIM_Base_Stop_IT(tim);
}


timer_status_t is_timer_on(TIM_HandleTypeDef* tim)
{
	if ((tim->Instance->CR1) && 0x01 == 1)
		return timer_started;
	else
		return timer_stopped;
}
