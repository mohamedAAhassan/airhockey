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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release_Linux/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Point2.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/Pak.o \
	${OBJECTDIR}/src/polyscript/polygon.o \
	${OBJECTDIR}/src/polyscript/token.o \
	${OBJECTDIR}/src/polyscript/scanner.o \
	${OBJECTDIR}/src/polyscript/parser.o \
	${OBJECTDIR}/src/Kij.o \
	${OBJECTDIR}/src/graphics.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglut

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release_Linux.mk dist/Release_Linux/${PLATFORM}/airhockey

dist/Release_Linux/${PLATFORM}/airhockey: ${OBJECTFILES}
	${MKDIR} -p dist/Release_Linux/${PLATFORM}
	${LINK.cc} -o dist/Release_Linux/${PLATFORM}/airhockey ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Point2.o: src/Point2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Point2.o src/Point2.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/Pak.o: src/Pak.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Pak.o src/Pak.cpp

${OBJECTDIR}/src/polyscript/polygon.o: src/polyscript/polygon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/polyscript
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/polyscript/polygon.o src/polyscript/polygon.cpp

${OBJECTDIR}/src/polyscript/token.o: src/polyscript/token.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/polyscript
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/polyscript/token.o src/polyscript/token.cpp

${OBJECTDIR}/src/polyscript/scanner.o: src/polyscript/scanner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/polyscript
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/polyscript/scanner.o src/polyscript/scanner.cpp

${OBJECTDIR}/src/polyscript/parser.o: src/polyscript/parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/polyscript
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/polyscript/parser.o src/polyscript/parser.cpp

${OBJECTDIR}/src/Kij.o: src/Kij.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Kij.o src/Kij.cpp

${OBJECTDIR}/src/graphics.o: src/graphics.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/graphics.o src/graphics.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release_Linux
	${RM} dist/Release_Linux/${PLATFORM}/airhockey

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
