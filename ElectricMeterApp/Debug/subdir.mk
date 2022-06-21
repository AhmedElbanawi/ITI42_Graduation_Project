################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO.c \
../DIO_CFG.c \
../FLASH_DATA.c \
../REQ.c \
../UDS.c \
../URT.c \
../WDT.c \
../main.c 

OBJS += \
./DIO.o \
./DIO_CFG.o \
./FLASH_DATA.o \
./REQ.o \
./UDS.o \
./URT.o \
./WDT.o \
./main.o 

C_DEPS += \
./DIO.d \
./DIO_CFG.d \
./FLASH_DATA.d \
./REQ.d \
./UDS.d \
./URT.d \
./WDT.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


