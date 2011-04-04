################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FRCComms/BitField16.cpp \
../FRCComms/BitField8.cpp \
../FRCComms/ByteReader.cpp \
../FRCComms/ByteWriter.cpp \
../FRCComms/CRC32.cpp \
../FRCComms/Configuration.cpp \
../FRCComms/ControlData.cpp \
../FRCComms/FRCCommunication.cpp \
../FRCComms/Joystick.cpp \
../FRCComms/Main.cpp \
../FRCComms/Mode.cpp \
../FRCComms/RobotStatusLight.cpp \
../FRCComms/StatusData.cpp 

C_SRCS += \
../FRCComms/Missing.c 

OBJS += \
./FRCComms/BitField16.o \
./FRCComms/BitField8.o \
./FRCComms/ByteReader.o \
./FRCComms/ByteWriter.o \
./FRCComms/CRC32.o \
./FRCComms/Configuration.o \
./FRCComms/ControlData.o \
./FRCComms/FRCCommunication.o \
./FRCComms/Joystick.o \
./FRCComms/Main.o \
./FRCComms/Missing.o \
./FRCComms/Mode.o \
./FRCComms/RobotStatusLight.o \
./FRCComms/StatusData.o 

C_DEPS += \
./FRCComms/Missing.d 

CPP_DEPS += \
./FRCComms/BitField16.d \
./FRCComms/BitField8.d \
./FRCComms/ByteReader.d \
./FRCComms/ByteWriter.d \
./FRCComms/CRC32.d \
./FRCComms/Configuration.d \
./FRCComms/ControlData.d \
./FRCComms/FRCCommunication.d \
./FRCComms/Joystick.d \
./FRCComms/Main.d \
./FRCComms/Mode.d \
./FRCComms/RobotStatusLight.d \
./FRCComms/StatusData.d 


# Each subdirectory must supply rules for building sources it contributes
FRCComms/%.o: ../FRCComms/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FRCComms/%.o: ../FRCComms/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


