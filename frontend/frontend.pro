QT       += core gui
QT       += network
QT       += serialport
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG(debug, debug|release): DESTDIR = $$PWD/build/debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balancewindow.cpp \
    changeaccountwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    modeselectwindow.cpp \
    optionswindow.cpp \
    receiptwindow.cpp \
    sessiondata.cpp \
    startwindow.cpp \
    transactionswindow.cpp \
    withdrawwindow.cpp

HEADERS += \
    balancewindow.h \
    changeaccountwindow.h \
    mainwindow.h \
    modeselectwindow.h \
    optionswindow.h \
    receiptwindow.h \
    sessiondata.h \
    startwindow.h \
    transactionswindow.h \
    withdrawwindow.h

FORMS += \
    balancewindow.ui \
    changeaccountwindow.ui \
    mainwindow.ui \
    modeselectwindow.ui \
    optionswindow.ui \
    receiptwindow.ui \
    startwindow.ui \
    transactionswindow.ui \
    withdrawwindow.ui
#
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$$PWD/lib/DLLRestApi/build/debug/ -lDLLRestApi

INCLUDEPATH += $$PWD/lib/DLLRestApi
DEPENDPATH += $$PWD/lib/DLLRestApi

unix:!macx|win32: LIBS += -L$$PWD/lib/DLLPinCode/build/debug/ -lDLLPinCode

INCLUDEPATH += $$PWD/lib/DLLPinCode
DEPENDPATH += $$PWD/lib/DLLPinCode

unix:!macx|win32: LIBS += -L$$PWD/lib/DLLSerialPort/build/debug/ -lDLLSerialPort

INCLUDEPATH += $$PWD/lib/DLLSerialPort
DEPENDPATH += $$PWD/lib/DLLSerialPort
