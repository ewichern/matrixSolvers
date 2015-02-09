################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IterativeSolvers.cpp \
../matrixGenerator.cpp \
../matrixSolver.cpp 

OBJS += \
./IterativeSolvers.o \
./matrixGenerator.o \
./matrixSolver.o 

CPP_DEPS += \
./IterativeSolvers.d \
./matrixGenerator.d \
./matrixSolver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/erik/libraries -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


