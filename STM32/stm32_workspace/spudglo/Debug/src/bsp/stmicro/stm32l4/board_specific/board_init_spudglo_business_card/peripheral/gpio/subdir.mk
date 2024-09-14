################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.c 

OBJS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.o 

C_DEPS += \
./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/%.o src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/%.su src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/%.cyclo: ../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/%.c src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.c_includes.args"

clean: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_business_card-2f-peripheral-2f-gpio

clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_business_card-2f-peripheral-2f-gpio:
	-$(RM) ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.cyclo ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.d ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.o ./src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_business_card/peripheral/gpio/board_spudglo_business_card_gpio_config.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-board_specific-2f-board_init_spudglo_business_card-2f-peripheral-2f-gpio

