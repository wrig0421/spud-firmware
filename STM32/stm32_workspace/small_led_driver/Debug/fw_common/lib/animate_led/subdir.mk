################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led/animate_led.c 

OBJS += \
./fw_common/lib/animate_led/animate_led.o 

C_DEPS += \
./fw_common/lib/animate_led/animate_led.d 


# Each subdirectory must supply rules for building sources it contributes
fw_common/lib/animate_led/animate_led.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led/animate_led.c fw_common/lib/animate_led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/bsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-fw_common-2f-lib-2f-animate_led

clean-fw_common-2f-lib-2f-animate_led:
	-$(RM) ./fw_common/lib/animate_led/animate_led.d ./fw_common/lib/animate_led/animate_led.o ./fw_common/lib/animate_led/animate_led.su

.PHONY: clean-fw_common-2f-lib-2f-animate_led
