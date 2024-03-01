QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = JesusAha
QMAKE_TARGET_PRODUCT = SmartCalc_21
QMAKE_TARGET_COPYRIGHT = JesusAha_school_21

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../1.c \
    ../credits.c \
    ../deposid.c \
    ../sort.c \
    ../calculation.c \
    credit.cpp \
    depos.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../c.h \
    ../credits.h \
    ../deposid.h \
    credit.h \
    depos.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit.ui \
    depos.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
