################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LPAggregationAlgorithm.cpp \
../src/ScalarLPAggregationAlgorithm.cpp \
../src/VectorLPAggregationAlgorithm.cpp 

OBJS += \
./src/LPAggregationAlgorithm.o \
./src/ScalarLPAggregationAlgorithm.o \
./src/VectorLPAggregationAlgorithm.o 

CPP_DEPS += \
./src/LPAggregationAlgorithm.d \
./src/ScalarLPAggregationAlgorithm.d \
./src/VectorLPAggregationAlgorithm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


