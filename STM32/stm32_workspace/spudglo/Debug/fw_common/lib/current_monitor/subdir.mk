################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/current_monitor/current_monitor.c 

OBJS += \
./fw_common/lib/current_monitor/current_monitor.o 

C_DEPS += \
./fw_common/lib/current_monitor/current_monitor.d 


# Each subdirectory must supply rules for building sources it contributes
fw_common/lib/current_monitor/current_monitor.o: /Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/current_monitor/current_monitor.c fw_common/lib/current_monitor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/queue" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/color_led" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/animate_led" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/task" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/current_monitor" -I"/Users/srw/Documents/GitHub/spud-firmware/STM32/stm32_workspace/fw_common/lib/semaphore" -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-fw_common-2f-lib-2f-current_monitor

clean-fw_common-2f-lib-2f-current_monitor:
	-$(RM) ./fw_common/lib/current_monitor/current_monitor.cyclo ./fw_common/lib/current_monitor/current_monitor.d ./fw_common/lib/current_monitor/current_monitor.o ./fw_common/lib/current_monitor/current_monitor.su

.PHONY: clean-fw_common-2f-lib-2f-current_monitor

