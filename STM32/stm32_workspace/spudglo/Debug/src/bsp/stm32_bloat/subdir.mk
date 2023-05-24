################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stm32_bloat/stm32l4xx_hal_msp.c \
../src/bsp/stm32_bloat/stm32l4xx_it.c \
../src/bsp/stm32_bloat/syscalls.c \
../src/bsp/stm32_bloat/sysmem.c \
../src/bsp/stm32_bloat/system_stm32l4xx.c 

OBJS += \
./src/bsp/stm32_bloat/stm32l4xx_hal_msp.o \
./src/bsp/stm32_bloat/stm32l4xx_it.o \
./src/bsp/stm32_bloat/syscalls.o \
./src/bsp/stm32_bloat/sysmem.o \
./src/bsp/stm32_bloat/system_stm32l4xx.o 

C_DEPS += \
./src/bsp/stm32_bloat/stm32l4xx_hal_msp.d \
./src/bsp/stm32_bloat/stm32l4xx_it.d \
./src/bsp/stm32_bloat/syscalls.d \
./src/bsp/stm32_bloat/sysmem.d \
./src/bsp/stm32_bloat/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stm32_bloat/%.o src/bsp/stm32_bloat/%.su: ../src/bsp/stm32_bloat/%.c src/bsp/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-bsp-2f-stm32_bloat

clean-src-2f-bsp-2f-stm32_bloat:
	-$(RM) ./src/bsp/stm32_bloat/stm32l4xx_hal_msp.d ./src/bsp/stm32_bloat/stm32l4xx_hal_msp.o ./src/bsp/stm32_bloat/stm32l4xx_hal_msp.su ./src/bsp/stm32_bloat/stm32l4xx_it.d ./src/bsp/stm32_bloat/stm32l4xx_it.o ./src/bsp/stm32_bloat/stm32l4xx_it.su ./src/bsp/stm32_bloat/syscalls.d ./src/bsp/stm32_bloat/syscalls.o ./src/bsp/stm32_bloat/syscalls.su ./src/bsp/stm32_bloat/sysmem.d ./src/bsp/stm32_bloat/sysmem.o ./src/bsp/stm32_bloat/sysmem.su ./src/bsp/stm32_bloat/system_stm32l4xx.d ./src/bsp/stm32_bloat/system_stm32l4xx.o ./src/bsp/stm32_bloat/system_stm32l4xx.su

.PHONY: clean-src-2f-bsp-2f-stm32_bloat

