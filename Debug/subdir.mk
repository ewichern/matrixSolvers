################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../googleTestsMain.cpp \
../sampleMatrix.cpp \
../sampleMatrix_test.cpp 

OBJS += \
./googleTestsMain.o \
./sampleMatrix.o \
./sampleMatrix_test.o 

CPP_DEPS += \
./googleTestsMain.d \
./sampleMatrix.d \
./sampleMatrix_test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/erik/libraries -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


