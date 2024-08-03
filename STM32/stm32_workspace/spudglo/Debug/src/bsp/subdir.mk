################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/board_init_common.c \
../src/bsp/flash_access.c \
../src/bsp/flash_info.c 

OBJS += \
./src/bsp/board_init_common.o \
./src/bsp/flash_access.o \
./src/bsp/flash_info.o 

C_DEPS += \
./src/bsp/board_init_common.d \
./src/bsp/flash_access.d \
./src/bsp/flash_info.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o src/bsp/%.su src/bsp/%.cyclo: ../src/bsp/%.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/board_init_common.c_includes.args"

clean: clean-src-2f-bsp

clean-src-2f-bsp:
	-$(RM) ./src/bsp/board_init_common.cyclo ./src/bsp/board_init_common.d ./src/bsp/board_init_common.o ./src/bsp/board_init_common.su ./src/bsp/flash_access.cyclo ./src/bsp/flash_access.d ./src/bsp/flash_access.o ./src/bsp/flash_access.su ./src/bsp/flash_info.cyclo ./src/bsp/flash_info.d ./src/bsp/flash_info.o ./src/bsp/flash_info.su

.PHONY: clean-src-2f-bsp

