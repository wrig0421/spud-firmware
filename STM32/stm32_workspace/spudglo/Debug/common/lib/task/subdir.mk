################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_button_press.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_led_ctrl.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_mn_wild.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_notify.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_pkt_process.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_uart.c 

OBJS += \
./common/lib/task/task_button_press.o \
./common/lib/task/task_led_ctrl.o \
./common/lib/task/task_mn_wild.o \
./common/lib/task/task_notify.o \
./common/lib/task/task_pkt_process.o \
./common/lib/task/task_uart.o 

C_DEPS += \
./common/lib/task/task_button_press.d \
./common/lib/task/task_led_ctrl.d \
./common/lib/task/task_mn_wild.d \
./common/lib/task/task_notify.d \
./common/lib/task/task_pkt_process.d \
./common/lib/task/task_uart.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/task/task_button_press.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_button_press.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_button_press.c_includes.args"
common/lib/task/task_led_ctrl.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_led_ctrl.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_led_ctrl.c_includes.args"
common/lib/task/task_mn_wild.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_mn_wild.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_mn_wild.c_includes.args"
common/lib/task/task_notify.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_notify.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_notify.c_includes.args"
common/lib/task/task_pkt_process.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_pkt_process.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_pkt_process.c_includes.args"
common/lib/task/task_uart.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/task/task_uart.c common/lib/task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/task/task_uart.c_includes.args"

clean: clean-common-2f-lib-2f-task

clean-common-2f-lib-2f-task:
	-$(RM) ./common/lib/task/task_button_press.cyclo ./common/lib/task/task_button_press.d ./common/lib/task/task_button_press.o ./common/lib/task/task_button_press.su ./common/lib/task/task_led_ctrl.cyclo ./common/lib/task/task_led_ctrl.d ./common/lib/task/task_led_ctrl.o ./common/lib/task/task_led_ctrl.su ./common/lib/task/task_mn_wild.cyclo ./common/lib/task/task_mn_wild.d ./common/lib/task/task_mn_wild.o ./common/lib/task/task_mn_wild.su ./common/lib/task/task_notify.cyclo ./common/lib/task/task_notify.d ./common/lib/task/task_notify.o ./common/lib/task/task_notify.su ./common/lib/task/task_pkt_process.cyclo ./common/lib/task/task_pkt_process.d ./common/lib/task/task_pkt_process.o ./common/lib/task/task_pkt_process.su ./common/lib/task/task_uart.cyclo ./common/lib/task/task_uart.d ./common/lib/task/task_uart.o ./common/lib/task/task_uart.su

.PHONY: clean-common-2f-lib-2f-task

