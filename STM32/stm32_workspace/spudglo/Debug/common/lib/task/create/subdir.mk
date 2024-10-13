################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/create/task_create.c 

OBJS += \
./common/lib/task/create/task_create.o 

C_DEPS += \
./common/lib/task/create/task_create.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/task/create/task_create.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/create/task_create.c common/lib/task/create/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/create/task_create.c_includes.args"

clean: clean-common-2f-lib-2f-task-2f-create

clean-common-2f-lib-2f-task-2f-create:
	-$(RM) ./common/lib/task/create/task_create.cyclo ./common/lib/task/create/task_create.d ./common/lib/task/create/task_create.o ./common/lib/task/create/task_create.su

.PHONY: clean-common-2f-lib-2f-task-2f-create

