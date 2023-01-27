#ifndef PWR_MODES_H_
#define PWR_MODES_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"


/**********************************DEFINES******************************************/


/*********************************STRUCTURES****************************************/


/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
//** SLEEP MODE **//
void pwr_modes_sleep_preparation(void);
void pwr_modes_enter_sleep(void);

//** STOP MODE **//
void pwr_modes_stop_preparation(void);
void pwr_modes_enter_stop(void);
void SystemClock_Config(void);

//** STANDBY MODE  **//
void pwr_modes_standby_preparation(void);
void pwr_modes_enter_standby_enable_wakeup_pin(void);


#endif /* PWR_MODES_H_ */
