################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/rv8803/rv8803.c 

OBJS += \
./common/lib/sensor_third_party/rv8803/rv8803.o 

C_DEPS += \
./common/lib/sensor_third_party/rv8803/rv8803.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/sensor_third_party/rv8803/rv8803.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/rv8803/rv8803.c common/lib/sensor_third_party/rv8803/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/sensor_third_party/rv8803/rv8803.c_includes.args"

clean: clean-common-2f-lib-2f-sensor_third_party-2f-rv8803

clean-common-2f-lib-2f-sensor_third_party-2f-rv8803:
	-$(RM) ./common/lib/sensor_third_party/rv8803/rv8803.cyclo ./common/lib/sensor_third_party/rv8803/rv8803.d ./common/lib/sensor_third_party/rv8803/rv8803.o ./common/lib/sensor_third_party/rv8803/rv8803.su

.PHONY: clean-common-2f-lib-2f-sensor_third_party-2f-rv8803

