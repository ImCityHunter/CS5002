################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/array_deque.c \
../src/array_list.c \
../src/messagepriorityqueue.c \
../src/messagepriorityqueue_main.c 

OBJS += \
./src/array_deque.o \
./src/array_list.o \
./src/messagepriorityqueue.o \
./src/messagepriorityqueue_main.o 

C_DEPS += \
./src/array_deque.d \
./src/array_list.d \
./src/messagepriorityqueue.d \
./src/messagepriorityqueue_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


