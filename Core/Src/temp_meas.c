#include "main.h"
#include <math.h>
#include <temp_meas.h>

extern ADC_HandleTypeDef hadc;


float rtd_read_temperature_f(void)
{
    // --- Constants ---
	const float VCC =  3.3f;

    const float A =  0.0026f;
    const float B = -0.52f;
    const float C = -13.5f;     // only for T < 0 °C

	uint32_t sum = 0;

    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

    // Take 10 samples
    for (int i = 0; i < 10; i++)
    {
        uint16_t raw = HAL_ADC_GetValue(&hadc);
        sum += raw;
        HAL_Delay(2); // small delay to avoid reading the exact same sample
    }

    // Calculate average raw ADC value
    float avg_raw = sum / 10.0f;

    // Convert to voltage (assuming 3.3V ref and 12-bit ADC)
    float voltage = (VCC * avg_raw) / 4095.0f;

    // Calculate temperature
    float temperatureInC = A*pow(voltage,2) + B*voltage + C;
    float temperatureInF = (temperatureInC * 1.8f) + 32;

    return temperatureInF;
}
