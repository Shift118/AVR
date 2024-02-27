################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/External_EEPROM.c \
../src/i2c.c \
../src/keypad.c \
../src/lcd.c \
../src/main.c \
../src/uart.c 

OBJS += \
./src/External_EEPROM.o \
./src/i2c.o \
./src/keypad.o \
./src/lcd.o \
./src/main.o \
./src/uart.o 

C_DEPS += \
./src/External_EEPROM.d \
./src/i2c.d \
./src/keypad.d \
./src/lcd.d \
./src/main.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


