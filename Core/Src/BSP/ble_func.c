

/*********************************INCLUDES******************************************/
#include "BSP/ble_func.h"
#include "BSP/led_gpio.h"
#include "BSP/max17048.h"
#include "BSP/ble.h"
#include "BSP/timers.h"

#include <stdio.h>
#include <string.h>

#include "tim.h"

#include "BSP/led_pwm.h"
#include "rtc.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
volatile led_t led_array[5] = {0};

volatile uint8_t led_alarm[4] = {0};

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

uint8_t is_phone_connected()
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == MOBILE_CONNECTED)
	{
		return MOBILE_CONNECTED;
	}
	else
		return MOBILE_NOT_CONNECTED;
}

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
	// if PWM not used uncomment line below
	// led_gpio_all_off();

	// if PWM not used comment line below
	led_pwm_all_off();
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

void one_pwm_led_on_fp(uint8_t* payload)
{
	led_pwm_set(payload[0], payload[1]);
}


void rtc_set_time_fp(uint8_t* payload)
{
	RTC_TimeTypeDef my_time = {0};

	my_time.Hours = payload[0];
	my_time.Minutes = payload[1];
	my_time.Seconds = 0;

	if (HAL_RTC_SetTime(&hrtc, &my_time, RTC_FORMAT_BIN) == HAL_OK)
	{
		// define text we want to send to mobile phone
		char vcell_tekst[40] = {0};
		sprintf(&vcell_tekst[0], "RTC vrijeme: %d:%d\r\n", payload[0], payload[1]);

		// Send to mobile phone
		HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);

	}


}

void rtc_set_alarm_a_b_fp(uint8_t* payload)
{
	RTC_AlarmTypeDef my_alarm_A = {0};
	RTC_AlarmTypeDef my_alarm_B = {0};

	my_alarm_A.AlarmTime.Hours = payload[DATA_1];
	my_alarm_A.AlarmTime.Minutes = payload[DATA_2];
	my_alarm_A.AlarmTime.Seconds = 0;

	my_alarm_A.Alarm = RTC_ALARM_A;

	my_alarm_A.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;

	my_alarm_B.AlarmTime.Hours = payload[DATA_3];
	my_alarm_B.AlarmTime.Minutes = payload[DATA_4];
	my_alarm_B.AlarmTime.Seconds = 0;

	my_alarm_B.Alarm = RTC_ALARM_B;

	my_alarm_B.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;

	if (HAL_RTC_SetAlarm_IT(&hrtc, &my_alarm_A, RTC_FORMAT_BIN) == HAL_OK && HAL_RTC_SetAlarm_IT(&hrtc, &my_alarm_B, RTC_FORMAT_BIN) == HAL_OK)
	{
		// define text we want to send to mobile phone
		char vcell_tekst[40] = {0};
		sprintf(&vcell_tekst[0], "alarmA: %d:%d, alarmB: %d:%d\r\n", payload[DATA_1], payload[DATA_2], payload[DATA_3], payload[DATA_4]);

		// Send to mobile phone
		HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);
	}

}

void rtc_set_led_fp(uint8_t* payload)
{
	led_alarm[DATA_1] = payload[DATA_1];
	led_alarm[DATA_2] = payload[DATA_2];
	led_alarm[DATA_3] = payload[DATA_3];
	led_alarm[DATA_4] = payload[DATA_4];

	// define text we want to send to mobile phone
	char vcell_tekst[40] = {0};
	sprintf(&vcell_tekst[0], "--LED-ice za RTC postavljene--\r\n");

	// Send to mobile phone
	HAL_UART_Transmit(ble.uart, (uint8_t*) vcell_tekst, strlen(vcell_tekst), ble.timeout_ms);
}
