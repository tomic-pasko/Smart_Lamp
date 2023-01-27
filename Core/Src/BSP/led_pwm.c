

/*********************************INCLUDES******************************************/
#include "BSP/led_pwm.h"
#include "tim.h"
#include "BSP/timers.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
led_pwm_s led_pwm;

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

void led_pwm_init(TIM_HandleTypeDef* tim, uint16_t max_counter_value)
{
	led_pwm.tim3 = tim;
	led_pwm.count = max_counter_value;
	led_pwm.init_flag = 1;
	led_pwm.red_led = PWM_LED_OFF;
	led_pwm.green_led = PWM_LED_OFF;
	led_pwm.blue_led = PWM_LED_OFF;
	led_pwm.white_led = PWM_LED_OFF;
}

void led_pwm_set(led_pwm_t led, uint8_t percentage_on)
{
	if (led_pwm.init_flag == 0)
	{
		return ;
	}

	uint16_t compare = percentage_on * led_pwm.count / 100;



	if (led == RED_LED)
	{
		__HAL_TIM_SET_COMPARE(led_pwm.tim3, LED_RED_CHANNEL, compare);

		if (compare == 0)
		{
			HAL_TIM_PWM_Stop(led_pwm.tim3, LED_RED_CHANNEL);
			led_pwm.red_led = PWM_LED_OFF;
		}
		else
		{
			HAL_TIM_PWM_Start(led_pwm.tim3, LED_RED_CHANNEL);
			led_pwm.red_led = PWM_LED_ON;
		}
	}
	else if (led == GREEN_LED)
	{
		__HAL_TIM_SET_COMPARE(led_pwm.tim3, LED_GREEN_CHANNEL, compare);

		if (compare == 0)
		{
			HAL_TIM_PWM_Stop(led_pwm.tim3, LED_GREEN_CHANNEL);
			led_pwm.red_led = PWM_LED_OFF;
		}
		else
		{
			HAL_TIM_PWM_Start(led_pwm.tim3, LED_GREEN_CHANNEL);
			led_pwm.red_led = PWM_LED_ON;
		}
	}
	else if (led == BLUE_LED)
	{
		__HAL_TIM_SET_COMPARE(led_pwm.tim3, LED_BLUE_CHANNEL, compare);

		if (compare == 0)
		{
			HAL_TIM_PWM_Stop(led_pwm.tim3, LED_BLUE_CHANNEL);
			led_pwm.red_led = PWM_LED_OFF;
		}
		else
		{
			HAL_TIM_PWM_Start(led_pwm.tim3, LED_BLUE_CHANNEL);
			led_pwm.red_led = PWM_LED_ON;
		}
	}
	else if (led == WHITE_LED)
	{
		__HAL_TIM_SET_COMPARE(led_pwm.tim3, LED_WHITE_CHANNEL, compare);

		if (compare == 0)
		{
			HAL_TIM_PWM_Stop(led_pwm.tim3, LED_WHITE_CHANNEL);
			led_pwm.red_led = PWM_LED_OFF;
		}
		else
		{
			HAL_TIM_PWM_Start(led_pwm.tim3, LED_WHITE_CHANNEL);
			led_pwm.red_led = PWM_LED_ON;
		}
	}




}

void led_pwm_all_off(void)
{
	//turn off led array
	timer_off(&htim7);

	HAL_TIM_PWM_Stop(led_pwm.tim3, LED_RED_CHANNEL);
	HAL_TIM_PWM_Stop(led_pwm.tim3, LED_GREEN_CHANNEL);
	HAL_TIM_PWM_Stop(led_pwm.tim3, LED_BLUE_CHANNEL);
	HAL_TIM_PWM_Stop(led_pwm.tim3, LED_WHITE_CHANNEL);

	led_pwm.red_led = PWM_LED_OFF;
	led_pwm.green_led = PWM_LED_OFF;
	led_pwm.blue_led = PWM_LED_OFF;
	led_pwm.white_led = PWM_LED_OFF;
}


led_output_t get_led_red(void)
{
	return led_pwm.red_led;
}


led_output_t get_led_green(void)
{
	return led_pwm.green_led;
}


led_output_t get_led_blue(void)
{
	return led_pwm.blue_led;
}


led_output_t get_led_white(void)
{
	return led_pwm.white_led;
}
