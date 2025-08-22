#include "stm32l1xx_hal.h"
#include <stdbool.h>

// Example: using PA0 as the tilt input pin
#define TILT_GPIO_PORT GPIOA
#define TILT_PIN       GPIO_PIN_10
#define DEBOUNCE_MS    10

static bool last_tilt_state = false;

// Call this in main() before using detect_tilt()
void tilt_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA (adjust for your pin)

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = TILT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // Internal pull-up
    HAL_GPIO_Init(TILT_GPIO_PORT, &GPIO_InitStruct);
}

// Returns 1 if tilted, 0 if not tilted
bool detect_tilt(void) {

    // 1. Debounce: take multiple samples
    bool stable_state = (HAL_GPIO_ReadPin(TILT_GPIO_PORT, TILT_PIN) == GPIO_PIN_RESET);
    HAL_Delay(DEBOUNCE_MS);
    bool confirm_state = (HAL_GPIO_ReadPin(TILT_GPIO_PORT, TILT_PIN) == GPIO_PIN_RESET);

    // 2. Update last_tilt_state only if both samples match
    if (stable_state == confirm_state) {
        last_tilt_state = stable_state;
    }

    return !last_tilt_state;
}
