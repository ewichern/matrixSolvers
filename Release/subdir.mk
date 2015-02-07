################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../googleTestsMain.cc \
../test_matrixGenerator.cc \
../test_sparseMatrix.cc 

CPP_SRCS += \
../IterativeSolvers.cpp \
../matrixGenerator.cpp \
../matrixSolver.cpp \
../test_iterativeSolvers.cpp \
../test_matrixSolver.cpp 

CC_DEPS += \
./googleTestsMain.d \
./test_matrixGenerator.d \
./test_sparseMatrix.d 

OBJS += \
./IterativeSolvers.o \
./googleTestsMain.o \
./matrixGenerator.o \
./matrixSolver.o \
./test_iterativeSolvers.o \
./test_matrixGenerator.o \
./test_matrixSolver.o \
./test_sparseMatrix.o 

CPP_DEPS += \
./IterativeSolvers.d \
./matrixGenerator.d \
./matrixSolver.d \
./test_iterativeSolvers.d \
./test_matrixSolver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


