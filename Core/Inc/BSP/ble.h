#ifndef BLE_H_
#define BLE_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"  // STM32L0 - Nucleo
#include "BSP/led_gpio.h"
/**********************************DEFINES******************************************/
#define BLE_MAX_EXPECTED_RX_HEADER_BYTES 4
#define TIMEOUT_MS 100

#define BLE_STATE_PORT GPIOA
#define BLE_STATE_PIN GPIO_PIN_11

#define CMD_ID   0
#define MSG_ID_H 1
#define MSG_ID_L 2
#define MSG_LEN  3

//Cmd ID
#define LED_CMD_ID    0xAF
#define BATT_CMD_ID   0xBC

//Msg ID
#define ONE_PWM_LED_MSG_ID       0x0601
#define TWO_PWM_LED_TIMER_MSG_ID 0x0603

#define ONE_LED_MSG_ID           0x0701
#define TWO_LED_MSG_ID           0x0702
#define TIMER_LED_MSG_ID         0x0703
#define ALL_LED_OFF_MSG_ID       0x0704

#define BATT_MSG_ID              0x0801
#define BATT_TIMER_MSG_ID        0x0802

#define RTC_MSG_ID               0x0A01
#define RTC_ALARM_A_B_MSG_ID     0x0A02
#define RTC_LED_MSG_ID           0x0A03

/*********************************STRUCTURES****************************************/
typedef struct
{
	UART_HandleTypeDef* uart;
	uint8_t rx_head_size;
	uint32_t timeout_ms;
	uint8_t init_flag;
}ble_s;


/******************************EXTERN VARIABLES*************************************/
extern ble_s ble;

/****************************FUNCTION PROTOTYPES************************************/
void ble_init(UART_HandleTypeDef* uart, uint8_t rx_header_size, uint32_t timeout_ms);

HAL_StatusTypeDef ble_handler();

#endif /* BLE_H_ */
