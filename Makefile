#!/usr/bin/make

# Compiler to use
CC = g++
CC_GDB = g++ -g
STD = c++0x

# Compile options
CFLAGS = -Wall
LIBPATH = /usr/local/lib/

# Program version
MAJOR_VERSION = 0
MINOR_VERSION = 0
PATCH_VERSION = 0
VERSION = ${MAJOR_VERSION}_${MINOR_VERSION}_${PATCH_VERSION}

# Output executable name
EXECNAME = dd2d_v${VERSION}
DEBUGNAME = ${EXECNAME}_gdb

dd2d:	O/defect.o O/main.o O/rotationMatrix.o O/slipPlaneStatistics.o O/strain.o O/vector3d.o O/dislocation.o O/matrix33.o O/simulateSingleSlipPlane.o O/standardSlipSystem.o O/stress.o O/dislocationSource.o O/parameter.o O/slipPlane.o O/statistics.o O/tools.o
	${CC} -std=${STD} ${CFLAGS} -o ${EXECNAME} O/defect.o O/main.o O/rotationMatrix.o O/slipPlaneStatistics.o O/strain.o O/vector3d.o O/dislocation.o O/matrix33.o O/simulateSingleSlipPlane.o O/standardSlipSystem.o O/stress.o O/dislocationSource.o O/parameter.o O/slipPlane.o O/statistics.o O/tools.o -L${LIBPATH}

dd2d_gdb:	O_GDB/defect.o O_GDB/main.o O_GDB/rotationMatrix.o O_GDB/slipPlaneStatistics.o O_GDB/strain.o O_GDB/vector3d.o O_GDB/dislocation.o O_GDB/matrix33.o O_GDB/simulateSingleSlipPlane.o O_GDB/standardSlipSystem.o O_GDB/stress.o O_GDB/dislocationSource.o O_GDB/parameter.o O_GDB/slipPlane.o O_GDB/statistics.o O_GDB/tools.o
	${CC_GDB} -std=${STD} ${CFLAGS} -o ${DEBUGNAME} O_GDB/defect.o O_GDB/main.o O_GDB/rotationMatrix.o O_GDB/slipPlaneStatistics.o O_GDB/strain.o O_GDB/vector3d.o O_GDB/dislocation.o O_GDB/matrix33.o O_GDB/simulateSingleSlipPlane.o O_GDB/standardSlipSystem.o O_GDB/stress.o O_GDB/dislocationSource.o O_GDB/parameter.o O_GDB/slipPlane.o O_GDB/statistics.o O_GDB/tools.o -L${LIBPATH}

O_files:
	${CC} -std=${STD} -c -o O/defect.o defect.cpp
	${CC} -std=${STD} -c -o O/dislocation.o dislocation.cpp 
	${CC} -std=${STD} -c -o O/dislocationSource.o dislocationSource.cpp 
	${CC} -std=${STD} -c -o O/main.o main.cpp
	${CC} -std=${STD} -c -o O/matrix33.o matrix33.cpp
	${CC} -std=${STD} -c -o O/parameter.o parameter.cpp
	${CC} -std=${STD} -c -o O/rotationMatrix.o rotationMatrix.cpp
	${CC} -std=${STD} -c -o O/simulateSingleSlipPlane.o simulateSingleSlipPlane.cpp
	${CC} -std=${STD} -c -o O/slipPlane.o slipPlane.cpp 
	${CC} -std=${STD} -c -o O/slipPlaneStatistics.o slipPlaneStatistics.cpp 
	${CC} -std=${STD} -c -o O/standardSlipSystem.o standardSlipSystem.cpp 
	${CC} -std=${STD} -c -o O/statistics.o statistics.cpp 
	${CC} -std=${STD} -c -o O/strain.o strain.cpp 
	${CC} -std=${STD} -c -o O/stress.o stress.cpp 
	${CC} -std=${STD} -c -o O/tools.o tools.cpp 
	${CC} -std=${STD} -c -o O/vector3d.o vector3d.cpp

O_GDB_files:
	${CC_GDB} -std=${STD} -c -o O_GDB/defect.o defect.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/dislocation.o dislocation.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/dislocationSource.o dislocationSource.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/main.o main.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/matrix33.o matrix33.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/parameter.o parameter.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/rotationMatrix.o rotationMatrix.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/simulateSingleSlipPlane.o simulateSingleSlipPlane.cpp
	${CC_GDB} -std=${STD} -c -o O_GDB/slipPlane.o slipPlane.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/slipPlaneStatistics.o slipPlaneStatistics.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/standardSlipSystem.o standardSlipSystem.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/statistics.o statistics.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/strain.o strain.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/stress.o stress.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/tools.o tools.cpp 
	${CC_GDB} -std=${STD} -c -o O_GDB/vector3d.o vector3d.cpp

build:
	make O_files
	make dd2d
	make O_GDB_files
	make dd2d_gdb

rebuild:
	make clean
	make build

clean:
	rm -f O/*
	rm -f O_GDB/*
	rm -f ${EXECNAME}
	rm -f ${DEBUGNAME}

default:
	rebuild
