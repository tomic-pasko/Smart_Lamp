#ifndef MAX17048_H_
#define MAX17048_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"  // STM32L0 - Nucleo

/**********************************DEFINES******************************************/
// I2C adresa
#define MAX17048_I2C_ADDR 0x36

/*********************************STRUCTURES****************************************/
typedef struct {
	I2C_HandleTypeDef* i2c_comm;   // Pointer to structure for I2C communication
	uint8_t i2c_addr;              // I2C address
	uint32_t timeout_ms;           // Timeout for blocking function
}max17048_s;

/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/
void init_MAX17048(I2C_HandleTypeDef* i2c, uint8_t addr, uint32_t timeout_ms);
void get_MAX17048_vcell_value(float* soc_value);

#endif /* MAX17048_H_ */
