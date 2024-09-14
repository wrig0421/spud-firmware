################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdk/FreeRTOS/Source/convenience/free_rtos_convenience.c 

OBJS += \
./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.o 

C_DEPS += \
./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/FreeRTOS/Source/convenience/%.o sdk/FreeRTOS/Source/convenience/%.su sdk/FreeRTOS/Source/convenience/%.cyclo: ../sdk/FreeRTOS/Source/convenience/%.c sdk/FreeRTOS/Source/convenience/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"sdk/FreeRTOS/Source/convenience/free_rtos_convenience.c_includes.args"

clean: clean-sdk-2f-FreeRTOS-2f-Source-2f-convenience

clean-sdk-2f-FreeRTOS-2f-Source-2f-convenience:
	-$(RM) ./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.cyclo ./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.d ./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.o ./sdk/FreeRTOS/Source/convenience/free_rtos_convenience.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source-2f-convenience

