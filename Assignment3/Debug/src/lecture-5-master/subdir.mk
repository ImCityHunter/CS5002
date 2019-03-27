################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lecture-5-master/linked_array.c \
../src/lecture-5-master/linked_list.c \
../src/lecture-5-master/linked_list_crawler_main.c \
../src/lecture-5-master/linked_list_iterator.c \
../src/lecture-5-master/linked_node.c 

OBJS += \
./src/lecture-5-master/linked_array.o \
./src/lecture-5-master/linked_list.o \
./src/lecture-5-master/linked_list_crawler_main.o \
./src/lecture-5-master/linked_list_iterator.o \
./src/lecture-5-master/linked_node.o 

C_DEPS += \
./src/lecture-5-master/linked_array.d \
./src/lecture-5-master/linked_list.d \
./src/lecture-5-master/linked_list_crawler_main.d \
./src/lecture-5-master/linked_list_iterator.d \
./src/lecture-5-master/linked_node.d 


# Each subdirectory must supply rules for building sources it contributes
src/lecture-5-master/%.o: ../src/lecture-5-master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


