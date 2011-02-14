################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BitField8.cpp \
../ByteReader.cpp \
../ByteWriter.cpp \
../CommandData.cpp \
../FRCCommunication.cpp \
../Main.cpp \
../Mode.cpp \
../StatusData.cpp \
../UserCode.cpp 

C_SRCS += \
../Missing.c \
../UserConstants.c 

OBJS += \
./BitField8.o \
./ByteReader.o \
./ByteWriter.o \
./CommandData.o \
./FRCCommunication.o \
./Main.o \
./Missing.o \
./Mode.o \
./StatusData.o \
./UserCode.o \
./UserConstants.o 

C_DEPS += \
./Missing.d \
./UserConstants.d 

CPP_DEPS += \
./BitField8.d \
./ByteReader.d \
./ByteWriter.d \
./CommandData.d \
./FRCCommunication.d \
./Main.d \
./Mode.d \
./StatusData.d \
./UserCode.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\ehaskins.EHNET\Code\Next Robots\workspace\Arduino" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\ehaskins.EHNET\Code\Next Robots\workspace\Arduino" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


