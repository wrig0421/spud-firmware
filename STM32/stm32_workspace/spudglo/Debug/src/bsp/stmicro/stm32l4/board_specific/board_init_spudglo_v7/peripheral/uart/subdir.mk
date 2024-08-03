################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.c 

OBJS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.o 

C_DEPS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/%.o src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/%.su src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/%.cyclo: ../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/%.c src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.c_includes.args"

clean: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-uart

clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-uart:
	-$(RM) ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.cyclo ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.d ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.o ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/uart/board_spudglo_v7_uart_config.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-uart

