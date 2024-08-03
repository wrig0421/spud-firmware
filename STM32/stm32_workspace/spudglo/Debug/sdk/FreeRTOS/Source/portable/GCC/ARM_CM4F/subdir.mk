################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.su sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.cyclo: ../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c_includes.args"

clean: clean-sdk-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-sdk-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

