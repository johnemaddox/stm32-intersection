#include "leds.h"
#include "stm32g0xx_hal.h"

void leds_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SR_RCLK_PIN | SR_SRCLK_PIN | SR_SER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SR_GPIO_PORT, &GPIO_InitStruct);

    // Initial state: clocks low, SER low
    HAL_GPIO_WritePin(SR_GPIO_PORT, SR_RCLK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SR_GPIO_PORT, SR_SRCLK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SR_GPIO_PORT, SR_SER_PIN, GPIO_PIN_RESET);
}

void leds_write(uint8_t value) {
    // Write 8 bits MSB first
    for (int i = 7; i >= 0; i--) {
        uint8_t bit = (value >> i) & 0x01;
        HAL_GPIO_WritePin(SR_GPIO_PORT, SR_SER_PIN, bit ? GPIO_PIN_SET : GPIO_PIN_RESET);

        // Pulse shift clock (SRCLK)
        HAL_GPIO_WritePin(SR_GPIO_PORT, SR_SRCLK_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SR_GPIO_PORT, SR_SRCLK_PIN, GPIO_PIN_SET);
    }

    // Pulse storage clock (RCLK) to update outputs
    HAL_GPIO_WritePin(SR_GPIO_PORT, SR_RCLK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SR_GPIO_PORT, SR_RCLK_PIN, GPIO_PIN_SET);
}
