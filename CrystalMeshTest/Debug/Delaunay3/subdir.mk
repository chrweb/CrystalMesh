################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Delaunay3/DelaunayTriangulation3Test.cpp \
../Delaunay3/TestComplexConstruction.cpp 

OBJS += \
./Delaunay3/DelaunayTriangulation3Test.o \
./Delaunay3/TestComplexConstruction.o 

CPP_DEPS += \
./Delaunay3/DelaunayTriangulation3Test.d \
./Delaunay3/TestComplexConstruction.d 


# Each subdirectory must supply rules for building sources it contributes
Delaunay3/%.o: ../Delaunay3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest" -I"/home/christoph/EclipseTestWorkspace0/C++/CrystalMesh/gTest/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


