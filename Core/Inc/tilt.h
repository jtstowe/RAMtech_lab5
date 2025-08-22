#ifndef TILT_H
#define TILT_H

#include "stm32l1xx_hal.h"
#include <stdbool.h>

// Initialize the tilt switch input
void tilt_init(void);

// Check if device is tilted (returns 1 if tilted, 0 if not)
// Debouncing is handled internally
bool detect_tilt(void);

#endif // TILT_H
