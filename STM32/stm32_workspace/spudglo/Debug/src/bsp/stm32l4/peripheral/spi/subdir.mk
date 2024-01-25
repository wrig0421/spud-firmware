################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/stm32l4/peripheral/spi/spi_access_hal.c 

OBJS += \
./src/bsp/stm32l4/peripheral/spi/spi_access_hal.o 

C_DEPS += \
./src/bsp/stm32l4/peripheral/spi/spi_access_hal.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/stm32l4/peripheral/spi/%.o src/bsp/stm32l4/peripheral/spi/%.su src/bsp/stm32l4/peripheral/spi/%.cyclo: ../src/bsp/stm32l4/peripheral/spi/%.c src/bsp/stm32l4/peripheral/spi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../src/stm32_bloat -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../src/bsp -I../startup -I../src -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../src/bsp/board_specific -I../src/bsp/board_specific/board_init_spud_glo_v3 -I../src/bsp/board_specific/board_init_spud_glo_v4 -I../sdk/CMSIS/Include -I../src/bsp/stm32_bloat -I../src/flash -I../src/task -I../src/util -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-bsp-2f-stm32l4-2f-peripheral-2f-spi

clean-src-2f-bsp-2f-stm32l4-2f-peripheral-2f-spi:
	-$(RM) ./src/bsp/stm32l4/peripheral/spi/spi_access_hal.cyclo ./src/bsp/stm32l4/peripheral/spi/spi_access_hal.d ./src/bsp/stm32l4/peripheral/spi/spi_access_hal.o ./src/bsp/stm32l4/peripheral/spi/spi_access_hal.su

.PHONY: clean-src-2f-bsp-2f-stm32l4-2f-peripheral-2f-spi
