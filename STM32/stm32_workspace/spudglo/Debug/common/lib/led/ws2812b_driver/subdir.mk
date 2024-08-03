################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/ws2812b_driver/ws2812b.c 

OBJS += \
./common/lib/led/ws2812b_driver/ws2812b.o 

C_DEPS += \
./common/lib/led/ws2812b_driver/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/led/ws2812b_driver/ws2812b.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/led/ws2812b_driver/ws2812b.c common/lib/led/ws2812b_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/led/ws2812b_driver/ws2812b.c_includes.args"

clean: clean-common-2f-lib-2f-led-2f-ws2812b_driver

clean-common-2f-lib-2f-led-2f-ws2812b_driver:
	-$(RM) ./common/lib/led/ws2812b_driver/ws2812b.cyclo ./common/lib/led/ws2812b_driver/ws2812b.d ./common/lib/led/ws2812b_driver/ws2812b.o ./common/lib/led/ws2812b_driver/ws2812b.su

.PHONY: clean-common-2f-lib-2f-led-2f-ws2812b_driver

