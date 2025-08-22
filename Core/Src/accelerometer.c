/*
 * accelerometer.c
 *
 *  Created on: Jul 7, 2025
 *      Author: Alex Riebe
 */


#include "main.h"
#include <stdbool.h>

extern ADC_HandleTypeDef hadc;

static uint16_t read_adc_channel(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {
        .Channel = channel,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_4CYCLES
    };

    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    uint16_t val = HAL_ADC_GetValue(&hadc);
    HAL_ADC_Stop(&hadc);
    return val;
}

void accelerometer_read_xyz(uint16_t *x, uint16_t *y, uint16_t *z)
{
    *x = read_adc_channel(ADC_CHANNEL_2);
    *y = read_adc_channel(ADC_CHANNEL_3);
    *z = read_adc_channel(ADC_CHANNEL_4);
}


bool accelerometer_flip()
{
	uint16_t ax, ay, az;
	float vz , gz;

	accelerometer_read_xyz(&ax, &ay, &az);

	vz = (3.3f * az) / 4095.0f;
	gz = (vz - 1.65f) / 0.33f;

	if (gz < -0.75f) {
	    return true;
	}
	else{
		return false;
	}
}














