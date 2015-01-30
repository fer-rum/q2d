#include "ApplicationContext.h"

#include "Application.h"
#include "ComponentFactory.h"
#include "Document.h"
#include "gui/MainWindow.h"
#include "Project.h"

using namespace q2d;
using MainWindow = q2d::gui::MainWindow;

ApplicationContext::ApplicationContext(Application *parent)
    : QObject(parent) {
    // TODO load basic libraries
    this->m_componentFactory = new ComponentFactory(this);

    // create the main window
    this->mainWindow = new gui::MainWindow(this);
    this->mainWindow->setupSignalsAndSlots();
    this->mainWindow->show();

    this->setupSignalsAndSlots();

    QStandardItemModel* componentHierarchy = this->m_componentFactory->getComponentHierarchy();
    Q_CHECK_PTR(componentHierarchy);
    emit this->signal_componentModelChanged(componentHierarchy);
}

ApplicationContext::~ApplicationContext(){
    // TODO save project
    // TODO uninitialize and close mainWindow
    delete this->m_componentFactory;
}

Project*
ApplicationContext::getCurrentProject(){
    return this->currentProject;
}

gui::MainWindow*
ApplicationContext::getMainWindow(){
    return this->mainWindow;
}

ComponentFactory*
ApplicationContext::componentFactory() {
    return this->m_componentFactory;
}

//TODO: Convert to new Signal/Slot Syntax
void
ApplicationContext::setupSignalsAndSlots(){
    Q_CHECK_PTR(this->mainWindow);

    // ApplicationContext -> MainWindow
    connect(this, &ApplicationContext::signal_projectNameChanged,
            this->mainWindow, &MainWindow::slot_updateProjectName);
    connect(this, &ApplicationContext::signal_canSaveProjects,
            this->mainWindow, &MainWindow::slot_enableProjectSaving);
    connect(this, &ApplicationContext::signal_canAddDocuments,
            this->mainWindow, &MainWindow::slot_enableDocumentMenus);
    connect(this, &ApplicationContext::signal_documentModelChanged,
            this->mainWindow, &MainWindow::slot_setDocumentModel);
    connect(this, &ApplicationContext::signal_componentModelChanged,
            this->mainWindow, &MainWindow::slot_setComponentModel);
    connect(this, &ApplicationContext::signal_showDocument,
            this->mainWindow, static_cast<void (MainWindow::*)(Document*)>
            (&MainWindow::slot_openDocumentTab)); // ship around overloaded function
    // saving signal has to be set up by project

    // MainWindow -> ComponentFactory
    connect(this->mainWindow, &MainWindow::signal_createCategory,
            this->m_componentFactory, &ComponentFactory::slot_addCategory);
    connect(this->mainWindow, &MainWindow::signal_loadType,
            this->m_componentFactory, &ComponentFactory::slot_loadType);



}

/**
 * @brief ApplicationContext::slot_newDocument forwards the request of creating
 * a new document to the project.
 */
void
ApplicationContext::slot_newDocument(QString name){

    Q_CHECK_PTR(this->currentProject);

    emit this->signal_createDocument(name);
}

/**
 * @brief ApplicationContext::createProject
 * @param name
 *
 * Assumption: Name is not empty
 * Assumption: There is no current project
 */
void
ApplicationContext::slot_newProject(QString name){

    // TODO unload current project
    // TODO unload unused component libraries

    // create new empty project
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(this->currentProject == nullptr);

    Project* newProject = new Project(name, this);
    Q_CHECK_PTR(newProject);

    this->currentProject = newProject;
    newProject->setupSignalsAndSlots();

    // inform other objects about changes
    emit this->signal_projectNameChanged(name);
    emit this->signal_canSaveProjects(true);
    // enable document menus
    emit this->signal_canAddDocuments(true);
    emit this->signal_documentModelChanged(newProject->getDocuments());
}


// TODO is this still useful?
/**
 * @brief ApplicationContext::slot_projectNameChanged
 * Propagates forward a change in the current projects name.
 *
 * @param newName
 */
void
ApplicationContext::slot_projectNameChanged(QString newName){
    emit this->signal_projectNameChanged(newName);
}
