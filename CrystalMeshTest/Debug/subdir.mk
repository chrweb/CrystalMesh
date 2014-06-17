################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/src/gtest-all.cc \
/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/src/gtest_main.cc 

OBJS += \
./gtest-all.o \
./gtest_main.o 

CC_DEPS += \
./gtest-all.d \
./gtest_main.d 


# Each subdirectory must supply rules for building sources it contributes
gtest-all.o: /home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/src/gtest-all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest" -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gtest_main.o: /home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/src/gtest_main.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest" -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


