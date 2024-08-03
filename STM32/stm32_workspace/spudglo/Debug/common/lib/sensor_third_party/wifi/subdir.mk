################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/wifi/esp8266.c \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/wifi/esp8266_webserver.c 

OBJS += \
./common/lib/sensor_third_party/wifi/esp8266.o \
./common/lib/sensor_third_party/wifi/esp8266_webserver.o 

C_DEPS += \
./common/lib/sensor_third_party/wifi/esp8266.d \
./common/lib/sensor_third_party/wifi/esp8266_webserver.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/sensor_third_party/wifi/esp8266.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/wifi/esp8266.c common/lib/sensor_third_party/wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/sensor_third_party/wifi/esp8266.c_includes.args"
common/lib/sensor_third_party/wifi/esp8266_webserver.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/wifi/esp8266_webserver.c common/lib/sensor_third_party/wifi/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/sensor_third_party/wifi/esp8266_webserver.c_includes.args"

clean: clean-common-2f-lib-2f-sensor_third_party-2f-wifi

clean-common-2f-lib-2f-sensor_third_party-2f-wifi:
	-$(RM) ./common/lib/sensor_third_party/wifi/esp8266.cyclo ./common/lib/sensor_third_party/wifi/esp8266.d ./common/lib/sensor_third_party/wifi/esp8266.o ./common/lib/sensor_third_party/wifi/esp8266.su ./common/lib/sensor_third_party/wifi/esp8266_webserver.cyclo ./common/lib/sensor_third_party/wifi/esp8266_webserver.d ./common/lib/sensor_third_party/wifi/esp8266_webserver.o ./common/lib/sensor_third_party/wifi/esp8266_webserver.su

.PHONY: clean-common-2f-lib-2f-sensor_third_party-2f-wifi

