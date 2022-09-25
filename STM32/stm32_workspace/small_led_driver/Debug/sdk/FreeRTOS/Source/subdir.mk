################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
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
sdk/FreeRTOS/Source/%.o sdk/FreeRTOS/Source/%.su: ../sdk/FreeRTOS/Source/%.c sdk/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/work/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/ws2812b_driver" -I"C:/work/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/color_led" -I"C:/work/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/animate_led" -I"C:/work/Spud_code_collection/STM32/stm32_workspace/fw_common/lib/task" -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../sdk/CMSIS/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v1 -I../src/bsp/board_specific/board_init_spud_glo_v2 -I../src/bsp/board_specific/board_init_spud_glo_v3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-sdk-2f-FreeRTOS-2f-Source

clean-sdk-2f-FreeRTOS-2f-Source:
	-$(RM) ./sdk/FreeRTOS/Source/croutine.d ./sdk/FreeRTOS/Source/croutine.o ./sdk/FreeRTOS/Source/croutine.su ./sdk/FreeRTOS/Source/event_groups.d ./sdk/FreeRTOS/Source/event_groups.o ./sdk/FreeRTOS/Source/event_groups.su ./sdk/FreeRTOS/Source/list.d ./sdk/FreeRTOS/Source/list.o ./sdk/FreeRTOS/Source/list.su ./sdk/FreeRTOS/Source/queue.d ./sdk/FreeRTOS/Source/queue.o ./sdk/FreeRTOS/Source/queue.su ./sdk/FreeRTOS/Source/stream_buffer.d ./sdk/FreeRTOS/Source/stream_buffer.o ./sdk/FreeRTOS/Source/stream_buffer.su ./sdk/FreeRTOS/Source/tasks.d ./sdk/FreeRTOS/Source/tasks.o ./sdk/FreeRTOS/Source/tasks.su ./sdk/FreeRTOS/Source/timers.d ./sdk/FreeRTOS/Source/timers.o ./sdk/FreeRTOS/Source/timers.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source

