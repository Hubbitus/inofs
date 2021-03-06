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
	${OBJECTDIR}/src/InoFS.o \
	${OBJECTDIR}/src/InoFS.exceptions.o \
	${OBJECTDIR}/src/InoFS_options.o \
	${OBJECTDIR}/src/Utils/Singleton/Singleton.o \
	${OBJECTDIR}/src/Utils/log/log.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/pstream_exec/pstream_exec.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f2

${TESTDIR}/TestFiles/f2: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/InoFS.o: src/InoFS.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS.o src/InoFS.cpp

${OBJECTDIR}/src/InoFS.exceptions.o: src/InoFS.exceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS.exceptions.o src/InoFS.exceptions.cpp

${OBJECTDIR}/src/InoFS_options.o: src/InoFS_options.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS_options.o src/InoFS_options.cpp

${OBJECTDIR}/src/Utils/Singleton/Singleton.o: src/Utils/Singleton/Singleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Utils/Singleton
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Utils/Singleton/Singleton.o src/Utils/Singleton/Singleton.cpp

${OBJECTDIR}/src/Utils/log/log.o: src/Utils/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Utils/log
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Utils/log/log.o src/Utils/log/log.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/pstream_exec/pstream_exec.o: src/pstream_exec/pstream_exec.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pstream_exec
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pstream_exec/pstream_exec.o src/pstream_exec/pstream_exec.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f3: ${TESTDIR}/src/tests/psexectest.o ${TESTDIR}/src/tests/psexectestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/src/tests/psexectest.o: src/tests/psexectest.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/src/tests/psexectest.o src/tests/psexectest.cpp


${TESTDIR}/src/tests/psexectestrunner.o: src/tests/psexectestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/src/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/src/tests/psexectestrunner.o src/tests/psexectestrunner.cpp


${OBJECTDIR}/src/InoFS_nomain.o: ${OBJECTDIR}/src/InoFS.o src/InoFS.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/InoFS.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS_nomain.o src/InoFS.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/InoFS.o ${OBJECTDIR}/src/InoFS_nomain.o;\
	fi

${OBJECTDIR}/src/InoFS.exceptions_nomain.o: ${OBJECTDIR}/src/InoFS.exceptions.o src/InoFS.exceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/InoFS.exceptions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS.exceptions_nomain.o src/InoFS.exceptions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/InoFS.exceptions.o ${OBJECTDIR}/src/InoFS.exceptions_nomain.o;\
	fi

${OBJECTDIR}/src/InoFS_options_nomain.o: ${OBJECTDIR}/src/InoFS_options.o src/InoFS_options.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/InoFS_options.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InoFS_options_nomain.o src/InoFS_options.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/InoFS_options.o ${OBJECTDIR}/src/InoFS_options_nomain.o;\
	fi

${OBJECTDIR}/src/Utils/Singleton/Singleton_nomain.o: ${OBJECTDIR}/src/Utils/Singleton/Singleton.o src/Utils/Singleton/Singleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Utils/Singleton
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Utils/Singleton/Singleton.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Utils/Singleton/Singleton_nomain.o src/Utils/Singleton/Singleton.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Utils/Singleton/Singleton.o ${OBJECTDIR}/src/Utils/Singleton/Singleton_nomain.o;\
	fi

${OBJECTDIR}/src/Utils/log/log_nomain.o: ${OBJECTDIR}/src/Utils/log/log.o src/Utils/log/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Utils/log
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Utils/log/log.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Utils/log/log_nomain.o src/Utils/log/log.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Utils/log/log.o ${OBJECTDIR}/src/Utils/log/log_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/src/pstream_exec/pstream_exec_nomain.o: ${OBJECTDIR}/src/pstream_exec/pstream_exec.o src/pstream_exec/pstream_exec.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pstream_exec
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pstream_exec/pstream_exec.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pstream_exec/pstream_exec_nomain.o src/pstream_exec/pstream_exec.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pstream_exec/pstream_exec.o ${OBJECTDIR}/src/pstream_exec/pstream_exec_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f2

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
