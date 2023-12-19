################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sdk/FreeRTOS/Source/croutine.c \
../sdk/FreeRTOS/Source/event_groups.c \
../sdk/FreeRTOS/Source/list.c \
../sdk/FreeRTOS/Source/queue.c \
../sdk/FreeRTOS/Source/stream_buffer.c \
../sdk/FreeRTOS/Source/tasks.c \
../sdk/FreeRTOS/Source/timers.c 

OBJS += \
./sdk/FreeRTOS/Source/croutine.o \
./sdk/FreeRTOS/Source/event_groups.o \
./sdk/FreeRTOS/Source/list.o \
./sdk/FreeRTOS/Source/queue.o \
./sdk/FreeRTOS/Source/stream_buffer.o \
./sdk/FreeRTOS/Source/tasks.o \
./sdk/FreeRTOS/Source/timers.o 

C_DEPS += \
./sdk/FreeRTOS/Source/croutine.d \
./sdk/FreeRTOS/Source/event_groups.d \
./sdk/FreeRTOS/Source/list.d \
./sdk/FreeRTOS/Source/queue.d \
./sdk/FreeRTOS/Source/stream_buffer.d \
./sdk/FreeRTOS/Source/tasks.d \
./sdk/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/FreeRTOS/Source/%.o sdk/FreeRTOS/Source/%.su sdk/FreeRTOS/Source/%.cyclo: ../sdk/FreeRTOS/Source/%.c sdk/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../startup -I../src -I../src/app -I../src/bsp -I../src/bsp/peripheral -I../src/bsp/stmicro -I../src/bsp/stmicro/peripheral -I../src/bsp/stmicro/peripheral/i2c -I../src/bsp/stmicro/peripheral/spi -I../src/bsp/stmicro/peripheral/uart -I../src/bsp/stmicro/stm32l4 -I../src/bsp/stmicro/stm32l4/bloat -I../src/bsp/stmicro/stm32l4/board_specific -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v3 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/i2c -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/spi -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/uart -I../src/lib/flash -I../src/lib/util -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../sdk/CMSIS/Include -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/i2c" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/spi" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/uart" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I../src/task -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sdk-2f-FreeRTOS-2f-Source

clean-sdk-2f-FreeRTOS-2f-Source:
	-$(RM) ./sdk/FreeRTOS/Source/croutine.cyclo ./sdk/FreeRTOS/Source/croutine.d ./sdk/FreeRTOS/Source/croutine.o ./sdk/FreeRTOS/Source/croutine.su ./sdk/FreeRTOS/Source/event_groups.cyclo ./sdk/FreeRTOS/Source/event_groups.d ./sdk/FreeRTOS/Source/event_groups.o ./sdk/FreeRTOS/Source/event_groups.su ./sdk/FreeRTOS/Source/list.cyclo ./sdk/FreeRTOS/Source/list.d ./sdk/FreeRTOS/Source/list.o ./sdk/FreeRTOS/Source/list.su ./sdk/FreeRTOS/Source/queue.cyclo ./sdk/FreeRTOS/Source/queue.d ./sdk/FreeRTOS/Source/queue.o ./sdk/FreeRTOS/Source/queue.su ./sdk/FreeRTOS/Source/stream_buffer.cyclo ./sdk/FreeRTOS/Source/stream_buffer.d ./sdk/FreeRTOS/Source/stream_buffer.o ./sdk/FreeRTOS/Source/stream_buffer.su ./sdk/FreeRTOS/Source/tasks.cyclo ./sdk/FreeRTOS/Source/tasks.d ./sdk/FreeRTOS/Source/tasks.o ./sdk/FreeRTOS/Source/tasks.su ./sdk/FreeRTOS/Source/timers.cyclo ./sdk/FreeRTOS/Source/timers.d ./sdk/FreeRTOS/Source/timers.o ./sdk/FreeRTOS/Source/timers.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source

