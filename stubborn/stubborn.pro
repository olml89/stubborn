QT += widgets
QT -= gui

CONFIG += c++17
CONFIG -= app_bundle console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Config/config.cpp \
        Config/configbuilder.cpp \
        File/file.cpp \
        Process/process.cpp \
        Program/program.cpp \
        main.cpp \
        stubborn.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Config/config.h \
    Config/configbuilder.h \
    File/file.h \
    Process/process.h \
    Program/program.h \
    stubborn.h
