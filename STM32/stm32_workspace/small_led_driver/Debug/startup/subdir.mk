################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l431rctx.s 

OBJS += \
./startup/startup_stm32l431rctx.o 

S_DEPS += \
./startup/startup_stm32l431rctx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_stm32l431rctx.o: ../startup/startup_stm32l431rctx.s startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"startup/startup_stm32l431rctx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

