################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Complexity.cpp \
../src/Eval.cpp \
../src/LPAggreg.cpp \
../src/LPAggregWrapper.cpp \
../src/LPValues.cpp \
../src/NodeLPAggreg.cpp \
../src/Quality.cpp 

OBJS += \
./src/Complexity.o \
./src/Eval.o \
./src/LPAggreg.o \
./src/LPAggregWrapper.o \
./src/LPValues.o \
./src/NodeLPAggreg.o \
./src/Quality.o 

CPP_DEPS += \
./src/Complexity.d \
./src/Eval.d \
./src/LPAggreg.d \
./src/LPAggregWrapper.d \
./src/LPValues.d \
./src/NodeLPAggreg.d \
./src/Quality.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O1 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


