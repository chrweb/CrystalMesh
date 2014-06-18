################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Subdiv3/FacetEdge.cpp 

OBJS += \
./Subdiv3/FacetEdge.o 

CPP_DEPS += \
./Subdiv3/FacetEdge.d 


# Each subdirectory must supply rules for building sources it contributes
Subdiv3/%.o: ../Subdiv3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


