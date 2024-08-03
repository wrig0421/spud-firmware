################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.c 

OBJS += \
./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.o 

C_DEPS += \
./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.d 


# Each subdirectory must supply rules for building sources it contributes
common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.o: C:/Users/Spud/Documents/GitHub/spud-firmware/STM32/stm32_workspace/common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.c common/lib/sensor_third_party/adafruit_soundboard/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.c_includes.args"

clean: clean-common-2f-lib-2f-sensor_third_party-2f-adafruit_soundboard

clean-common-2f-lib-2f-sensor_third_party-2f-adafruit_soundboard:
	-$(RM) ./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.cyclo ./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.d ./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.o ./common/lib/sensor_third_party/adafruit_soundboard/adafruit_soundboard.su

.PHONY: clean-common-2f-lib-2f-sensor_third_party-2f-adafruit_soundboard

