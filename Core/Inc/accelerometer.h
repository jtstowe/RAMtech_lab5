/*
 * accelerometer.h
 *
 *  Created on: Jul 7, 2025
 *      Author: Alex Riebe
 */

#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_

#include <stdint.h>
#include <stdbool.h>

void accelerometer_read_xyz(uint16_t *x, uint16_t *y, uint16_t *z);
bool accelerometer_flip();

#endif /* INC_ACCELEROMETER_H_ */
