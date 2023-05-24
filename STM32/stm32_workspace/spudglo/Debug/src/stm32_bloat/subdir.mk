################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
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
src/stm32_bloat/%.o src/stm32_bloat/%.su src/stm32_bloat/%.cyclo: ../src/stm32_bloat/%.c src/stm32_bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/queue" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/color_led" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/animate_led" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/task" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/current_monitor" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/semaphore" -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v1 -I../src/bsp/board_specific/board_init_spud_glo_v2 -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-stm32_bloat

clean-src-2f-stm32_bloat:
	-$(RM) ./src/stm32_bloat/stm32l4xx_hal_msp.cyclo ./src/stm32_bloat/stm32l4xx_hal_msp.d ./src/stm32_bloat/stm32l4xx_hal_msp.o ./src/stm32_bloat/stm32l4xx_hal_msp.su ./src/stm32_bloat/stm32l4xx_it.cyclo ./src/stm32_bloat/stm32l4xx_it.d ./src/stm32_bloat/stm32l4xx_it.o ./src/stm32_bloat/stm32l4xx_it.su ./src/stm32_bloat/syscalls.cyclo ./src/stm32_bloat/syscalls.d ./src/stm32_bloat/syscalls.o ./src/stm32_bloat/syscalls.su ./src/stm32_bloat/sysmem.cyclo ./src/stm32_bloat/sysmem.d ./src/stm32_bloat/sysmem.o ./src/stm32_bloat/sysmem.su ./src/stm32_bloat/system_stm32l4xx.cyclo ./src/stm32_bloat/system_stm32l4xx.d ./src/stm32_bloat/system_stm32l4xx.o ./src/stm32_bloat/system_stm32l4xx.su

.PHONY: clean-src-2f-stm32_bloat
