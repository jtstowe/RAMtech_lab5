################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LiquidCrystal_Shield.c \
../Core/Src/accelerometer.c \
../Core/Src/button_input.c \
../Core/Src/custom_chars.c \
../Core/Src/lcd_i2c.c \
../Core/Src/main.c \
../Core/Src/rtd_sensor.c \
../Core/Src/signal_input.c \
../Core/Src/stm32l1xx_hal_msp.c \
../Core/Src/stm32l1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l1xx.c \
../Core/Src/tilt.c 

OBJS += \
./Core/Src/LiquidCrystal_Shield.o \
./Core/Src/accelerometer.o \
./Core/Src/button_input.o \
./Core/Src/custom_chars.o \
./Core/Src/lcd_i2c.o \
./Core/Src/main.o \
./Core/Src/rtd_sensor.o \
./Core/Src/signal_input.o \
./Core/Src/stm32l1xx_hal_msp.o \
./Core/Src/stm32l1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l1xx.o \
./Core/Src/tilt.o 

C_DEPS += \
./Core/Src/LiquidCrystal_Shield.d \
./Core/Src/accelerometer.d \
./Core/Src/button_input.d \
./Core/Src/custom_chars.d \
./Core/Src/lcd_i2c.d \
./Core/Src/main.d \
./Core/Src/rtd_sensor.d \
./Core/Src/signal_input.d \
./Core/Src/stm32l1xx_hal_msp.d \
./Core/Src/stm32l1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l1xx.d \
./Core/Src/tilt.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LiquidCrystal_Shield.cyclo ./Core/Src/LiquidCrystal_Shield.d ./Core/Src/LiquidCrystal_Shield.o ./Core/Src/LiquidCrystal_Shield.su ./Core/Src/accelerometer.cyclo ./Core/Src/accelerometer.d ./Core/Src/accelerometer.o ./Core/Src/accelerometer.su ./Core/Src/button_input.cyclo ./Core/Src/button_input.d ./Core/Src/button_input.o ./Core/Src/button_input.su ./Core/Src/custom_chars.cyclo ./Core/Src/custom_chars.d ./Core/Src/custom_chars.o ./Core/Src/custom_chars.su ./Core/Src/lcd_i2c.cyclo ./Core/Src/lcd_i2c.d ./Core/Src/lcd_i2c.o ./Core/Src/lcd_i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtd_sensor.cyclo ./Core/Src/rtd_sensor.d ./Core/Src/rtd_sensor.o ./Core/Src/rtd_sensor.su ./Core/Src/signal_input.cyclo ./Core/Src/signal_input.d ./Core/Src/signal_input.o ./Core/Src/signal_input.su ./Core/Src/stm32l1xx_hal_msp.cyclo ./Core/Src/stm32l1xx_hal_msp.d ./Core/Src/stm32l1xx_hal_msp.o ./Core/Src/stm32l1xx_hal_msp.su ./Core/Src/stm32l1xx_it.cyclo ./Core/Src/stm32l1xx_it.d ./Core/Src/stm32l1xx_it.o ./Core/Src/stm32l1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l1xx.cyclo ./Core/Src/system_stm32l1xx.d ./Core/Src/system_stm32l1xx.o ./Core/Src/system_stm32l1xx.su ./Core/Src/tilt.cyclo ./Core/Src/tilt.d ./Core/Src/tilt.o ./Core/Src/tilt.su

.PHONY: clean-Core-2f-Src

