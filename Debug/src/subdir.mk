################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/access_devices.cpp \
../src/trik_motors_function_1.cpp \
../src/usbMSP430Interface.cpp 

OBJS += \
./src/access_devices.o \
./src/trik_motors_function_1.o \
./src/usbMSP430Interface.o 

CPP_DEPS += \
./src/access_devices.d \
./src/trik_motors_function_1.d \
./src/usbMSP430Interface.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	/opt/trik-sdk/sysroots/i686-oesdk-linux/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


