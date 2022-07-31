################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./lib/color_led/color_led.o 

C_DEPS += \
./lib/color_led/color_led.d 


# Each subdirectory must supply rules for building sources it contributes
lib/color_led/color_led.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led/color_led.c lib/color_led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/STM32L4xx_HAL_Driver/Inc" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/STM32L4xx_HAL_Driver/Inc/Legacy" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/CMSIS/Include" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/startup" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src/stm32_bloat" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/src/bsp" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver_mac/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-color_led

clean-lib-2f-color_led:
	-$(RM) ./lib/color_led/color_led.d ./lib/color_led/color_led.o ./lib/color_led/color_led.su

.PHONY: clean-lib-2f-color_led

