TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vector3d.cpp \
    tools.cpp \
    stress.cpp \
    strain.cpp \
    statistics.cpp \
    slipPlaneStatistics.cpp \
    slipPlane.cpp \
    simulateSingleSlipPlane.cpp \
    rotationMatrix.cpp \
    parameter.cpp \
    matrix33.cpp \
    dislocationSource.cpp \
    dislocation.cpp \
    defect.cpp

HEADERS += \
    vector3d.h \
    tools.h \
    stress.h \
    strain.h \
    statistics.h \
    slipPlaneDefaults.h \
    slipPlane.h \
    simulateSingleSlipPlane.h \
    rotationMatrix.h \
    parameter.h \
    matrix33.h \
    dislocationSourceDefaults.h \
    dislocationSource.h \
    dislocationDefaults.h \
    dislocation.h \
    defect.h

