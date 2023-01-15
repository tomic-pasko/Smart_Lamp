#ifndef TIMERS_H_
#define TIMERS_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"  // STM32L0 - Nucleo

/**********************************DEFINES******************************************/
#define TIM_FREQ 0.001 // timer freq in seconds

/*********************************STRUCTURES****************************************/
typedef enum
{
	timer_stopped = 0,
	timer_started = 1
}timer_status_t;

/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
void timer_on(TIM_HandleTypeDef* tim, uint8_t interval_s);
void timer_off(TIM_HandleTypeDef* tim);
timer_status_t is_timer_on(TIM_HandleTypeDef* tim);

#endif /* TIMERS_H_ */
