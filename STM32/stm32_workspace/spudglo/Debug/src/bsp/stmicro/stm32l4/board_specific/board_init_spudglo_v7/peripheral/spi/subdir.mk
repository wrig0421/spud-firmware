################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.c 

OBJS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.o 

C_DEPS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/%.o src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/%.su src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/%.cyclo: ../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/%.c src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.c_includes.args"

clean: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-spi

clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-spi:
	-$(RM) ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.cyclo ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.d ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.o ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v7/peripheral/spi/board_spudglo_v7_spi_config.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_v7-2f-peripheral-2f-spi

