################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/Geometry\ Vector3D.cpp 

OBJS += \
./Math/Geometry\ Vector3D.o 

CPP_DEPS += \
./Math/Geometry\ Vector3D.d 


# Each subdirectory must supply rules for building sources it contributes
Math/Geometry\ Vector3D.o: ../Math/Geometry\ Vector3D.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"Math/Geometry Vector3D.d" -MT"Math/Geometry\ Vector3D.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


