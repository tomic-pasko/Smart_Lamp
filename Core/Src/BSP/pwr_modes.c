

/*********************************INCLUDES******************************************/
#include "BSP/pwr_modes.h"
#include "BSP/timers.h"
#include "BSP/led_pwm.h"
#include "usart.h"
#include "tim.h"

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/
//** SLEEP MODE **//
void pwr_modes_sleep_preparation(void)
{
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
}

void pwr_modes_enter_sleep(void)
{
  /* Suspend SysTick */
  HAL_SuspendTick();
  /* Enter Sleep Mode */
  HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  /* Resume SysTick */
  HAL_ResumeTick();

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  // MORA postojati odredena pauza kod budenja iz stop mode-a da se periferija tipa UART uspije postaviti prije nego se koristi
  HAL_Delay(20);

  /* "Hack" - problem sa overrunning-om */
  HAL_UART_Init(&huart1);
}


//** STOP MODE **//
void pwr_modes_stop_preparation(void)
{
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();

  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();

  /* Select HSI as system clock source after Wake Up from Stop mode */
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
}

void pwr_modes_enter_stop(void)
{
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Suspend SysTick */
  HAL_SuspendTick();
  /* Enter Stop Mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  /* Resume SysTick */
  HAL_ResumeTick();

  /* Clear Wake Up Flag */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

  /* Configures system clock after wake-up from STOP */
  SystemClock_Config();

  // MORA postojati odredena pauza kod budenja iz stop mode-a da se periferija tipa UART uspije postaviti prije nego se koristi
  HAL_Delay(20);

  /* "Hack" - problem sa overrunning-om */
  HAL_UART_Init(&huart1);
}


//** STANDBY MODE  **//
void pwr_modes_standby_preparation(void)
{
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* Enable Ultra low power mode */
  HAL_PWREx_EnableUltraLowPower();

  /* Enable the fast wake up from Ultra low power mode */
  HAL_PWREx_EnableFastWakeUp();

  /* Check and handle if the system was resumed from Standby mode */
  if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
	/* Clear Standby flag */
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
  }

  // MORA postojati odredena pauza kod budenja iz standby mode-a da se periferija tipa UART uspije postaviti prije nego se koristi
  HAL_Delay(20);
}


void pwr_modes_enter_standby_enable_wakeup_pin(void)
{
  timer_off(&htim6);
  timer_off(&htim7);
  HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  HAL_NVIC_DisableIRQ(TIM7_IRQn);
  HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);
  led_pwm_all_off();
  HAL_Delay(20);

  /* Disable all used wakeup sources: PWR_WAKEUP_PIN2 */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);

  /* Clear all related wakeup flags*/
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

  /* Enable WakeUp Pin PWR_WAKEUP_PIN2 connected to PC.13 */
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);

  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();

  while(1);
}
