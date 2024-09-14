################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/peripheral/spi/spi_acces.c 

OBJS += \
./common/lib/peripheral/spi/spi_acces.o 

C_DEPS += \
./common/lib/peripheral/spi/spi_acces.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/peripheral/spi/spi_acces.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/peripheral/spi/spi_acces.c common/lib/peripheral/spi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/peripheral/spi/spi_acces.c_includes.args"

clean: clean-common-2f-lib-2f-peripheral-2f-spi

clean-common-2f-lib-2f-peripheral-2f-spi:
	-$(RM) ./common/lib/peripheral/spi/spi_acces.cyclo ./common/lib/peripheral/spi/spi_acces.d ./common/lib/peripheral/spi/spi_acces.o ./common/lib/peripheral/spi/spi_acces.su

.PHONY: clean-common-2f-lib-2f-peripheral-2f-spi

