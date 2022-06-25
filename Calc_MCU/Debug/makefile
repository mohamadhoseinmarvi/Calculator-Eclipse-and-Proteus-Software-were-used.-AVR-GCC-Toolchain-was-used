################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/TMR1/subdir.mk
-include MCAL/TMR0/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Two_MCU_Calc.lss \

FLASH_IMAGE += \
Two_MCU_Calc.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Two_MCU_Calc.elf secondary-outputs

# Tool invocations
Two_MCU_Calc.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Two_MCU_Calc.map -Wl,-u,vfprintf -mmcu=atmega32 -o "Two_MCU_Calc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Two_MCU_Calc.lss: Two_MCU_Calc.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Two_MCU_Calc.elf  >"Two_MCU_Calc.lss"
	@echo 'Finished building: $@'
	@echo ' '

Two_MCU_Calc.hex: Two_MCU_Calc.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Two_MCU_Calc.elf  "Two_MCU_Calc.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Two_MCU_Calc.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Two_MCU_Calc.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Two_MCU_Calc.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
