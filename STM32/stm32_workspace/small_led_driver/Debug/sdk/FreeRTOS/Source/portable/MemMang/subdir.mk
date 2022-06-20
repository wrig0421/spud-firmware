################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdk/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./sdk/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./sdk/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/FreeRTOS/Source/portable/MemMang/heap_4.o: ../sdk/FreeRTOS/Source/portable/MemMang/heap_4.c sdk/FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sdk/FreeRTOS/Source/portable/MemMang/heap_4.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

