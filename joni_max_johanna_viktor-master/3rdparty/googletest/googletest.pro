TEMPLATE = lib
CONFIG += staticlib
INCLUDEPATH += \
    googletest \
    googlemock \
    googletest/include \
    googlemock/include
SOURCES += \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc
LIBS += -lpthread
TARGET = googletest
