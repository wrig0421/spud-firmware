################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/numbers.c \
../src/task_create.c \
../src/task_dma_transfer.c 

OBJS += \
./src/main.o \
./src/numbers.o \
./src/task_create.o \
./src/task_dma_transfer.o 

C_DEPS += \
./src/main.d \
./src/numbers.d \
./src/task_create.d \
./src/task_dma_transfer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/task" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/current_monitor" -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../sdk/CMSIS/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v1 -I../src/bsp/board_specific/board_init_spud_glo_v2 -I../src/bsp/board_specific/board_init_spud_glo_v3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/main.d ./src/main.o ./src/main.su ./src/numbers.d ./src/numbers.o ./src/numbers.su ./src/task_create.d ./src/task_create.o ./src/task_create.su ./src/task_dma_transfer.d ./src/task_dma_transfer.o ./src/task_dma_transfer.su

.PHONY: clean-src

