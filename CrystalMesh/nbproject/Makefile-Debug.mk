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
	${OBJECTDIR}/Corner.o \
	${OBJECTDIR}/Crater.o \
	${OBJECTDIR}/DelaunayTriangulation3D.o \
	${OBJECTDIR}/DelaunayVertex.o \
	${OBJECTDIR}/DirectedEdgeRing.o \
	${OBJECTDIR}/EdgeRing.o \
	${OBJECTDIR}/FacetEdge.o \
	${OBJECTDIR}/Fan.o \
	${OBJECTDIR}/Manifold.o \
	${OBJECTDIR}/Triangle.o \
	${OBJECTDIR}/Vertex.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

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
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdjacentDirectedEdgeRings.o AdjacentDirectedEdgeRings.cpp

${OBJECTDIR}/Corner.o: Corner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Corner.o Corner.cpp

${OBJECTDIR}/Crater.o: Crater.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Crater.o Crater.cpp

${OBJECTDIR}/DelaunayTriangulation3D.o: DelaunayTriangulation3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayTriangulation3D.o DelaunayTriangulation3D.cpp

${OBJECTDIR}/DelaunayVertex.o: DelaunayVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayVertex.o DelaunayVertex.cpp

${OBJECTDIR}/DirectedEdgeRing.o: DirectedEdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectedEdgeRing.o DirectedEdgeRing.cpp

${OBJECTDIR}/EdgeRing.o: EdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EdgeRing.o EdgeRing.cpp

${OBJECTDIR}/FacetEdge.o: FacetEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FacetEdge.o FacetEdge.cpp

${OBJECTDIR}/Fan.o: Fan.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Fan.o Fan.cpp

${OBJECTDIR}/Manifold.o: Manifold.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manifold.o Manifold.cpp

${OBJECTDIR}/Triangle.o: Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Triangle.o Triangle.cpp

${OBJECTDIR}/Vertex.o: Vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vertex.o Vertex.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/ComplexTest/TestEdgeRings.o ${TESTDIR}/ComplexTest/TestManifold.o ${TESTDIR}/ComplexTest/TestTopologicalOperations.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -pthread -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../googletest/dist/Debug/GNU-Linux-x86/libgoogletest.a ../Mathbox/dist/Debug/GNU-Linux-x86/libmathbox.a ../Toolbox/dist/Debug/GNU-Linux-x86/libtoolbox.a 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/DelaunayTest/TestCrater.o ${TESTDIR}/DelaunayTest/TestDelaunayVertex.o ${TESTDIR}/DelaunayTest/TestFan.o ${TESTDIR}/DelaunayTest/TestTriangle.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -pthread -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} ../googletest/dist/Debug/GNU-Linux-x86/libgoogletest.a ../Toolbox/dist/Debug/GNU-Linux-x86/libtoolbox.a ../Mathbox/dist/Debug/GNU-Linux-x86/libmathbox.a 


${TESTDIR}/ComplexTest/TestEdgeRings.o: ComplexTest/TestEdgeRings.cpp 
	${MKDIR} -p ${TESTDIR}/ComplexTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/ComplexTest/TestEdgeRings.o ComplexTest/TestEdgeRings.cpp


${TESTDIR}/ComplexTest/TestManifold.o: ComplexTest/TestManifold.cpp 
	${MKDIR} -p ${TESTDIR}/ComplexTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/ComplexTest/TestManifold.o ComplexTest/TestManifold.cpp


${TESTDIR}/ComplexTest/TestTopologicalOperations.o: ComplexTest/TestTopologicalOperations.cpp 
	${MKDIR} -p ${TESTDIR}/ComplexTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/ComplexTest/TestTopologicalOperations.o ComplexTest/TestTopologicalOperations.cpp


${TESTDIR}/DelaunayTest/TestCrater.o: DelaunayTest/TestCrater.cpp 
	${MKDIR} -p ${TESTDIR}/DelaunayTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/DelaunayTest/TestCrater.o DelaunayTest/TestCrater.cpp


${TESTDIR}/DelaunayTest/TestDelaunayVertex.o: DelaunayTest/TestDelaunayVertex.cpp 
	${MKDIR} -p ${TESTDIR}/DelaunayTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/DelaunayTest/TestDelaunayVertex.o DelaunayTest/TestDelaunayVertex.cpp


${TESTDIR}/DelaunayTest/TestFan.o: DelaunayTest/TestFan.cpp 
	${MKDIR} -p ${TESTDIR}/DelaunayTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/DelaunayTest/TestFan.o DelaunayTest/TestFan.cpp


${TESTDIR}/DelaunayTest/TestTriangle.o: DelaunayTest/TestTriangle.cpp 
	${MKDIR} -p ${TESTDIR}/DelaunayTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I. -I../gTest -I../gTest/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/DelaunayTest/TestTriangle.o DelaunayTest/TestTriangle.cpp


${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o: ${OBJECTDIR}/AdjacentDirectedEdgeRings.o AdjacentDirectedEdgeRings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AdjacentDirectedEdgeRings.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o AdjacentDirectedEdgeRings.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AdjacentDirectedEdgeRings.o ${OBJECTDIR}/AdjacentDirectedEdgeRings_nomain.o;\
	fi

${OBJECTDIR}/Corner_nomain.o: ${OBJECTDIR}/Corner.o Corner.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Corner.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Corner_nomain.o Corner.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Corner.o ${OBJECTDIR}/Corner_nomain.o;\
	fi

${OBJECTDIR}/Crater_nomain.o: ${OBJECTDIR}/Crater.o Crater.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Crater.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Crater_nomain.o Crater.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Crater.o ${OBJECTDIR}/Crater_nomain.o;\
	fi

${OBJECTDIR}/DelaunayTriangulation3D_nomain.o: ${OBJECTDIR}/DelaunayTriangulation3D.o DelaunayTriangulation3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DelaunayTriangulation3D.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayTriangulation3D_nomain.o DelaunayTriangulation3D.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DelaunayTriangulation3D.o ${OBJECTDIR}/DelaunayTriangulation3D_nomain.o;\
	fi

${OBJECTDIR}/DelaunayVertex_nomain.o: ${OBJECTDIR}/DelaunayVertex.o DelaunayVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DelaunayVertex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DelaunayVertex_nomain.o DelaunayVertex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DelaunayVertex.o ${OBJECTDIR}/DelaunayVertex_nomain.o;\
	fi

${OBJECTDIR}/DirectedEdgeRing_nomain.o: ${OBJECTDIR}/DirectedEdgeRing.o DirectedEdgeRing.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DirectedEdgeRing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectedEdgeRing_nomain.o DirectedEdgeRing.cpp;\
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
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EdgeRing_nomain.o EdgeRing.cpp;\
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
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FacetEdge_nomain.o FacetEdge.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FacetEdge.o ${OBJECTDIR}/FacetEdge_nomain.o;\
	fi

${OBJECTDIR}/Fan_nomain.o: ${OBJECTDIR}/Fan.o Fan.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Fan.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Fan_nomain.o Fan.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Fan.o ${OBJECTDIR}/Fan_nomain.o;\
	fi

${OBJECTDIR}/Manifold_nomain.o: ${OBJECTDIR}/Manifold.o Manifold.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Manifold.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Manifold_nomain.o Manifold.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Manifold.o ${OBJECTDIR}/Manifold_nomain.o;\
	fi

${OBJECTDIR}/Triangle_nomain.o: ${OBJECTDIR}/Triangle.o Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Triangle.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Triangle_nomain.o Triangle.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Triangle.o ${OBJECTDIR}/Triangle_nomain.o;\
	fi

${OBJECTDIR}/Vertex_nomain.o: ${OBJECTDIR}/Vertex.o Vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Vertex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DDEBUG -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vertex_nomain.o Vertex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Vertex.o ${OBJECTDIR}/Vertex_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
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
