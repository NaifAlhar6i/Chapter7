#-------------------------------------------------
#
# Project created by QtCreator 2017-04-30T11:06:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = V2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 warn_off
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    Helper/renderer.cpp \
    GL/Particle/spherevao.cpp \
    GL/Particle/sphereshader.cpp \
    GL/glmanager.cpp \
    CL/cldevice.cpp \
    CL/clcontext.cpp \
    CL/clcommand.cpp \
    CL/clprogram.cpp \
    CL/clkernel.cpp \
    Helper/debugger.cpp \
    IO/xtcmanager.cpp \
    IO/datamanager.cpp \
    IO/gromanager.cpp \
    Memory/memorymanager.cpp \
    CL/clplatform.cpp \
    CL/clmemory.cpp \
    CL/cltask.cpp \
    Memory/datastructure.cpp \
    CL/clmanager.cpp \
    CL/clgltask.cpp \
    IO/xdrfile.c \
    IO/xdrfile_xtc.c \
    IO/stl.cpp \
    IO/mmf.cpp \
    glwidget.cpp \
    Helper/transformation.cpp \
    GL/Particle/particle.cpp \
    Helper/framerate.cpp \
    Helper/processing.cpp

HEADERS  += mainwindow.h \
    include/glheaders.h \
    include/constdata.h \
    include/structure.h \
    GL/glmanager.h \
    Helper/renderer.h \
    GL/Particle/spherevao.h \
    GL/Particle/sphereshader.h \
    include/clheaders.h \
    CL/cldevice.h \
    CL/clcontext.h \
    CL/clcommand.h \
    CL/clprogram.h \
    CL/clkernel.h \
    Helper/debugger.h \
    IO/xtcmanager.h \
    IO/datamanager.h \
    IO/gromanager.h \
    Memory/memorymanager.h \
    CL/clplatform.h \
    CL/clmemory.h \
    CL/cltask.h \
    Memory/datastructure.h \
    CL/clmanager.h \
    CL/clgltask.h \
    IO/xdrfile.h \
    IO/xdrfile_xtc.h \
    IO/stl.h \
    IO/mmf.h \
    glwidget.h \
    Helper/transformation.h \
    GL/Particle/particle.h \
    Helper/framerate.h \
    Helper/processing.h

FORMS    += mainwindow.ui


LIBS += -framework OpenCL
INCLUDEPATH = "/usr/local/Cellar/freeglut/2.8.1/include/"\
                "/usr/local/Cellar/glew/1.13.0/include/"\
                "/usr/local/Cellar/glm/0.9.7.1/include"\
                "/usr/local/Cellar/boost/1.62.0"\
                "/usr/local/Cellar/boost/1.62.0/include"\

LIBS += -L/usr/local/Cellar/boost/1.62.0/lib
LIBS += -lboost_system-mt -lboost_filesystem-mt -lboost_iostreams-mt -lboost_serialization-mt

RESOURCES += \
    kernels.qrc

