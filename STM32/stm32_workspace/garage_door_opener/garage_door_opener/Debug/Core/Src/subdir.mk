################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/board_init.c \
../Core/Src/flash_access.c \
../Core/Src/fonts.c \
../Core/Src/freertos.c \
../Core/Src/gt_521fx_driver.c \
../Core/Src/keypad.c \
../Core/Src/main.c \
../Core/Src/packet_def.c \
../Core/Src/packet_queue.c \
../Core/Src/serial_com.c \
../Core/Src/ssd1351_driver.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_hal_timebase_tim.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/task_create.c \
../Core/Src/task_keypad_access.c \
../Core/Src/task_sensor_access.c 

OBJS += \
./Core/Src/board_init.o \
./Core/Src/flash_access.o \
./Core/Src/fonts.o \
./Core/Src/freertos.o \
./Core/Src/gt_521fx_driver.o \
./Core/Src/keypad.o \
./Core/Src/main.o \
./Core/Src/packet_def.o \
./Core/Src/packet_queue.o \
./Core/Src/serial_com.o \
./Core/Src/ssd1351_driver.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_hal_timebase_tim.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/task_create.o \
./Core/Src/task_keypad_access.o \
./Core/Src/task_sensor_access.o 

C_DEPS += \
./Core/Src/board_init.d \
./Core/Src/flash_access.d \
./Core/Src/fonts.d \
./Core/Src/freertos.d \
./Core/Src/gt_521fx_driver.d \
./Core/Src/keypad.d \
./Core/Src/main.d \
./Core/Src/packet_def.d \
./Core/Src/packet_queue.d \
./Core/Src/serial_com.d \
./Core/Src/ssd1351_driver.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_hal_timebase_tim.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/task_create.d \
./Core/Src/task_keypad_access.d \
./Core/Src/task_sensor_access.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/board_init.d ./Core/Src/board_init.o ./Core/Src/board_init.su ./Core/Src/flash_access.d ./Core/Src/flash_access.o ./Core/Src/flash_access.su ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/gt_521fx_driver.d ./Core/Src/gt_521fx_driver.o ./Core/Src/gt_521fx_driver.su ./Core/Src/keypad.d ./Core/Src/keypad.o ./Core/Src/keypad.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/packet_def.d ./Core/Src/packet_def.o ./Core/Src/packet_def.su ./Core/Src/packet_queue.d ./Core/Src/packet_queue.o ./Core/Src/packet_queue.su ./Core/Src/serial_com.d ./Core/Src/serial_com.o ./Core/Src/serial_com.su ./Core/Src/ssd1351_driver.d ./Core/Src/ssd1351_driver.o ./Core/Src/ssd1351_driver.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_hal_timebase_tim.d ./Core/Src/stm32l4xx_hal_timebase_tim.o ./Core/Src/stm32l4xx_hal_timebase_tim.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/task_create.d ./Core/Src/task_create.o ./Core/Src/task_create.su ./Core/Src/task_keypad_access.d ./Core/Src/task_keypad_access.o ./Core/Src/task_keypad_access.su ./Core/Src/task_sensor_access.d ./Core/Src/task_sensor_access.o ./Core/Src/task_sensor_access.su

.PHONY: clean-Core-2f-Src

