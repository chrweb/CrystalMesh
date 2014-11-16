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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AdjacentDirectedEdgeRings.o \
	${OBJECTDIR}/ComplexConstruction.o \
	${OBJECTDIR}/DelaunayTriangulation3D.o \
	${OBJECTDIR}/DirectedEdgeRing.o \
	${OBJECTDIR}/EdgeRing.o \
	${OBJECTDIR}/FacetEdge.o \
	${OBJECTDIR}/Manifold.o \
	${OBJECTDIR}/Primitives.o \
	${OBJECTDIR}/Vertex.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a

${OBJECTDIR}/AdjacentDirectedEdgeRings.o: AdjacentDirectedEdgeRings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdjacentDirectedEdgeRings.o AdjacentDirectedEdgeRings.cpp

${OBJECTDIR}/ComplexConstruction.o: ComplexConstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComplexConstruction.o ComplexConstruction.cpp

${OBJECTDIR}/DelaunayTriangulation3D.o: DelaunayTriangulation3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayTriangulation3D.o DelaunayTriangulation3D.cpp

${OBJECTDIR}/DirectedEdgeRing.o: DirectedEdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectedEdgeRing.o DirectedEdgeRing.cpp

${OBJECTDIR}/EdgeRing.o: EdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EdgeRing.o EdgeRing.cpp

${OBJECTDIR}/FacetEdge.o: FacetEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FacetEdge.o FacetEdge.cpp

${OBJECTDIR}/Manifold.o: Manifold.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manifold.o Manifold.cpp

${OBJECTDIR}/Primitives.o: Primitives.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Primitives.o Primitives.cpp

${OBJECTDIR}/Vertex.o: Vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vertex.o Vertex.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../googletest/dist/Debug/GNU-Linux-x86/libgoogletest.a 


${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o: ${OBJECTDIR}/AdjacentDirectedEdgeRings.o AdjacentDirectedEdgeRings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AdjacentDirectedEdgeRings.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o AdjacentDirectedEdgeRings.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AdjacentDirectedEdgeRings.o ${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o;\
	fi

${OBJECTDIR}/ComplexConstruction_nomain.o: ${OBJECTDIR}/ComplexConstruction.o ComplexConstruction.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ComplexConstruction.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComplexConstruction_nomain.o ComplexConstruction.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ComplexConstruction.o ${OBJECTDIR}/ComplexConstruction_nomain.o;\
	fi

${OBJECTDIR}/DelaunayTriangulation3D_nomain.o: ${OBJECTDIR}/DelaunayTriangulation3D.o DelaunayTriangulation3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DelaunayTriangulation3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayTriangulation3D_nomain.o DelaunayTriangulation3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DelaunayTriangulation3D.o ${OBJECTDIR}/DelaunayTriangulation3D_nomain.o;\
	fi

${OBJECTDIR}/DirectedEdgeRing_nomain.o: ${OBJECTDIR}/DirectedEdgeRing.o DirectedEdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DirectedEdgeRing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectedEdgeRing_nomain.o DirectedEdgeRing.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DirectedEdgeRing.o ${OBJECTDIR}/DirectedEdgeRing_nomain.o;\
	fi

${OBJECTDIR}/EdgeRing_nomain.o: ${OBJECTDIR}/EdgeRing.o EdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/EdgeRing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EdgeRing_nomain.o EdgeRing.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/EdgeRing.o ${OBJECTDIR}/EdgeRing_nomain.o;\
	fi

${OBJECTDIR}/FacetEdge_nomain.o: ${OBJECTDIR}/FacetEdge.o FacetEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FacetEdge.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FacetEdge_nomain.o FacetEdge.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FacetEdge.o ${OBJECTDIR}/FacetEdge_nomain.o;\
	fi

${OBJECTDIR}/Manifold_nomain.o: ${OBJECTDIR}/Manifold.o Manifold.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Manifold.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manifold_nomain.o Manifold.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Manifold.o ${OBJECTDIR}/Manifold_nomain.o;\
	fi

${OBJECTDIR}/Primitives_nomain.o: ${OBJECTDIR}/Primitives.o Primitives.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Primitives.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Primitives_nomain.o Primitives.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Primitives.o ${OBJECTDIR}/Primitives_nomain.o;\
	fi

${OBJECTDIR}/Vertex_nomain.o: ${OBJECTDIR}/Vertex.o Vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Vertex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vertex_nomain.o Vertex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Vertex.o ${OBJECTDIR}/Vertex_nomain.o;\
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
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcrystalmesh.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
