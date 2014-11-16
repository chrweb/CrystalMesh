#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Geometry_Plane3D.o \
	${OBJECTDIR}/Geometry_Point3D.o \
	${OBJECTDIR}/Geometry_Vector2D.o \
	${OBJECTDIR}/Geometry_Vector3D.o \
	${OBJECTDIR}/Mathbox.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a

${OBJECTDIR}/Geometry_Plane3D.o: Geometry_Plane3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Plane3D.o Geometry_Plane3D.cpp

${OBJECTDIR}/Geometry_Point3D.o: Geometry_Point3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Point3D.o Geometry_Point3D.cpp

${OBJECTDIR}/Geometry_Vector2D.o: Geometry_Vector2D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Vector2D.o Geometry_Vector2D.cpp

${OBJECTDIR}/Geometry_Vector3D.o: Geometry_Vector3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Vector3D.o Geometry_Vector3D.cpp

${OBJECTDIR}/Mathbox.o: Mathbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mathbox.o Mathbox.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/Tests/TestMath.o ${TESTDIR}/Tests/TestPlane3D.o ${TESTDIR}/Tests/TestPoint3D.o ${TESTDIR}/Tests/TestUPL.o ${TESTDIR}/Tests/TestVector3D.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../googletest/dist/Release/GNU-Linux-x86/libgoogletest.a 


${TESTDIR}/Tests/TestMath.o: Tests/TestMath.cpp 
	${MKDIR} -p ${TESTDIR}/Tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/Tests/TestMath.o Tests/TestMath.cpp


${TESTDIR}/Tests/TestPlane3D.o: Tests/TestPlane3D.cpp 
	${MKDIR} -p ${TESTDIR}/Tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/Tests/TestPlane3D.o Tests/TestPlane3D.cpp


${TESTDIR}/Tests/TestPoint3D.o: Tests/TestPoint3D.cpp 
	${MKDIR} -p ${TESTDIR}/Tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/Tests/TestPoint3D.o Tests/TestPoint3D.cpp


${TESTDIR}/Tests/TestUPL.o: Tests/TestUPL.cpp 
	${MKDIR} -p ${TESTDIR}/Tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/Tests/TestUPL.o Tests/TestUPL.cpp


${TESTDIR}/Tests/TestVector3D.o: Tests/TestVector3D.cpp 
	${MKDIR} -p ${TESTDIR}/Tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/Tests/TestVector3D.o Tests/TestVector3D.cpp


${OBJECTDIR}/Geometry_Plane3D_nomain.o: ${OBJECTDIR}/Geometry_Plane3D.o Geometry_Plane3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Geometry_Plane3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Plane3D_nomain.o Geometry_Plane3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Geometry_Plane3D.o ${OBJECTDIR}/Geometry_Plane3D_nomain.o;\
	fi

${OBJECTDIR}/Geometry_Point3D_nomain.o: ${OBJECTDIR}/Geometry_Point3D.o Geometry_Point3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Geometry_Point3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Point3D_nomain.o Geometry_Point3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Geometry_Point3D.o ${OBJECTDIR}/Geometry_Point3D_nomain.o;\
	fi

${OBJECTDIR}/Geometry_Vector2D_nomain.o: ${OBJECTDIR}/Geometry_Vector2D.o Geometry_Vector2D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Geometry_Vector2D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Vector2D_nomain.o Geometry_Vector2D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Geometry_Vector2D.o ${OBJECTDIR}/Geometry_Vector2D_nomain.o;\
	fi

${OBJECTDIR}/Geometry_Vector3D_nomain.o: ${OBJECTDIR}/Geometry_Vector3D.o Geometry_Vector3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Geometry_Vector3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geometry_Vector3D_nomain.o Geometry_Vector3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Geometry_Vector3D.o ${OBJECTDIR}/Geometry_Vector3D_nomain.o;\
	fi

${OBJECTDIR}/Mathbox_nomain.o: ${OBJECTDIR}/Mathbox.o Mathbox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Mathbox.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mathbox_nomain.o Mathbox.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Mathbox.o ${OBJECTDIR}/Mathbox_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmathbox.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
