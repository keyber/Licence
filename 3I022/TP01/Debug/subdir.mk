################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../etire.c \
../histogram.c \
../main.c \
../readpgm.c \
../writepgm.c 

OBJS += \
./etire.o \
./histogram.o \
./main.o \
./readpgm.o \
./writepgm.o 

C_DEPS += \
./etire.d \
./histogram.d \
./main.d \
./readpgm.d \
./writepgm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


