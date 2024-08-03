################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/peripheral/button/button_access.c 

OBJS += \
./common/lib/peripheral/button/button_access.o 

C_DEPS += \
./common/lib/peripheral/button/button_access.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/peripheral/button/button_access.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/peripheral/button/button_access.c common/lib/peripheral/button/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/peripheral/button/button_access.c_includes.args"

clean: clean-common-2f-lib-2f-peripheral-2f-button

clean-common-2f-lib-2f-peripheral-2f-button:
	-$(RM) ./common/lib/peripheral/button/button_access.cyclo ./common/lib/peripheral/button/button_access.d ./common/lib/peripheral/button/button_access.o ./common/lib/peripheral/button/button_access.su

.PHONY: clean-common-2f-lib-2f-peripheral-2f-button

