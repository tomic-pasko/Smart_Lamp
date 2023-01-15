#ifndef BLE_FUNC_H_
#define BLE_FUNC_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"  // STM32L0 - Nucleo
#include "BSP/led_gpio.h"

/**********************************DEFINES******************************************/
extern volatile led_t led_array[4];

/*********************************STRUCTURES****************************************/
typedef void (*fun_ptr_t)(uint8_t* payload);

typedef struct
{
	uint8_t cmd_id;
	uint16_t msg_id;
	fun_ptr_t func_p;
}ble_rx_s;

typedef struct
{
	ble_rx_s one_led_on;
	ble_rx_s vcell;
	ble_rx_s all_led_off;
	ble_rx_s two_led_on;
	ble_rx_s vcell_timer;
	ble_rx_s led_array;

}ble_rx_all_s;

/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
void one_led_on_fp(uint8_t* payload);

void vcell_fp(uint8_t* payload);

void all_led_off_fp(uint8_t* payload);

void two_led_on_fp(uint8_t* payload);

void vcell_timer_fp(uint8_t* payload);

void led_array_fp(uint8_t* payload);

#endif /* BLE_FUNC_H_ */
