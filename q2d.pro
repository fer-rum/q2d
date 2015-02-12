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
    gui/SchematicsTab.cpp \
    ComponentFactory.cpp \
    Constants.cpp \
    gui/SchematicsView.cpp \
    gui/SchematicsScene.cpp \
    gui/ComponentTreeView.cpp \
    metamodel/PortDescriptor.cpp \
    gui/PortGraphicsItem.cpp \
    gui/ComponentGraphicsItem.cpp \
    DocumentEntry.cpp \
    gui/WireGraphicsItem.cpp \
    gui/SchematicsSceneChild.cpp \
    JsonHelpers.cpp \
    model/ConfigurationBit.cpp \
    metamodel/ConfigurationBitDescriptor.cpp \
    metamodel/HierarchyElement.cpp \
    Enumerations.cpp \
    metamodel/Category.cpp \
    metamodel/ComponentElement.cpp \
    Util.cpp \
    metamodel/ComponentDescriptor.cpp \
    interfaces/Quantor.cpp \
    interfaces/QIContext.cpp \
    interfaces/QICircuit.cpp

HEADERS  +=\
    gui/MainWindow.h \
    model/ModelElement.h \
    patterns/Observable.h \
    patterns/Observer.h \
    model/Node.h \
    model/Conductor.h \
    model/Component.h \
    model/Model.h \
    Document.h \
    Project.h \
    Application.h \
    ApplicationContext.h \
    gui/SchematicsTab.h \
    ComponentFactory.h \
    Constants.h \
    gui/SchematicsView.h \
    gui/SchematicsScene.h \
    gui/ComponentTreeView.h \
    metamodel/PortDescriptor.h \
    gui/PortGraphicsItem.h \
    gui/ComponentGraphicsItem.h \
    DocumentEntry.h \
    gui/WireGraphicsItem.h \
    gui/SchematicsSceneChild.h \
    JsonHelpers.h \
    Enumerations.h \
    model/ConfigurationBit.h \
    metamodel/ConfigurationBitDescriptor.h \
    metamodel/Category.h \
    metamodel/Element.h \
    metamodel/HierarchyElement.h \
    metamodel/ComponentElement.h \
    Util.h \
    metamodel/ComponentDescriptor.h \
    interfaces/Quantor.h \
    interfaces/QIContext.h \
    interfaces/Iterator.h \
    interfaces/VariableType.h \
    interfaces/QICircuit.h

FORMS    +=\
    gui/MainWindow.ui \
    gui/SchematicsTab.ui
