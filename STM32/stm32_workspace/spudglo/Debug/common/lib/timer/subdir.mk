################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/timer/timer_ctrl.c 

OBJS += \
./common/lib/timer/timer_ctrl.o 

C_DEPS += \
./common/lib/timer/timer_ctrl.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/timer/timer_ctrl.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/timer/timer_ctrl.c common/lib/timer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/timer/timer_ctrl.c_includes.args"

clean: clean-common-2f-lib-2f-timer

clean-common-2f-lib-2f-timer:
	-$(RM) ./common/lib/timer/timer_ctrl.cyclo ./common/lib/timer/timer_ctrl.d ./common/lib/timer/timer_ctrl.o ./common/lib/timer/timer_ctrl.su

.PHONY: clean-common-2f-lib-2f-timer

