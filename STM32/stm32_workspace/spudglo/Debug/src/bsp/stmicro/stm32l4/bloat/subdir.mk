################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.c \
../src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.c \
../src/bsp/stmicro/stm32l4/bloat/syscalls.c \
../src/bsp/stmicro/stm32l4/bloat/sysmem.c \
../src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.c 

OBJS += \
./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.o \
./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.o \
./src/bsp/stmicro/stm32l4/bloat/syscalls.o \
./src/bsp/stmicro/stm32l4/bloat/sysmem.o \
./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.o 

C_DEPS += \
./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.d \
./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.d \
./src/bsp/stmicro/stm32l4/bloat/syscalls.d \
./src/bsp/stmicro/stm32l4/bloat/sysmem.d \
./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/stm32l4/bloat/%.o src/bsp/stmicro/stm32l4/bloat/%.su src/bsp/stmicro/stm32l4/bloat/%.cyclo: ../src/bsp/stmicro/stm32l4/bloat/%.c src/bsp/stmicro/stm32l4/bloat/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.c_includes.args"

clean: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat

clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat:
	-$(RM) ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.cyclo ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.d ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.o ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.su ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.cyclo ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.d ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.o ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.su ./src/bsp/stmicro/stm32l4/bloat/syscalls.cyclo ./src/bsp/stmicro/stm32l4/bloat/syscalls.d ./src/bsp/stmicro/stm32l4/bloat/syscalls.o ./src/bsp/stmicro/stm32l4/bloat/syscalls.su ./src/bsp/stmicro/stm32l4/bloat/sysmem.cyclo ./src/bsp/stmicro/stm32l4/bloat/sysmem.d ./src/bsp/stmicro/stm32l4/bloat/sysmem.o ./src/bsp/stmicro/stm32l4/bloat/sysmem.su ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.cyclo ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.d ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.o ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat

