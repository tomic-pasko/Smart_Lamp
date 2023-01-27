#ifndef LED_PWM_H_
#define LED_PWM_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"  // STM32L1 - Nucleo

/**********************************DEFINES******************************************/
#define LED_RED_CHANNEL TIM_CHANNEL_1
#define LED_GREEN_CHANNEL TIM_CHANNEL_2
#define LED_BLUE_CHANNEL TIM_CHANNEL_3
#define LED_WHITE_CHANNEL TIM_CHANNEL_4

/*********************************STRUCTURES****************************************/
typedef enum
{
	RED_LED = 1,
	GREEN_LED = 2,
	BLUE_LED = 3,
	WHITE_LED = 4,
}led_pwm_t;

typedef enum
{
	PWM_LED_OFF,
	PWM_LED_ON,
}led_output_t;

typedef struct
{
	TIM_HandleTypeDef* tim3;
	uint16_t count;
	uint8_t init_flag;
	led_output_t red_led;
	led_output_t green_led;
	led_output_t blue_led;
	led_output_t white_led;
}led_pwm_s;

/******************************EXTERN VARIABLES*************************************/
extern led_pwm_s led_pwm;

/****************************FUNCTION PROTOTYPES************************************/
void led_pwm_init(TIM_HandleTypeDef* tim, uint16_t max_counter_value);
void led_pwm_set(led_pwm_t led, uint8_t percentage_on);
void led_pwm_all_off(void);
led_output_t get_led_red(void);
led_output_t get_led_green(void);
led_output_t get_led_blue(void);
led_output_t get_led_white(void);

#endif /* LED_PWM_H_ */
