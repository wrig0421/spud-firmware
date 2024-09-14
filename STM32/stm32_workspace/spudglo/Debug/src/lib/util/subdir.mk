################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/util/numbers.c \
../src/lib/util/version.c 

OBJS += \
./src/lib/util/numbers.o \
./src/lib/util/version.o 

C_DEPS += \
./src/lib/util/numbers.d \
./src/lib/util/version.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/util/%.o src/lib/util/%.su src/lib/util/%.cyclo: ../src/lib/util/%.c src/lib/util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/lib/util/numbers.c_includes.args"

clean: clean-src-2f-lib-2f-util

clean-src-2f-lib-2f-util:
	-$(RM) ./src/lib/util/numbers.cyclo ./src/lib/util/numbers.d ./src/lib/util/numbers.o ./src/lib/util/numbers.su ./src/lib/util/version.cyclo ./src/lib/util/version.d ./src/lib/util/version.o ./src/lib/util/version.su

.PHONY: clean-src-2f-lib-2f-util

