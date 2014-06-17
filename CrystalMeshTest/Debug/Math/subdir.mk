################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/TestVector3D.cpp 

OBJS += \
./Math/TestVector3D.o 

CPP_DEPS += \
./Math/TestVector3D.d 


# Each subdirectory must supply rules for building sources it contributes
Math/%.o: ../Math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest" -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


