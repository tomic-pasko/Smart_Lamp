

/*********************************INCLUDES******************************************/
#include "BSP/max17048.h"
#include <math.h>

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/
static max17048_s max17048;

uint8_t vcell_msb = 0x02;
uint8_t vcell_lsb = 0x03;

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

void init_MAX17048(I2C_HandleTypeDef* i2c, uint8_t addr, uint32_t timeout_ms)
{
	max17048.i2c_comm = i2c;
	max17048.i2c_addr = addr;
	max17048.timeout_ms = timeout_ms;
}

void get_MAX17048_vcell_value(float* vcell_value)
{

	uint8_t received_data[2] = {0, 0};

	if (HAL_I2C_Master_Transmit(max17048.i2c_comm, max17048.i2c_addr << 1, &vcell_msb, 1, max17048.timeout_ms) == HAL_OK)
	{
		HAL_I2C_Master_Receive(max17048.i2c_comm, max17048.i2c_addr << 1, &received_data[1], 1, max17048.timeout_ms);
	}

	if (HAL_I2C_Master_Transmit(max17048.i2c_comm, max17048.i2c_addr << 1, &vcell_lsb, 1, max17048.timeout_ms) == HAL_OK)
	{
		HAL_I2C_Master_Receive(max17048.i2c_comm, max17048.i2c_addr << 1, &received_data[0], 1, max17048.timeout_ms);
	}

	*vcell_value = ((received_data[1] << 8) | (received_data[0])) * 78.125 * pow(10, -6);


}
