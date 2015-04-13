#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T16:41:14
#
#-------------------------------------------------

message(Base output directory is $$OUT_PWD)
# paths to seperately build parts
picosatDir = "$$OUT_PWD/picosat-960"
quantorDir = "$$OUT_PWD/quantor-3.2"

!exists($$picosatDir){
    downPico = $$prompt(Could not find picosat. Download? [N/y])
    equals(downPico, "y") {
        system(wget -q http://fmv.jku.at/picosat/picosat-960.tar.gz && tar -xaf picosat-960.tar.gz)
    } else {
        error(No picosat directory)
    }
} {
message(picosat directory is $$picosatDir)
!exists($$picosatDir/config.h) {
    system(cd $$picosatDir && ./configure && make config.h)
}


!exists($$quantorDir){
    downQuantor = $$prompt(Could not find quantor. Download? [N/y])
    equals(downQuantor, "y") {
        system(wget -q http://fmv.jku.at/quantor/quantor-3.2.tar.gz && tar -xaf quantor-3.2.tar.gz)
    } else {
        error(No quantor directory)
    }
}
message(quantor directory is $$quantorDir)
!exists($$quantorDir/config.h) {
    system(cd $$quantorDir && ./configure && make options.c)
}

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt c++11 debug
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

TARGET = q2d
TEMPLATE = app


SOURCES +=\
    gui/MainWindow.cpp \
    model/ModelElement.cpp \
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
    gui/ComponentTreeView.cpp \
    metamodel/PortDescriptor.cpp \
    gui/PortGraphicsItem.cpp \
    gui/ComponentGraphicsItem.cpp \
    DocumentEntry.cpp \
    gui/WireGraphicsItem.cpp \
    JsonHelpers.cpp \
    metamodel/ConfigurationBitDescriptor.cpp \
    metamodel/HierarchyElement.cpp \
    Enumerations.cpp \
    metamodel/Category.cpp \
    metamodel/ComponentElement.cpp \
    Util.cpp \
    metamodel/ComponentDescriptor.cpp \
    interfaces/Quantor.cpp \
    interfaces/quantor/QIContext.cpp \
    interfaces/quantor/Quantorizer.cpp \
    interfaces/quantor/Result.cpp \
# including relevant picosat foles
    $$picosatDir/picosat.c \
    $$picosatDir/version.c \
#including relevant quantor files
    $$quantorDir/quantor.c \
    gui/QuantorResultDialog.cpp \
    MapModel.cpp \
    model/Port.cpp \
    gui/Schematic.cpp \
    gui/SchematicElement.cpp \
    metamodel/FunctionDescriptor.cpp \
    factories/DocumentEntryFactory.cpp \
    factories/GIFactory.cpp \
    gui/ComponentDetailView.cpp \
    PortListModel.cpp \
    gui/ModulePortGI.cpp \
    model/ModuleInterface.cpp \
    core/Identifiable.cpp \
    factories/ToolTipFactory.cpp

HEADERS  +=\
    gui/MainWindow.h \
    model/ModelElement.h \
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
    gui/ComponentTreeView.h \
    metamodel/PortDescriptor.h \
    gui/PortGraphicsItem.h \
    gui/ComponentGraphicsItem.h \
    DocumentEntry.h \
    gui/WireGraphicsItem.h \
    JsonHelpers.h \
    Enumerations.h \
    metamodel/ConfigurationBitDescriptor.h \
    metamodel/Category.h \
    metamodel/Element.h \
    metamodel/HierarchyElement.h \
    metamodel/ComponentElement.h \
    Util.h \
    metamodel/ComponentDescriptor.h \
    interfaces/Quantor.h \
    interfaces/VariableType.h \
    interfaces/quantor/ParseException.h \
    interfaces/quantor/QIContext.h \
    interfaces/quantor/Quantorizer.hpp \
    interfaces/quantor/VariableType.h \
    interfaces/quantor/Result.h \
    $$picosatDir/*.h \
    $$quantorDir/*.h \
    gui/QuantorResultDialog.h \
    MapModel.h \
    model/Port.h \
    gui/Schematic.h \
    gui/SchematicElement.h \
    metamodel/FunctionDescriptor.h \
    factories/DocumentEntryFactory.h \
    interfaces/quantor/Context.h \
    factories/GIFactory.h \
    gui/ComponentDetailView.h \
    PortListModel.h \
    gui/ModulePortGI.h \
    model/ModuleInterface.h \
    core/Identifiable.h \
    factories/ToolTipFactory.h

INCLUDEPATH +=\
    $$picosatDir \
    $$quantorDir

FORMS    +=\
    gui/MainWindow.ui \
    gui/SchematicsTab.ui \
    gui/QuantorResultDialog.ui \
    gui/ComponentDetailView.ui

# exclude quantorizer.ypp
HEADERS -= interfaces/quantor/Quantorizer.ypp
SOURCES -= interfaces/quantor/Quantorizer.ypp

# exclude picosat main
SOURCES -= $$picosatDir/main.c
# exclude quantor main
SOURCES -= $$quantorDir/main.c

RESOURCES += \
    icons.qrc
