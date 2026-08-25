#ifndef HAL_STUBS_H
#define HAL_STUBS_H

#include <stdint.h>

#define GPIOA            ((GPIO_TypeDef *) 0x40020000)
#define GPIOC            ((GPIO_TypeDef *) 0x40020800)
#define GPIO_PIN_4       ((uint16_t)0x0010)
#define GPIO_PIN_5       ((uint16_t)0x0020)
#define GPIO_PIN_6       ((uint16_t)0x0040)
#define GPIO_PIN_7       ((uint16_t)0x0080)
#define GPIO_PIN_13      ((uint16_t)0x2000)

typedef enum
{
    HAL_OK
} HAL_StatusTypeDef;

typedef enum
{
    GPIO_PIN_RESET,
    GPIO_PIN_SET
} GPIO_PinState;

typedef struct
{
    uint32_t MODER;
} GPIO_TypeDef;

extern uint32_t mock_tick;

HAL_StatusTypeDef HAL_Init(void);
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

#endif // HAL_STUBS_H
