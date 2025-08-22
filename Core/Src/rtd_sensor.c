#include "main.h"
#include <math.h>
#include "rtd_sensor.h"

extern ADC_HandleTypeDef hadc;


float rtd_read_temperature_f(void)
{
    // --- Constants ---
    const float VCC  = 3.3f;         // Excitation voltage
    const float RREF = 100.0f;       // Reference resistor (ohms)
    const float R0   = 100.0f;       // Pt100 resistance at 0 °C

    // IEC 60751 coefficients
    const float A =  3.9083e-3f;
    const float B = -5.775e-7f;
    const float C = -4.183e-12f;     // only for T < 0 °C

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

    // --- Step 1: Voltage -> Resistance ---
    if (voltage <= 0.0f || voltage >= VCC) {
        return -999.9f; // error: invalid voltage
    }
    float Rrtd = RREF * (VCC - voltage) / voltage;

    // --- Step 2: Resistance -> Temperature ---
    if (Rrtd >= R0) {
        // 0 to 850 °C: closed-form inverse
        float ratio = Rrtd / R0;
        float disc = (A * A) - (4.0f * B * (1.0f - ratio));
        if (disc < 0.0f) return -999.9f;
        return (-A + sqrtf(disc)) / (2.0f * B);
    } else {
        // Below 0 °C: use Newton-Raphson iteration
        float T = -50.0f; // initial guess
        for (int i = 0; i < 20; i++) {
            float f  = R0 * (1 + A*T + B*T*T + C*(T-100.0f)*T*T*T) - Rrtd;
            float df = R0 * (A + 2*B*T + 3*C*(T-100.0f)*T*T + C*T*T*T);
            T -= f / df; // returning temp in C
        }
        float temperatureInF = (T * 1.8f) + 32;
        return temperatureInF;
    }
}
