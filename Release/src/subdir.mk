################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Complexity.cpp \
../src/Eval.cpp \
../src/LPAggreg.cpp \
../src/LPAggregWrapper.cpp \
../src/MLPAggregWrapper.cpp \
../src/MatrixLPAggreg.cpp \
../src/MatrixNodeLPAggreg.cpp \
../src/NodeLPAggreg.cpp \
../src/NodeLPAggregWrapper.cpp \
../src/Quality.cpp \
../src/ScalarLPAggreg.cpp \
../src/ScalarNodeLPAggreg.cpp \
../src/VLPAggregWrapper.cpp \
../src/VectorLPAggreg.cpp \
../src/VectorNodeLPAggreg.cpp 

OBJS += \
./src/Complexity.o \
./src/Eval.o \
./src/LPAggreg.o \
./src/LPAggregWrapper.o \
./src/MLPAggregWrapper.o \
./src/MatrixLPAggreg.o \
./src/MatrixNodeLPAggreg.o \
./src/NodeLPAggreg.o \
./src/NodeLPAggregWrapper.o \
./src/Quality.o \
./src/ScalarLPAggreg.o \
./src/ScalarNodeLPAggreg.o \
./src/VLPAggregWrapper.o \
./src/VectorLPAggreg.o \
./src/VectorNodeLPAggreg.o 

CPP_DEPS += \
./src/Complexity.d \
./src/Eval.d \
./src/LPAggreg.d \
./src/LPAggregWrapper.d \
./src/MLPAggregWrapper.d \
./src/MatrixLPAggreg.d \
./src/MatrixNodeLPAggreg.d \
./src/NodeLPAggreg.d \
./src/NodeLPAggregWrapper.d \
./src/Quality.d \
./src/ScalarLPAggreg.d \
./src/ScalarNodeLPAggreg.d \
./src/VLPAggregWrapper.d \
./src/VectorLPAggreg.d \
./src/VectorNodeLPAggreg.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O1 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


