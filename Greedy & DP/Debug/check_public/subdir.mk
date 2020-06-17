################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../check_public/p1.cpp \
../check_public/p2.cpp \
../check_public/p3.cpp \
../check_public/p4.cpp 

OBJS += \
./check_public/p1.o \
./check_public/p2.o \
./check_public/p3.o \
./check_public/p4.o 

CPP_DEPS += \
./check_public/p1.d \
./check_public/p2.d \
./check_public/p3.d \
./check_public/p4.d 


# Each subdirectory must supply rules for building sources it contributes
check_public/%.o: ../check_public/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


