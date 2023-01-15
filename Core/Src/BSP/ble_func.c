

/*********************************INCLUDES******************************************/
#include "BSP/ble_func.h"
#include "BSP/led_gpio.h"
#include "BSP/max17048.h"
#include "BSP/ble.h"
#include "BSP/timers.h"

#include <stdio.h>
#include <string.h>

#include "tim.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
volatile led_t led_array[4] = {0};

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/
void one_led_on_fp(uint8_t* payload)
{
	led_gpio_set(payload[0], payload[1]);
}


void vcell_fp(uint8_t* payload)
{

	if (payload[0] == 0xAA)
	{
		float vcell_value = 0;

		get_MAX17048_vcell_value(&vcell_value);

		// define text we want to send to mobile phone
		char vcell_tekst[40] = {0};
		sprintf(&vcell_tekst[0], "Napon baterije je: %.2f V\r\n", vcell_value);

		// Send to mobile phone
		HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);

	}

}


void all_led_off_fp(uint8_t* payload)
{
	led_gpio_all_off();
}


void two_led_on_fp(uint8_t* payload)
{
	led_gpio_set(payload[0], payload[1]);
	led_gpio_set(payload[2], payload[3]);
}


void vcell_timer_fp(uint8_t* payload)
{
	char vcell_tekst[40] = {0};

	if (payload[0] == 0xAA)
	{

		if (is_timer_on(&htim6) == timer_stopped)
		{
			timer_on(&htim6, payload[1]);

			sprintf(&vcell_tekst[0], "--Periodicno slanje batt--\r\n");

			// Send to mobile phone
			HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);

		}
		else
		{
			// update of msg interval

			timer_off(&htim6);

			timer_on(&htim6, payload[1]);

			sprintf(&vcell_tekst[0], "--Periodicno slanje batt--\r\n");

			// Send to mobile phone
			HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);
		}

	}
	else if(payload[0] == 0xFF)
	{
		if (is_timer_on(&htim6) == timer_started)
		{
			timer_off(&htim6);
			sprintf(&vcell_tekst[0], "--Prekid periodickog slanja--\r\n");

			// Send to mobile phone
			HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);
		}
		else
		{
			// Periodic msg bat state already off
			sprintf(&vcell_tekst[0], "--Periodicno slanje vec prekinuto--\r\n");

			// Send to mobile phone
			HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);
		}
	}
}


void led_array_fp(uint8_t* payload)
{
	for (uint8_t i = 0; i < sizeof(led_array); i++)
	{
		led_array[i] = payload[i];
	}

	if (is_timer_on(&htim7) == timer_stopped)
	{
		timer_on(&htim7, payload[4]);


	}
	else
	{
		// update of led interval
		timer_off(&htim7);

		timer_on(&htim7, payload[4]);

	}

}
