################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/stm32_bloat/subdir.mk
-include src/bsp/board_specific/board_init_spud_glo_v3/subdir.mk
-include src/bsp/board_specific/board_init_spud_glo_v2/subdir.mk
-include src/bsp/board_specific/board_init_spud_glo_v1/subdir.mk
-include src/bsp/subdir.mk
-include src/subdir.mk
-include sdk/STM32L4xx_HAL_Driver/Src/subdir.mk
-include sdk/FreeRTOS/Source/portable/MemMang/subdir.mk
-include sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include sdk/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include sdk/FreeRTOS/Source/subdir.mk
-include fw_common/ws2812b_driver/subdir.mk
-include fw_common/color_led/subdir.mk
-include fw_common/animate_led/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := small_led_driver
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
small_led_driver.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
small_led_driver.list \

OBJCOPY_BIN += \
small_led_driver.bin \


# All Target
all: main-build

# Main-build Target
main-build: small_led_driver.elf secondary-outputs

# Tool invocations
small_led_driver.elf: $(OBJS) $(USER_OBJS) C:\Users\splat\Documents\GitHub\Spud_code_collection\STM32\stm32_workspace\small_led_driver\STM32L431RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "small_led_driver.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\splat\Documents\GitHub\Spud_code_collection\STM32\stm32_workspace\small_led_driver\STM32L431RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="small_led_driver.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

small_led_driver.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "small_led_driver.list"
	@echo 'Finished building: $@'
	@echo ' '

small_led_driver.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "small_led_driver.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
