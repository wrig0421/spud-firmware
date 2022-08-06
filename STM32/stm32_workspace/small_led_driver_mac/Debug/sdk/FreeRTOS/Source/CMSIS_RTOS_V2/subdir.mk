################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c 

OBJS += \
./sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.o 

C_DEPS += \
./sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/FreeRTOS/Source/CMSIS_RTOS_V2/%.o sdk/FreeRTOS/Source/CMSIS_RTOS_V2/%.su: ../sdk/FreeRTOS/Source/CMSIS_RTOS_V2/%.c sdk/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/STM32L4xx_HAL_Driver/Inc" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/CMSIS/Include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/startup" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src/stm32_bloat" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src/bsp" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sdk-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2

clean-sdk-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2:
	-$(RM) ./sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.d ./sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.o ./sdk/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2

