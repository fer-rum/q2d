#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T16:41:14
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

TARGET = q2d
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    model/ModelElement.cpp \
    patterns/Observable.cpp \
    model/Node.cpp \
    model/Conductor.cpp \
    model/Component.cpp \
    model/Model.cpp \
    Document.cpp \
    Project.cpp \
    Application.cpp \
    Main.cpp \
    ApplicationContext.cpp \
    ComponentType.cpp \
    gui/SchematicsTab.cpp \
    ComponentDescriptor.cpp \
    ComponentCategory.cpp \
    ComponentFactory.cpp \
    Constants.cpp \
    gui/SchematicsView.cpp \
    gui/SchematicsScene.cpp \
    gui/ComponentTreeView.cpp \
    model/PortDirection.cpp \
    PortDescriptor.cpp \
    gui/PortGraphicsItem.cpp

HEADERS  += MainWindow.h \
    model/ModelElement.h \
    patterns/Observable.h \
    patterns/Observer.h \
    model/Node.h \
    model/Conductor.h \
    model/PortDirection.h \
    model/Component.h \
    model/Model.h \
    Document.h \
    Project.h \
    Application.h \
    ApplicationContext.h \
    ComponentType.h \
    gui/SchematicsTab.h \
    ComponentDescriptor.h \
    ComponentCategory.h \
    ComponentFactory.h \
    Constants.h \
    gui/SchematicsView.h \
    gui/SchematicsScene.h \
    gui/ComponentTreeView.h \
    PortDescriptor.h \
    gui/PortGraphicsItem.h

FORMS    += MainWindow.ui \
    gui/SchematicsTab.ui
