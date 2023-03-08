TARGET = application

QT += quick charts widgets quickcontrols2
CONFIG += c++1z

INCLUDEPATH += ../3rdparty/xml2json/include

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src

SOURCES += \
        main.cpp \
        src/autocompleter.cpp \
        src/basechartmodel.cpp \
        src/fileio.cpp \
        src/fmiclient.cpp \
        src/linechart.cpp \
        src/linechartmodel.cpp \
        src/httpclient.cpp  \
        src/fingridclient.cpp \
        src/piechartmodel.cpp \
        src/presetcontroller.cpp \
        src/uicontroller.cpp

HEADERS += \
        src/autocompleter.h \
        src/basechartmodel.h \
        src/fileio.h \
        src/fmiclient.h \
        src/linechart.h \
        src/linechartmodel.h \
        src/httpclient.h \
        src/fingridclient.h \
        src/piechartmodel.h \
        src/presetcontroller.h \
        src/uicontroller.h



RESOURCES += \
        data.qrc \
        qml.qrc

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

#Copy used files to build directory
QMAKE_POST_LINK += $(COPY_DIR) $$shell_path($$PWD/data) $$shell_path($$DESTDIR/data)



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
