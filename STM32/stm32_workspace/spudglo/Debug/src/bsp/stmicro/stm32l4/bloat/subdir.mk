################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../startup -I../src -I../src/app -I../src/bsp -I../src/bsp/peripheral -I../src/bsp/stmicro -I../src/bsp/stmicro/peripheral -I../src/bsp/stmicro/peripheral/i2c -I../src/bsp/stmicro/peripheral/spi -I../src/bsp/stmicro/peripheral/uart -I../src/bsp/stmicro/stm32l4 -I../src/bsp/stmicro/stm32l4/bloat -I../src/bsp/stmicro/stm32l4/board_specific -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v3 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5 -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/i2c -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/spi -I../src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/uart -I../src/lib/flash -I../src/lib/util -I../sdk/FreeRTOS/Source/CMSIS_RTOS_V2 -I../sdk/CMSIS/Device/ST/STM32L4xx/Include -I../sdk/STM32l4xx_HAL_Driver/Inc -I../sdk/STM32l4xx_HAL_Driver/Inc/Legacy -I../sdk/FreeRTOS/Source -I../sdk/FreeRTOS/Source/include -I../sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../sdk/CMSIS/Include -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/current_monitor" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/animate_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/color_led" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/led/ws2812b_driver" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/i2c" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/spi" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/peripheral/uart" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/semaphore" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/task" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/pkt" -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/queue" -I../src/task -I"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/common/lib/wifi" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat

clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat:
	-$(RM) ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.cyclo ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.d ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.o ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_hal_msp.su ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.cyclo ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.d ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.o ./src/bsp/stmicro/stm32l4/bloat/stm32l4xx_it.su ./src/bsp/stmicro/stm32l4/bloat/syscalls.cyclo ./src/bsp/stmicro/stm32l4/bloat/syscalls.d ./src/bsp/stmicro/stm32l4/bloat/syscalls.o ./src/bsp/stmicro/stm32l4/bloat/syscalls.su ./src/bsp/stmicro/stm32l4/bloat/sysmem.cyclo ./src/bsp/stmicro/stm32l4/bloat/sysmem.d ./src/bsp/stmicro/stm32l4/bloat/sysmem.o ./src/bsp/stmicro/stm32l4/bloat/sysmem.su ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.cyclo ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.d ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.o ./src/bsp/stmicro/stm32l4/bloat/system_stm32l4xx.su

.PHONY: clean-src-2f-bsp-2f-stmicro-2f-stm32l4-2f-bloat
