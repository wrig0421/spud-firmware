################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_button_press.c \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_led_ctrl.c \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_mn_wild.c \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_pkt_process.c \
/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_uart.c 

OBJS += \
./common/lib/task/task_button_press.o \
./common/lib/task/task_led_ctrl.o \
./common/lib/task/task_mn_wild.o \
./common/lib/task/task_pkt_process.o \
./common/lib/task/task_uart.o 

C_DEPS += \
./common/lib/task/task_button_press.d \
./common/lib/task/task_led_ctrl.d \
./common/lib/task/task_mn_wild.d \
./common/lib/task/task_pkt_process.d \
./common/lib/task/task_uart.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/task/task_button_press.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_button_press.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/lib/task/task_led_ctrl.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_led_ctrl.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/lib/task/task_mn_wild.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_mn_wild.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/lib/task/task_pkt_process.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_pkt_process.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/lib/task/task_uart.o: /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task/task_uart.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-lib-2f-task

clean-common-2f-lib-2f-task:
	-$(RM) ./common/lib/task/task_button_press.d ./common/lib/task/task_button_press.o ./common/lib/task/task_button_press.su ./common/lib/task/task_led_ctrl.d ./common/lib/task/task_led_ctrl.o ./common/lib/task/task_led_ctrl.su ./common/lib/task/task_mn_wild.d ./common/lib/task/task_mn_wild.o ./common/lib/task/task_mn_wild.su ./common/lib/task/task_pkt_process.d ./common/lib/task/task_pkt_process.o ./common/lib/task/task_pkt_process.su ./common/lib/task/task_uart.d ./common/lib/task/task_uart.o ./common/lib/task/task_uart.su

.PHONY: clean-common-2f-lib-2f-task
