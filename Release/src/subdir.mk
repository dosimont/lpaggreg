################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Complexity.cpp \
../src/DLPAggreg.cpp \
../src/DLPAggreg2.cpp \
../src/DLPCut.cpp \
../src/Eval.cpp \
../src/LPAggregWrapper.cpp \
../src/NLPAggreg.cpp \
../src/NLPAggreg1.cpp \
../src/NLPAggreg2.cpp \
../src/NLPAggreg3.cpp \
../src/OLPAggreg.cpp \
../src/OLPAggreg1.cpp \
../src/OLPAggreg2.cpp \
../src/OLPAggreg3.cpp \
../src/Quality.cpp 

OBJS += \
./src/Complexity.o \
./src/DLPAggreg.o \
./src/DLPAggreg2.o \
./src/DLPCut.o \
./src/Eval.o \
./src/LPAggregWrapper.o \
./src/NLPAggreg.o \
./src/NLPAggreg1.o \
./src/NLPAggreg2.o \
./src/NLPAggreg3.o \
./src/OLPAggreg.o \
./src/OLPAggreg1.o \
./src/OLPAggreg2.o \
./src/OLPAggreg3.o \
./src/Quality.o 

CPP_DEPS += \
./src/Complexity.d \
./src/DLPAggreg.d \
./src/DLPAggreg2.d \
./src/DLPCut.d \
./src/Eval.d \
./src/LPAggregWrapper.d \
./src/NLPAggreg.d \
./src/NLPAggreg1.d \
./src/NLPAggreg2.d \
./src/NLPAggreg3.d \
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


