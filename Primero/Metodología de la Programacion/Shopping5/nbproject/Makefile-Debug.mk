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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/src/DateTime.o \
	${OBJECTDIR}/src/Event.o \
	${OBJECTDIR}/src/EventSet.o \
	${OBJECTDIR}/src/Index.o \
	${OBJECTDIR}/src/Matrix.o \
	${OBJECTDIR}/src/Pair.o \
	${OBJECTDIR}/src/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/01.UnitDateTime.o \
	${TESTDIR}/tests/02.UnitEvent.o \
	${TESTDIR}/tests/03.UnitEventSet.o \
	${TESTDIR}/tests/04.UnitPair.o \
	${TESTDIR}/tests/05.UnitIndex.o \
	${TESTDIR}/tests/06.UnitMatrix.o \
	${TESTDIR}/tests/10.Integration.o

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
LDLIBSOPTIONS=../AnsiTerminal/dist/Debug/GNU-Linux/libansiterminal.a ../DataTable/dist/Debug/GNU-Linux/libdatatable.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping5

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping5: ../AnsiTerminal/dist/Debug/GNU-Linux/libansiterminal.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping5: ../DataTable/dist/Debug/GNU-Linux/libdatatable.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping5: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shopping5 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/DateTime.o: src/DateTime.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DateTime.o src/DateTime.cpp

${OBJECTDIR}/src/Event.o: src/Event.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Event.o src/Event.cpp

${OBJECTDIR}/src/EventSet.o: src/EventSet.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EventSet.o src/EventSet.cpp

${OBJECTDIR}/src/Index.o: src/Index.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Index.o src/Index.cpp

${OBJECTDIR}/src/Matrix.o: src/Matrix.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Matrix.o src/Matrix.cpp

${OBJECTDIR}/src/Pair.o: src/Pair.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Pair.o src/Pair.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../AnsiTerminal && ${MAKE}  -f Makefile CONF=Debug
	cd ../DataTable && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:
	cd ../Gtest && ${MAKE}  -f Makefile CONF=Debug

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/01.UnitDateTime.o ${TESTDIR}/tests/02.UnitEvent.o ${TESTDIR}/tests/03.UnitEventSet.o ${TESTDIR}/tests/04.UnitPair.o ${TESTDIR}/tests/05.UnitIndex.o ${TESTDIR}/tests/06.UnitMatrix.o ${TESTDIR}/tests/10.Integration.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -pthread  ../Gtest/dist/Debug/GNU-Linux/libgtest.a 


${TESTDIR}/tests/01.UnitDateTime.o: tests/01.UnitDateTime.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/01.UnitDateTime.o tests/01.UnitDateTime.cpp


${TESTDIR}/tests/02.UnitEvent.o: tests/02.UnitEvent.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/02.UnitEvent.o tests/02.UnitEvent.cpp


${TESTDIR}/tests/03.UnitEventSet.o: tests/03.UnitEventSet.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/03.UnitEventSet.o tests/03.UnitEventSet.cpp


${TESTDIR}/tests/04.UnitPair.o: tests/04.UnitPair.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/04.UnitPair.o tests/04.UnitPair.cpp


${TESTDIR}/tests/05.UnitIndex.o: tests/05.UnitIndex.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/05.UnitIndex.o tests/05.UnitIndex.cpp


${TESTDIR}/tests/06.UnitMatrix.o: tests/06.UnitMatrix.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/06.UnitMatrix.o tests/06.UnitMatrix.cpp


${TESTDIR}/tests/10.Integration.o: tests/10.Integration.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -D__INTEGRATION__ -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/10.Integration.o tests/10.Integration.cpp


${OBJECTDIR}/src/DateTime_nomain.o: ${OBJECTDIR}/src/DateTime.o src/DateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/DateTime.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DateTime_nomain.o src/DateTime.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/DateTime.o ${OBJECTDIR}/src/DateTime_nomain.o;\
	fi

${OBJECTDIR}/src/Event_nomain.o: ${OBJECTDIR}/src/Event.o src/Event.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Event.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Event_nomain.o src/Event.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Event.o ${OBJECTDIR}/src/Event_nomain.o;\
	fi

${OBJECTDIR}/src/EventSet_nomain.o: ${OBJECTDIR}/src/EventSet.o src/EventSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/EventSet.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EventSet_nomain.o src/EventSet.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/EventSet.o ${OBJECTDIR}/src/EventSet_nomain.o;\
	fi

${OBJECTDIR}/src/Index_nomain.o: ${OBJECTDIR}/src/Index.o src/Index.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Index.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Index_nomain.o src/Index.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Index.o ${OBJECTDIR}/src/Index_nomain.o;\
	fi

${OBJECTDIR}/src/Matrix_nomain.o: ${OBJECTDIR}/src/Matrix.o src/Matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Matrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Matrix_nomain.o src/Matrix.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Matrix.o ${OBJECTDIR}/src/Matrix_nomain.o;\
	fi

${OBJECTDIR}/src/Pair_nomain.o: ${OBJECTDIR}/src/Pair.o src/Pair.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Pair.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Pair_nomain.o src/Pair.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Pair.o ${OBJECTDIR}/src/Pair_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../MPTest/include -I../googletest-master/googletest/include -Iinclude -I../DataTable/include -I../AnsiTerminal/include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
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

# Subprojects
.clean-subprojects:
	cd ../AnsiTerminal && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../DataTable && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
