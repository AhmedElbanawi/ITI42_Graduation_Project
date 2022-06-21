################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP.c \
../CRC.c \
../DIO.c \
../DIO_CFG.c \
../FLASHER.c \
../FLASH_DATA.c \
../PARSER.c \
../RECORD.c \
../UDS.c \
../URT.c \
../main.c 

OBJS += \
./APP.o \
./CRC.o \
./DIO.o \
./DIO_CFG.o \
./FLASHER.o \
./FLASH_DATA.o \
./PARSER.o \
./RECORD.o \
./UDS.o \
./URT.o \
./main.o 

C_DEPS += \
./APP.d \
./CRC.d \
./DIO.d \
./DIO_CFG.d \
./FLASHER.d \
./FLASH_DATA.d \
./PARSER.d \
./RECORD.d \
./UDS.d \
./URT.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


