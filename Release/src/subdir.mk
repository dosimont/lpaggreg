################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Eval.cpp \
../src/LPAggregWrapper.cpp \
../src/OLPAggreg.cpp \
../src/OLPAggreg1.cpp \
../src/OLPAggreg2.cpp \
../src/OLPAggreg3.cpp \
../src/Quality.cpp 

OBJS += \
./src/Eval.o \
./src/LPAggregWrapper.o \
./src/OLPAggreg.o \
./src/OLPAggreg1.o \
./src/OLPAggreg2.o \
./src/OLPAggreg3.o \
./src/Quality.o 

CPP_DEPS += \
./src/Eval.d \
./src/LPAggregWrapper.d \
./src/OLPAggreg.d \
./src/OLPAggreg1.d \
./src/OLPAggreg2.d \
./src/OLPAggreg3.d \
./src/Quality.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O1 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


