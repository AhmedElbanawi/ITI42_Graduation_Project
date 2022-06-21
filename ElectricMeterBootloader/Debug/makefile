################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
ElectricMeterBootloader.lss \

FLASH_IMAGE += \
ElectricMeterBootloader.hex \

EEPROM_IMAGE += \
ElectricMeterBootloader.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ElectricMeterBootloader.elf secondary-outputs

# Tool invocations
ElectricMeterBootloader.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ElectricMeterBootloader.map -Ttext=0x7000 -mmcu=atmega32 -o "ElectricMeterBootloader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ElectricMeterBootloader.lss: ElectricMeterBootloader.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ElectricMeterBootloader.elf  >"ElectricMeterBootloader.lss"
	@echo 'Finished building: $@'
	@echo ' '

ElectricMeterBootloader.hex: ElectricMeterBootloader.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ElectricMeterBootloader.elf  "ElectricMeterBootloader.hex"
	@echo 'Finished building: $@'
	@echo ' '

ElectricMeterBootloader.eep: ElectricMeterBootloader.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ElectricMeterBootloader.elf  "ElectricMeterBootloader.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ElectricMeterBootloader.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ElectricMeterBootloader.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ElectricMeterBootloader.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -u -Uflash:w:ElectricMeterBootloader.hex:a -Ueeprom:w:ElectricMeterBootloader.eep:a -Ulfuse:w:0x4f:m -Uhfuse:w:0xd8:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ElectricMeterBootloader.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
