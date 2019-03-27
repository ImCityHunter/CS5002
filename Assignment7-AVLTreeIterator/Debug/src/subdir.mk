################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/avl_tree.c \
../src/binary_search_tree.c \
../src/binary_search_tree_main.c \
../src/binary_tree.c \
../src/binary_tree_iterator.c \
../src/binary_tree_node.c 

OBJS += \
./src/avl_tree.o \
./src/binary_search_tree.o \
./src/binary_search_tree_main.o \
./src/binary_tree.o \
./src/binary_tree_iterator.o \
./src/binary_tree_node.o 

C_DEPS += \
./src/avl_tree.d \
./src/binary_search_tree.d \
./src/binary_search_tree_main.d \
./src/binary_tree.d \
./src/binary_tree_iterator.d \
./src/binary_tree_node.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


