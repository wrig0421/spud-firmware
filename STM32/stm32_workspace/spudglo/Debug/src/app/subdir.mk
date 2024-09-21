################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/main.c \
../src/app/task_create.c \
../src/app/timer_create.c 

OBJS += \
./src/app/main.o \
./src/app/task_create.o \
./src/app/timer_create.o 

C_DEPS += \
./src/app/main.d \
./src/app/task_create.d \
./src/app/timer_create.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/%.o src/app/%.su src/app/%.cyclo: ../src/app/%.c src/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/app/main.c_includes.args"

clean: clean-src-2f-app

clean-src-2f-app:
	-$(RM) ./src/app/main.cyclo ./src/app/main.d ./src/app/main.o ./src/app/main.su ./src/app/task_create.cyclo ./src/app/task_create.d ./src/app/task_create.o ./src/app/task_create.su ./src/app/timer_create.cyclo ./src/app/timer_create.d ./src/app/timer_create.o ./src/app/timer_create.su

.PHONY: clean-src-2f-app

