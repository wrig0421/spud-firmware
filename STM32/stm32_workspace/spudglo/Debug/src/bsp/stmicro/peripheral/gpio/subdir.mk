################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/peripheral/gpio/gpio_access_hal.c \
../src/bsp/stmicro/peripheral/gpio/gpio_config_hal.c 

OBJS += \
./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.o \
./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.o 

C_DEPS += \
./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.d \
./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/peripheral/gpio/%.o src/bsp/stmicro/peripheral/gpio/%.su src/bsp/stmicro/peripheral/gpio/%.cyclo: ../src/bsp/stmicro/peripheral/gpio/%.c src/bsp/stmicro/peripheral/gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/stmicro/peripheral/gpio/gpio_access_hal.c_includes.args"

clean: clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-gpio

clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-gpio:
	-$(RM) ./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.cyclo ./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.d ./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.o ./src/bsp/stmicro/peripheral/gpio/gpio_access_hal.su ./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.cyclo ./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.d ./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.o ./src/bsp/stmicro/peripheral/gpio/gpio_config_hal.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-gpio

