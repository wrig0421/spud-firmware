################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.c 

OBJS += \
./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.o 

C_DEPS += \
./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.c common/lib/led/led_ctrl/led_ctrl_power/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.c_includes.args"

clean: clean-common-2f-lib-2f-led-2f-led_ctrl-2f-led_ctrl_power

clean-common-2f-lib-2f-led-2f-led_ctrl-2f-led_ctrl_power:
	-$(RM) ./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.cyclo ./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.d ./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.o ./common/lib/led/led_ctrl/led_ctrl_power/led_ctrl_power.su

.PHONY: clean-common-2f-lib-2f-led-2f-led_ctrl-2f-led_ctrl_power

