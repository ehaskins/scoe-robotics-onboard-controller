################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client.cpp \
../Ethernet.cpp \
../HardwareSerial.cpp \
../Print.cpp \
../SPI.cpp \
../Server.cpp \
../Tone.cpp \
../Udp.cpp \
../WMath.cpp \
../WString.cpp \
../socket.cpp \
../w5100.cpp 

C_SRCS += \
../WInterrupts.c \
../pins_arduino.c \
../wiring.c \
../wiring_analog.c \
../wiring_digital.c \
../wiring_pulse.c \
../wiring_shift.c 

OBJS += \
./Client.o \
./Ethernet.o \
./HardwareSerial.o \
./Print.o \
./SPI.o \
./Server.o \
./Tone.o \
./Udp.o \
./WInterrupts.o \
./WMath.o \
./WString.o \
./pins_arduino.o \
./socket.o \
./w5100.o \
./wiring.o \
./wiring_analog.o \
./wiring_digital.o \
./wiring_pulse.o \
./wiring_shift.o 

C_DEPS += \
./WInterrupts.d \
./pins_arduino.d \
./wiring.d \
./wiring_analog.d \
./wiring_digital.d \
./wiring_pulse.d \
./wiring_shift.d 

CPP_DEPS += \
./Client.d \
./Ethernet.d \
./HardwareSerial.d \
./Print.d \
./SPI.d \
./Server.d \
./Tone.d \
./Udp.d \
./WMath.d \
./WString.d \
./socket.d \
./w5100.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\ehaskins.EHNET\Code Local\Next Robots\workspace\Arduino" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wl,--gc-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\ehaskins.EHNET\Code Local\Next Robots\workspace\Arduino" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


