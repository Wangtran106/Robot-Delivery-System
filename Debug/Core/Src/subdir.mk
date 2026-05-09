################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HCSR04.c \
../Core/Src/MPU6050.c \
../Core/Src/bluetooth_receiver.c \
../Core/Src/bluetooth_transmitter.c \
../Core/Src/encoder.c \
../Core/Src/global.c \
../Core/Src/gpio.c \
../Core/Src/hx711.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/navigation.c \
../Core/Src/path_planning.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/HCSR04.o \
./Core/Src/MPU6050.o \
./Core/Src/bluetooth_receiver.o \
./Core/Src/bluetooth_transmitter.o \
./Core/Src/encoder.o \
./Core/Src/global.o \
./Core/Src/gpio.o \
./Core/Src/hx711.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/navigation.o \
./Core/Src/path_planning.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/HCSR04.d \
./Core/Src/MPU6050.d \
./Core/Src/bluetooth_receiver.d \
./Core/Src/bluetooth_transmitter.d \
./Core/Src/encoder.d \
./Core/Src/global.d \
./Core/Src/gpio.d \
./Core/Src/hx711.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/navigation.d \
./Core/Src/path_planning.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/HCSR04.cyclo ./Core/Src/HCSR04.d ./Core/Src/HCSR04.o ./Core/Src/HCSR04.su ./Core/Src/MPU6050.cyclo ./Core/Src/MPU6050.d ./Core/Src/MPU6050.o ./Core/Src/MPU6050.su ./Core/Src/bluetooth_receiver.cyclo ./Core/Src/bluetooth_receiver.d ./Core/Src/bluetooth_receiver.o ./Core/Src/bluetooth_receiver.su ./Core/Src/bluetooth_transmitter.cyclo ./Core/Src/bluetooth_transmitter.d ./Core/Src/bluetooth_transmitter.o ./Core/Src/bluetooth_transmitter.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/global.cyclo ./Core/Src/global.d ./Core/Src/global.o ./Core/Src/global.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/hx711.cyclo ./Core/Src/hx711.d ./Core/Src/hx711.o ./Core/Src/hx711.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/navigation.cyclo ./Core/Src/navigation.d ./Core/Src/navigation.o ./Core/Src/navigation.su ./Core/Src/path_planning.cyclo ./Core/Src/path_planning.d ./Core/Src/path_planning.o ./Core/Src/path_planning.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

