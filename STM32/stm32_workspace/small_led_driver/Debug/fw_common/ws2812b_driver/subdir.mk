################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver/ws2812b.c 

OBJS += \
./fw_common/ws2812b_driver/ws2812b.o 

C_DEPS += \
./fw_common/ws2812b_driver/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
fw_common/ws2812b_driver/ws2812b.o: C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver/ws2812b.c fw_common/ws2812b_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/bsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fw_common/ws2812b_driver/ws2812b.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

