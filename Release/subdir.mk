################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../test_denseMatrix.cc \
../test_monomial.cc \
../test_polynomial.cc \
../test_rootDriver.cc \
../test_rootSolvers.cc 

CPP_SRCS += \
../IterativeSolvers.cpp \
../directSolvers.cpp \
../matrixDriver.cpp \
../matrixGenerator.cpp \
../monomial.cpp \
../polynomial.cpp \
../rootDriver.cpp \
../rootSolvers.cpp 

O_SRCS += \
../IterativeSolvers.o \
../directSolvers.o \
../googleTestsMain.o \
../matrixGenerator.o \
../monomial.o \
../polynomial.o \
../rootSolvers.o \
../test_denseMatrix.o \
../test_directSolvers.o \
../test_iterativeSolvers.o \
../test_matrixGenerator.o \
../test_matrixSolver.o \
../test_monomial.o \
../test_polynomial.o \
../test_rootSolvers.o 

CC_DEPS += \
./test_denseMatrix.d \
./test_monomial.d \
./test_polynomial.d \
./test_rootDriver.d \
./test_rootSolvers.d 

OBJS += \
./IterativeSolvers.o \
./directSolvers.o \
./matrixDriver.o \
./matrixGenerator.o \
./monomial.o \
./polynomial.o \
./rootDriver.o \
./rootSolvers.o \
./test_denseMatrix.o \
./test_monomial.o \
./test_polynomial.o \
./test_rootDriver.o \
./test_rootSolvers.o 

CPP_DEPS += \
./IterativeSolvers.d \
./directSolvers.d \
./matrixDriver.d \
./matrixGenerator.d \
./monomial.d \
./polynomial.d \
./rootDriver.d \
./rootSolvers.d 


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


