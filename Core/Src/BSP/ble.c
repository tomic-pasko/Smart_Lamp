

/*********************************INCLUDES******************************************/
#include "BSP/ble.h"
#include <stdio.h>
#include "string.h"

#include "BSP/led_gpio.h"
#include "BSP/max17048.h"
#include "BSP/ble_func.h"


/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
ble_s ble;

static ble_rx_all_s ble_rx_all;
/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/


void ble_init(UART_HandleTypeDef* uart, uint8_t rx_header_size, uint32_t timeout_ms)
{
	ble.uart = uart;
	ble.rx_head_size = rx_header_size;
	ble.timeout_ms = timeout_ms;
	ble.init_flag = 1;

	ble_rx_all.one_led_on.cmd_id = LED_CMD_ID;
	ble_rx_all.one_led_on.msg_id = ONE_LED_MSG_ID;
	ble_rx_all.one_led_on.func_p = one_led_on_fp;

	ble_rx_all.vcell.cmd_id = BATT_CMD_ID;
	ble_rx_all.vcell.msg_id = BATT_MSG_ID;
	ble_rx_all.vcell.func_p = vcell_fp;

	ble_rx_all.all_led_off.cmd_id = LED_CMD_ID;
	ble_rx_all.all_led_off.msg_id = ALL_LED_OFF_MSG_ID;
	ble_rx_all.all_led_off.func_p = all_led_off_fp;

	ble_rx_all.two_led_on.cmd_id = LED_CMD_ID;
	ble_rx_all.two_led_on.msg_id = TWO_LED_MSG_ID;
	ble_rx_all.two_led_on.func_p = two_led_on_fp;

	ble_rx_all.vcell_timer.cmd_id = BATT_CMD_ID;
	ble_rx_all.vcell_timer.msg_id = BATT_TIMER_MSG_ID;
	ble_rx_all.vcell_timer.func_p = vcell_timer_fp;

	ble_rx_all.led_array.cmd_id = LED_CMD_ID;
	ble_rx_all.led_array.msg_id = TIMER_LED_MSG_ID;
	ble_rx_all.led_array.func_p = led_array_fp;

}


HAL_StatusTypeDef ble_handler()
{
	if (ble.init_flag != 1)
	{
		return HAL_ERROR;
	}

	uint8_t rx_header[BLE_MAX_EXPECTED_RX_HEADER_BYTES] = {0};

	if (HAL_UART_Receive(ble.uart, &rx_header[0], sizeof(rx_header), ble.timeout_ms) == HAL_OK)
	{

		uint8_t cmd_id = rx_header[CMD_ID];
		uint16_t msg_id = (rx_header[MSG_ID_H] << 8) | rx_header[MSG_ID_L];
		uint8_t len = rx_header[MSG_LEN] + 1;

		uint8_t rx_payload[6] = {0};

		if (HAL_UART_Receive(ble.uart, &rx_payload[0], len, ble.timeout_ms) == HAL_OK)
		{
			ble_rx_s* p = &ble_rx_all.one_led_on;

			for (uint8_t i = 0; i < (sizeof(ble_rx_all_s) / sizeof(ble_rx_s)); i++)
			{
				if((p->cmd_id == cmd_id) && (p->msg_id == msg_id))
				{
					p->func_p(&rx_payload[0]);
					break;
				}

				p++;
			}

		}

		return HAL_OK;

	}

	return HAL_ERROR;

}


