################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../atm.c \
../card.c \
../main.c \
../str_parse.c 

O_SRCS += \
../atm.o \
../main.o \
../str_parse.o 

OBJS += \
./atm.o \
./card.o \
./main.o \
./str_parse.o 

C_DEPS += \
./atm.d \
./card.d \
./main.d \
./str_parse.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


