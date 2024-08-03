################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/api/pkt/pkt.c 

OBJS += \
./common/api/pkt/pkt.o 

C_DEPS += \
./common/api/pkt/pkt.d 


# Each subdirectory must supply rules for building sources it contributes
common/api/pkt/pkt.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/api/pkt/pkt.c common/api/pkt/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/api/pkt/pkt.c_includes.args"

clean: clean-common-2f-api-2f-pkt

clean-common-2f-api-2f-pkt:
	-$(RM) ./common/api/pkt/pkt.cyclo ./common/api/pkt/pkt.d ./common/api/pkt/pkt.o ./common/api/pkt/pkt.su

.PHONY: clean-common-2f-api-2f-pkt

