include(gtest_dependency.pri)

TARGET = unit

TEMPLATE = app
CONFIG += c++11
QT += quick charts

QMAKE_CXXFLAGS += -Wno-sign-compare

# Test files
SOURCES +=  main.cpp \
            basechartmodel_test.cpp \
            dummy_test.cpp \
            linechart_test.cpp \
            linechartmodel_test.cpp


# Source Files
INCLUDEPATH += ../../application/src

SOURCES +=  ../../application/src/basechartmodel.cpp \
            ../../application/src/linechart.cpp \
            ../../application/src/linechartmodel.cpp

HEADERS +=  ../../application/src/basechartmodel.h \
            ../../application/src/linechart.h \
            ../../application/src/linechartmodel.h


