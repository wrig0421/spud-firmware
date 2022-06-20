################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/stm32_bloat/stm32l4xx_hal_msp.c \
../src/stm32_bloat/stm32l4xx_it.c \
../src/stm32_bloat/syscalls.c \
../src/stm32_bloat/sysmem.c \
../src/stm32_bloat/system_stm32l4xx.c 

OBJS += \
./src/stm32_bloat/stm32l4xx_hal_msp.o \
./src/stm32_bloat/stm32l4xx_it.o \
./src/stm32_bloat/syscalls.o \
./src/stm32_bloat/sysmem.o \
./src/stm32_bloat/system_stm32l4xx.o 

C_DEPS += \
./src/stm32_bloat/stm32l4xx_hal_msp.d \
./src/stm32_bloat/stm32l4xx_it.d \
./src/stm32_bloat/syscalls.d \
./src/stm32_bloat/sysmem.d \
./src/stm32_bloat/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/stm32_bloat/stm32l4xx_hal_msp.o: ../src/stm32_bloat/stm32l4xx_hal_msp.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32_bloat/stm32l4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32_bloat/stm32l4xx_it.o: ../src/stm32_bloat/stm32l4xx_it.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32_bloat/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32_bloat/syscalls.o: ../src/stm32_bloat/syscalls.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32_bloat/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32_bloat/sysmem.o: ../src/stm32_bloat/sysmem.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32_bloat/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/stm32_bloat/system_stm32l4xx.o: ../src/stm32_bloat/system_stm32l4xx.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/STM32l4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Device/ST/STM32L4xx/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/sdk/CMSIS/Include" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/startup" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/small_led_driver/src/stm32_bloat" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/Users/splat/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/stm32_bloat/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

