################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Subdiv3/DirectedEdgeRing.cpp \
../Subdiv3/EdgeRing.cpp \
../Subdiv3/FacetEdge.cpp \
../Subdiv3/Manifold.cpp \
../Subdiv3/Vertex.cpp 

OBJS += \
./Subdiv3/DirectedEdgeRing.o \
./Subdiv3/EdgeRing.o \
./Subdiv3/FacetEdge.o \
./Subdiv3/Manifold.o \
./Subdiv3/Vertex.o 

CPP_DEPS += \
./Subdiv3/DirectedEdgeRing.d \
./Subdiv3/EdgeRing.d \
./Subdiv3/FacetEdge.d \
./Subdiv3/Manifold.d \
./Subdiv3/Vertex.d 


# Each subdirectory must supply rules for building sources it contributes
Subdiv3/%.o: ../Subdiv3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


