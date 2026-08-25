#include "HAL_stubs.h"

uint32_t mock_tick = 0;

HAL_StatusTypeDef HAL_Init(void){ return HAL_OK; }
void HAL_IncTick(void){}
void HAL_Delay(uint32_t Delay){ mock_tick += Delay; }
uint32_t HAL_GetTick(void){ return mock_tick; }
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){ (void)GPIOx; (void)GPIO_Pin; (void)PinState; }
