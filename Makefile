#!/usr/bin/make

# Compiler to use
CC = g++
CC_GDB = g++ -g
STD = c++0x

# Compile options
PRODUCFLAGS = -Wall -ansi -W -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wunused-variables -fshort-enums -fno-common -Dinline= -O2

# Program version
MAJOR_VERSION = 0
MINOR_VERSION = 0
PATCH_VERSION = 0
VERSION = ${MAJOR_VERSION}_${MINOR_VERSION}_${PATCH_VERSION}

# Output executable name
EXECNAME = dd2d_v${VERSION}
DEBUGNAME = ${EXECNAME}_gdb

dd2d:	O/defect.o O/main.o O/rotationMatrix.o O/slipPlaneStatistics.o O/strain.o O/vector3d.o O/dislocation.o O/matrix33.o O/simulateSingleSlipPlane.o O/standardSlipSystem.o O/stress.o O/dislocationSource.o O/parameter.o O/slipPlane.o O/statistics.o O/tools.o
	${CC} ${PRODUCFLAGS} -o ${EXECNAME} O/defect.o O/main.o O/rotationMatrix.o O/slipPlaneStatistics.o O/strain.o O/vector3d.o O/dislocation.o O/matrix33.o O/simulateSingleSlipPlane.o O/standardSlipSystem.o O/stress.o O/dislocationSource.o O/parameter.o O/slipPlane.o O/statistics.o O/tools.o

dd2d_gdb:	O_GDBdefect.o O_GDBmain.o O_GDBrotationMatrix.o O_GDBslipPlaneStatistics.o O_GDBstrain.o O_GDBvector3d.o O_GDBdislocation.o O_GDBmatrix33.o O_GDBsimulateSingleSlipPlane.o O_GDBstandardSlipSystem.o O_GDBstress.o O_GDBdislocationSource.o O_GDBparameter.o O_GDBslipPlane.o O_GDBstatistics.o O_GDBtools.o
	${CC_GDB} ${PRODUCFLAGS} -o ${EXECNAME} O_GDBdefect.o O_GDBmain.o O_GDBrotationMatrix.o O_GDBslipPlaneStatistics.o O_GDBstrain.o O_GDBvector3d.o O_GDBdislocation.o O_GDBmatrix33.o O_GDBsimulateSingleSlipPlane.o O_GDBstandardSlipSystem.o O_GDBstress.o O_GDBdislocationSource.o O_GDBparameter.o O_GDBslipPlane.o O_GDBstatistics.o O_GDBtools.o

O/defect.o:	defect.cpp
  ${CC} -std=${STD} -o O/defect.o defect.cpp

O/dislocation.o:	dislocation.cpp
  ${CC} -std=${STD} -o O/dislocation.o dislocation.cpp

O/dislocationSource.o:	dislocationSource.cpp
  ${CC} -std=${STD} -o O/dislocationSource.o dislocationSource.cpp

O/main.o:	main.cpp
  ${CC} -std=${STD} -o O/main.o main.cpp

O/matrix33.o:	matrix33.cpp
  ${CC} -std=${STD} -o O/matrix33.o matrix33.cpp

O/parameter.o:	parameter.cpp
  ${CC} -std=${STD} -o O/parameter.o parameter.cpp

O/rotationMatrix.o:	rotationMatrix.cpp
  ${CC} -std=${STD} -o O/rotationMatrix.o rotationMatrix.cpp

O/simulateSingleSlipPlane.o:	simulateSingleSlipPlane.cpp
  ${CC} -std=${STD} -o O/simulateSingleSlipPlane.o simulateSingleSlipPlane.cpp

O/slipPlane.o:	slipPlane.cpp
  ${CC} -std=${STD} -o O/slipPlane.o slipPlane.cpp

O/slipPlaneStatistics.o:	slipPlaneStatistics.cpp
  ${CC} -std=${STD} -o O/slipPlaneStatistics.o slipPlaneStatistics.cpp

O/standardSlipSystem.o:	standardSlipSystem.cpp
  ${CC} -std=${STD} -o O/standardSlipSystem.o standardSlipSystem.cpp

O/statistics.o:	statistics.cpp
  ${CC} -std=${STD} -o O/statistics.o statistics.cpp

O/strain.o:	strain.cpp
  ${CC} -std=${STD} -o O/strain.o strain.cpp

O/stress.o:	stress.cpp
  ${CC} -std=${STD} -o O/stress.o stress.cpp

O/tools.o:	tools.cpp
  ${CC} -std=${STD} -o O/tools.o tools.cpp

O/vector3d.o:	vector3d.cpp
  ${CC} -std=${STD} -o O/vector3d.o vector3d.cpp

O_GDB/defect.o:	defect.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/defect.o defect.cpp

O_GDB/dislocation.o:	dislocation.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/dislocation.o dislocation.cpp

O_GDB/dislocationSource.o:	dislocationSource.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/dislocationSource.o dislocationSource.cpp

O_GDB/main.o:	main.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/main.o main.cpp

O_GDB/matrix33.o:	matrix33.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/matrix33.o matrix33.cpp

O_GDB/parameter.o:	parameter.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/parameter.o parameter.cpp

O_GDB/rotationMatrix.o:	rotationMatrix.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/rotationMatrix.o rotationMatrix.cpp

O_GDB/simulateSingleSlipPlane.o:	simulateSingleSlipPlane.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/simulateSingleSlipPlane.o simulateSingleSlipPlane.cpp

O_GDB/slipPlane.o:	slipPlane.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/slipPlane.o slipPlane.cpp

O_GDB/slipPlaneStatistics.o:	slipPlaneStatistics.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/slipPlaneStatistics.o slipPlaneStatistics.cpp

O_GDB/standardSlipSystem.o:	standardSlipSystem.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/standardSlipSystem.o standardSlipSystem.cpp

O_GDB/statistics.o:	statistics.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/statistics.o statistics.cpp

O_GDB/strain.o:	strain.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/strain.o strain.cpp

O_GDB/stress.o:	stress.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/stress.o stress.cpp

O_GDB/tools.o:	tools.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/tools.o tools.cpp

O_GDB/vector3d.o:	vector3d.cpp
  ${CC_GDB} -std=${STD} -o O_GDB/vector3d.o vector3d.cpp

build:
	make dd2d
	make dd2d_gdb

rebuild:
	make clean
	make build

clean:
	rm -f O/*
	rm -f O_GDB/*
	rm -f dd2d
	rm -f dd2d_gdb

