QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG(debug, debug|release): DESTDIR = $$PWD/build/debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
#
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$$PWD/lib/DLLSerialPort/build/debug/ -lDLLSerialPort

INCLUDEPATH += $$PWD/lib/DLLSerialPort/build
DEPENDPATH += $$PWD/lib/DLLSerialPort/build





unix:!macx|win32: LIBS += -L$$PWD/lib/DLLRestApi/build/debug/ -lDLLRestApi

INCLUDEPATH += $$PWD/lib/DLLRestApi/build
DEPENDPATH += $$PWD/lib/DLLRestApi/build
