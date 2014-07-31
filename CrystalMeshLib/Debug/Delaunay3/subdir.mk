################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Delaunay3/ComplexConstruction.cpp \
../Delaunay3/DelaunayTriangulation3D.cpp \
../Delaunay3/Primitives.cpp 

OBJS += \
./Delaunay3/ComplexConstruction.o \
./Delaunay3/DelaunayTriangulation3D.o \
./Delaunay3/Primitives.o 

CPP_DEPS += \
./Delaunay3/ComplexConstruction.d \
./Delaunay3/DelaunayTriangulation3D.d \
./Delaunay3/Primitives.d 


# Each subdirectory must supply rules for building sources it contributes
Delaunay3/%.o: ../Delaunay3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


