################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../test_denseMatrix.cc \
../test_rootSolvers.cc 

CPP_SRCS += \
../IterativeSolvers.cpp \
../directSolvers.cpp \
../matrixGenerator.cpp \
../rootSolvers.cpp \
../solversDriver.cpp 

CC_DEPS += \
./test_denseMatrix.d \
./test_rootSolvers.d 

OBJS += \
./IterativeSolvers.o \
./directSolvers.o \
./matrixGenerator.o \
./rootSolvers.o \
./solversDriver.o \
./test_denseMatrix.o \
./test_rootSolvers.o 

CPP_DEPS += \
./IterativeSolvers.d \
./directSolvers.d \
./matrixGenerator.d \
./rootSolvers.d \
./solversDriver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


