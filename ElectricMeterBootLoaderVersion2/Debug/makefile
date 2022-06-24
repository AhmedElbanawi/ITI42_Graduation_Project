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
ElectricMeterBootLoaderVersion2.lss \

FLASH_IMAGE += \
ElectricMeterBootLoaderVersion2.hex \

EEPROM_IMAGE += \
ElectricMeterBootLoaderVersion2.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ElectricMeterBootLoaderVersion2.elf secondary-outputs

# Tool invocations
ElectricMeterBootLoaderVersion2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ElectricMeterBootLoaderVersion2.map -Ttext=0x7000 -mmcu=atmega32 -o "ElectricMeterBootLoaderVersion2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ElectricMeterBootLoaderVersion2.lss: ElectricMeterBootLoaderVersion2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ElectricMeterBootLoaderVersion2.elf  >"ElectricMeterBootLoaderVersion2.lss"
	@echo 'Finished building: $@'
	@echo ' '

ElectricMeterBootLoaderVersion2.hex: ElectricMeterBootLoaderVersion2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ElectricMeterBootLoaderVersion2.elf  "ElectricMeterBootLoaderVersion2.hex"
	@echo 'Finished building: $@'
	@echo ' '

ElectricMeterBootLoaderVersion2.eep: ElectricMeterBootLoaderVersion2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ElectricMeterBootLoaderVersion2.elf  "ElectricMeterBootLoaderVersion2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ElectricMeterBootLoaderVersion2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ElectricMeterBootLoaderVersion2.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ElectricMeterBootLoaderVersion2.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -u -Uflash:w:ElectricMeterBootLoaderVersion2.hex:a -Ueeprom:w:ElectricMeterBootLoaderVersion2.eep:a -Ulfuse:w:0x4f:m -Uhfuse:w:0xd8:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ElectricMeterBootLoaderVersion2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
