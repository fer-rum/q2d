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
    gui/MainWindow.cpp \
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
    metamodel/ComponentType.cpp \
    gui/SchematicsTab.cpp \
    metamodel/ComponentDescriptor.cpp \
    metamodel/ComponentCategory.cpp \
    ComponentFactory.cpp \
    Constants.cpp \
    gui/SchematicsView.cpp \
    gui/SchematicsScene.cpp \
    gui/ComponentTreeView.cpp \
    model/PortDirection.cpp \
    metamodel/PortDescriptor.cpp \
    gui/PortGraphicsItem.cpp \
    gui/ComponentGraphicsItem.cpp

HEADERS  +=\
    gui/MainWindow.h \
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
    metamodel/ComponentType.h \
    gui/SchematicsTab.h \
    metamodel/ComponentDescriptor.h \
    metamodel/ComponentCategory.h \
    ComponentFactory.h \
    Constants.h \
    gui/SchematicsView.h \
    gui/SchematicsScene.h \
    gui/ComponentTreeView.h \
    metamodel/PortDescriptor.h \
    gui/PortGraphicsItem.h \
    gui/ComponentGraphicsItem.h

FORMS    +=\
    gui/MainWindow.ui \
    gui/SchematicsTab.ui
