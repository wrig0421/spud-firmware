################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stmicro/peripheral/uart/uart_access_hal.c \
../src/bsp/stmicro/peripheral/uart/uart_config_hal.c 

OBJS += \
./src/bsp/stmicro/peripheral/uart/uart_access_hal.o \
./src/bsp/stmicro/peripheral/uart/uart_config_hal.o 

C_DEPS += \
./src/bsp/stmicro/peripheral/uart/uart_access_hal.d \
./src/bsp/stmicro/peripheral/uart/uart_config_hal.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stmicro/peripheral/uart/%.o src/bsp/stmicro/peripheral/uart/%.su src/bsp/stmicro/peripheral/uart/%.cyclo: ../src/bsp/stmicro/peripheral/uart/%.c src/bsp/stmicro/peripheral/uart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../startup -I../src -I../src/app -I../src/bsp -I../src/bsp/peripheral -I../src/bsp/stmicro -I../src/bsp/stmicro/peripheral -I../src/bsp/stmicro/peripheral/gpio -I../src/bsp/stmicro/peripheral/i2c -I../src/bsp/stmicro/peripheral/spi -I../src/bsp/stmicro/peripheral/uart -I../src/bsp/stmicro/stm32l4 -I../src/bsp/stmicro/stm32l4/bloat -I../src/bsp/stmicro/stm32l4/board_specific -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v3 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/i2c -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/spi -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/uart -I../src/lib/flash -I../src/lib/util -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../sdk/CMSIS/Include -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/i2c" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/spi" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/uart" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I../src/task -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/wifi" -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4/peripheral/i2c -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4/peripheral/spi -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4/peripheral/uart -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-uart

clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-uart:
	-$(RM) ./src/bsp/stmicro/peripheral/uart/uart_access_hal.cyclo ./src/bsp/stmicro/peripheral/uart/uart_access_hal.d ./src/bsp/stmicro/peripheral/uart/uart_access_hal.o ./src/bsp/stmicro/peripheral/uart/uart_access_hal.su ./src/bsp/stmicro/peripheral/uart/uart_config_hal.cyclo ./src/bsp/stmicro/peripheral/uart/uart_config_hal.d ./src/bsp/stmicro/peripheral/uart/uart_config_hal.o ./src/bsp/stmicro/peripheral/uart/uart_config_hal.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-peripheral-2f-uart

