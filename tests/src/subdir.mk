################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HE2Ciphertext.cpp \
../src/PolyCiphertext.cpp \
../src/SSECiphertext.cpp \
../src/main.cpp 

OBJS += \
./src/HE2Ciphertext.o \
./src/PolyCiphertext.o \
./src/SSECiphertext.o \
./src/main.o 

CPP_DEPS += \
./src/HE2Ciphertext.d \
./src/PolyCiphertext.d \
./src/SSECiphertext.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../include" -I"src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


