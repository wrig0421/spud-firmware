################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"sdk/FreeRTOS/Source/croutine.c_includes.args"

clean: clean-sdk-2f-FreeRTOS-2f-Source

clean-sdk-2f-FreeRTOS-2f-Source:
	-$(RM) ./sdk/FreeRTOS/Source/croutine.cyclo ./sdk/FreeRTOS/Source/croutine.d ./sdk/FreeRTOS/Source/croutine.o ./sdk/FreeRTOS/Source/croutine.su ./sdk/FreeRTOS/Source/event_groups.cyclo ./sdk/FreeRTOS/Source/event_groups.d ./sdk/FreeRTOS/Source/event_groups.o ./sdk/FreeRTOS/Source/event_groups.su ./sdk/FreeRTOS/Source/list.cyclo ./sdk/FreeRTOS/Source/list.d ./sdk/FreeRTOS/Source/list.o ./sdk/FreeRTOS/Source/list.su ./sdk/FreeRTOS/Source/queue.cyclo ./sdk/FreeRTOS/Source/queue.d ./sdk/FreeRTOS/Source/queue.o ./sdk/FreeRTOS/Source/queue.su ./sdk/FreeRTOS/Source/stream_buffer.cyclo ./sdk/FreeRTOS/Source/stream_buffer.d ./sdk/FreeRTOS/Source/stream_buffer.o ./sdk/FreeRTOS/Source/stream_buffer.su ./sdk/FreeRTOS/Source/tasks.cyclo ./sdk/FreeRTOS/Source/tasks.d ./sdk/FreeRTOS/Source/tasks.o ./sdk/FreeRTOS/Source/tasks.su ./sdk/FreeRTOS/Source/timers.cyclo ./sdk/FreeRTOS/Source/timers.d ./sdk/FreeRTOS/Source/timers.o ./sdk/FreeRTOS/Source/timers.su

.PHONY: clean-sdk-2f-FreeRTOS-2f-Source

