################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/led_color/led_color.c 

OBJS += \
./common/lib/led/led_color/led_color.o 

C_DEPS += \
./common/lib/led/led_color/led_color.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/led/led_color/led_color.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/led_color/led_color.c common/lib/led/led_color/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/led/led_color/led_color.c_includes.args"

clean: clean-common-2f-lib-2f-led-2f-led_color

clean-common-2f-lib-2f-led-2f-led_color:
	-$(RM) ./common/lib/led/led_color/led_color.cyclo ./common/lib/led/led_color/led_color.d ./common/lib/led/led_color/led_color.o ./common/lib/led/led_color/led_color.su

.PHONY: clean-common-2f-lib-2f-led-2f-led_color

