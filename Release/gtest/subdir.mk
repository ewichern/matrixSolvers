################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../gtest/gtest-all.cc 

O_SRCS += \
../gtest/gtest-all.o 

CC_DEPS += \
./gtest/gtest-all.d 

OBJS += \
./gtest/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
gtest/%.o: ../gtest/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


