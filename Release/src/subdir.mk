################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LPAggreg.cpp \
../src/LPAggregWrapper.cpp \
../src/ScalarLPAggreg.cpp \
../src/VectorLPAggreg.cpp 

OBJS += \
./src/LPAggreg.o \
./src/LPAggregWrapper.o \
./src/ScalarLPAggreg.o \
./src/VectorLPAggreg.o 

CPP_DEPS += \
./src/LPAggreg.d \
./src/LPAggregWrapper.d \
./src/ScalarLPAggreg.d \
./src/VectorLPAggreg.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/java/latest/include -I/usr/java/latest/include/linux -O1 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


