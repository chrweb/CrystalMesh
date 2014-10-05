################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/CrystalMesh\ Math.cpp \
../Math/Geometry\ Plane3D.cpp \
../Math/Geometry\ Point.cpp \
../Math/Geometry\ Vector3D.cpp 

OBJS += \
./Math/CrystalMesh\ Math.o \
./Math/Geometry\ Plane3D.o \
./Math/Geometry\ Point.o \
./Math/Geometry\ Vector3D.o 

CPP_DEPS += \
./Math/CrystalMesh\ Math.d \
./Math/Geometry\ Plane3D.d \
./Math/Geometry\ Point.d \
./Math/Geometry\ Vector3D.d 


# Each subdirectory must supply rules for building sources it contributes
Math/CrystalMesh\ Math.o: ../Math/CrystalMesh\ Math.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -DDEBUG -MMD -MP -MF"Math/CrystalMesh Math.d" -MT"Math/CrystalMesh\ Math.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Math/Geometry\ Plane3D.o: ../Math/Geometry\ Plane3D.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -DDEBUG -MMD -MP -MF"Math/Geometry Plane3D.d" -MT"Math/Geometry\ Plane3D.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Math/Geometry\ Point.o: ../Math/Geometry\ Point.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -DDEBUG -MMD -MP -MF"Math/Geometry Point.d" -MT"Math/Geometry\ Point.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Math/Geometry\ Vector3D.o: ../Math/Geometry\ Vector3D.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -DDEBUG -MMD -MP -MF"Math/Geometry Vector3D.d" -MT"Math/Geometry\ Vector3D.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


