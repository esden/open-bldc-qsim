#-------------------------------------------------
#
# Project created by QtCreator 2012-04-17T16:36:51
#
#-------------------------------------------------

QT       += core gui opengl printsupport widgets

TARGET = open-bldc-qsim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    signalplot.cpp \
    simrunner.cpp \
    sim.cpp \
    csim/src/misc_utils.c \
    csim/src/dyn_model.c \
    csim/src/controller.c \
    csim/src/switch.c

HEADERS  += mainwindow.h \
    qcustomplot.h \
    signalplot.h \
    simrunner.h \
    sim.h \
    csim/src/misc_utils.h \
    csim/src/dyn_model.h \
    csim/src/controller.h \
    csim/src/switch.h

FORMS    += mainwindow.ui

macx {
    LIBS += -L/usr/local/lib
    INCLUDEPATH += /usr/local/include
}

LIBS += -lgsl

linux {
    LIBS += -lgslcblas
}


RESOURCES += \
    main.qrc
