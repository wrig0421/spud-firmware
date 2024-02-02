################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/task/subdir.mk
-include src/lib/util/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/uart/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/spi/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/peripheral/gpio/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v5/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v4/subdir.mk
-include src/bsp/stmicro/stm32l4/board_specific/board_init_spudglo_v3/subdir.mk
-include src/bsp/stmicro/stm32l4/bloat/subdir.mk
-include src/bsp/stmicro/peripheral/uart/subdir.mk
-include src/bsp/stmicro/peripheral/spi/subdir.mk
-include src/bsp/stmicro/peripheral/gpio/subdir.mk
-include src/bsp/subdir.mk
-include src/subdir.mk
-include sdk/STM32L4xx_HAL_Driver/Src/subdir.mk
-include sdk/FreeRTOS/Source/portable/MemMang/subdir.mk
-include sdk/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include sdk/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include sdk/FreeRTOS/Source/subdir.mk
-include common/lib/wifi/subdir.mk
-include common/lib/task/subdir.mk
-include common/lib/semaphore/subdir.mk
-include common/lib/pkt/subdir.mk
-include common/lib/peripheral/uart/subdir.mk
-include common/lib/peripheral/spi/subdir.mk
-include common/lib/led/ws2812b_driver/subdir.mk
-include common/lib/led/color_led/subdir.mk
-include common/lib/led/animate_led/subdir.mk
-include common/lib/current_monitor/subdir.mk
-include common/lib/adafruit_soundboard/subdir.mk
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


BUILD_ARTIFACT_NAME := spudglo
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
spudglo.elf \

MAP_FILES += \
spudglo.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
spudglo.list \

OBJCOPY_BIN += \
spudglo.bin \


# All Target
all: main-build

# Main-build Target
main-build: spudglo.elf secondary-outputs

# Tool invocations
spudglo.elf spudglo.map: $(OBJS) $(USER_OBJS) /Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/spudglo/0x800_STM32L431RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "spudglo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/spud/Documents/GitHub/Spud_code_collection/STM32/stm32_workspace/spudglo/0x800_STM32L431RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="spudglo.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

spudglo.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "spudglo.list"
	@echo 'Finished building: $@'
	@echo ' '

spudglo.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "spudglo.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout spudglo.bin spudglo.elf spudglo.list spudglo.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
