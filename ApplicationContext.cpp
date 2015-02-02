#include "ApplicationContext.h"

#include "Application.h"
#include "ComponentFactory.h"
#include "Document.h"
#include "gui/MainWindow.h"
#include "Project.h"

#include <QFile>

using namespace q2d;
using namespace constants;
using MainWindow = q2d::gui::MainWindow;

ApplicationContext::ApplicationContext(Application *parent)
    : QObject(parent) {
    // TODO load basic libraries
    this->m_componentFactory = new ComponentFactory(this);

    // create the main window
    this->m_mainWindow = new gui::MainWindow(this);
    this->m_mainWindow->setupSignalsAndSlots();
    this->m_mainWindow->show();

    this->setupSignalsAndSlots();

    QStandardItemModel* componentHierarchy = this->m_componentFactory->getComponentHierarchy();
    Q_CHECK_PTR(componentHierarchy);
    emit this->signal_componentModelChanged(componentHierarchy);
}

ApplicationContext::~ApplicationContext(){
    // TODO save project
    // TODO uninitialize and close mainWindow
}

bool
ApplicationContext::hasCurrentProject(){
    return m_currentProject != nullptr;
}

Project*
ApplicationContext::getCurrentProject(){
    return this->m_currentProject;
}

gui::MainWindow*
ApplicationContext::getMainWindow(){
    return this->m_mainWindow;
}

ComponentFactory*
ApplicationContext::componentFactory() {
    return this->m_componentFactory;
}

//TODO: Convert to new Signal/Slot Syntax
void
ApplicationContext::setupSignalsAndSlots(){
    Q_CHECK_PTR(this->m_mainWindow);

    // ApplicationContext -> MainWindow
    connect(this, &ApplicationContext::signal_projectNameChanged,
            m_mainWindow, &MainWindow::slot_updateProjectName);
    connect(this, &ApplicationContext::signal_canSaveProjects,
            m_mainWindow, &MainWindow::slot_enableProjectSaving);
    connect(this, &ApplicationContext::signal_canAddDocuments,
            m_mainWindow, &MainWindow::slot_enableDocumentMenus);
    connect(this, &ApplicationContext::signal_documentModelChanged,
            m_mainWindow, &MainWindow::slot_setDocumentModel);
    connect(this, &ApplicationContext::signal_componentModelChanged,
            m_mainWindow, &MainWindow::slot_setComponentModel);
    connect(this, &ApplicationContext::signal_showDocument,
            m_mainWindow, static_cast<void (MainWindow::*)(Document*)>
            (&MainWindow::slot_openDocumentTab)); // ship around overloaded function
    // saving signal has to be set up by project

    // MainWindow -> ComponentFactory
    connect(m_mainWindow, &MainWindow::signal_createCategory,
            m_componentFactory, &ComponentFactory::slot_addCategory);
    connect(m_mainWindow, &MainWindow::signal_loadType,
            m_componentFactory, &ComponentFactory::slot_loadType);
    connect(m_mainWindow, &MainWindow::signal_clearComponentTypes,
            m_componentFactory, &ComponentFactory::slot_clearHierarchy);



}

/**
 * @brief ApplicationContext::createProject creates a new Project - instance
 * and makes it the current project.
 *
 * Callers have to make sure:
 * <ul>
 * <li>The projects name is valid</li>
 * <li>There is no current project</li>
 * </ul>
 *
 * @param name is the name of the new project
 */
void
ApplicationContext::createProject(QString name){

    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!this->hasCurrentProject());

    Project* newProject = new Project(name, this);
    Q_CHECK_PTR(newProject);

    m_currentProject = newProject;
    newProject->setupSignalsAndSlots();

    // inform other objects about changes
    emit this->signal_projectNameChanged(name);
    emit this->signal_canSaveProjects(true);
    // enable document menus
    emit this->signal_canAddDocuments(true);
    emit this->signal_documentModelChanged(newProject->getDocuments());
}

void
ApplicationContext::unloadProject(){

    // TODO save (if wanted) before unloading

    delete m_currentProject;
    m_currentProject = nullptr;
    emit this->signal_canAddDocuments(false);
    emit this->signal_projectNameChanged(QString());
    emit this->signal_documentModelChanged(nullptr);
}

/**
 * @brief ApplicationContext::slot_newDocument forwards the request of creating
 * a new document to the project.
 */
void
ApplicationContext::slot_newDocument(QString name){

    Q_CHECK_PTR(this->m_currentProject);

    emit this->signal_createDocument(name);
}

/**
 * @brief ApplicationContext::createProject is triggered upon the UIs request
 * to create a new project.
 * It is up to the UI to generate or request a name from the user.
 *
 * @param name
 * <ul>
 * <li> Must not be empty </li>
 * </ul>
 *
 */
void
ApplicationContext::slot_newProject(QString name){

    // TODO unload current project
    if(this->hasCurrentProject()){
        this->unloadProject();
    }

    // TODO unload unused component libraries

    // create new empty project
    this->createProject(name);

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

void
ApplicationContext::slot_loadProject(QDir projectDir){

    // check, if all necessary files exist
    QFile componentTreeFile(projectDir.absolutePath() + FILE_COMPONENT_TREE);
    Q_ASSERT(componentTreeFile.exists());
    // TODO in case of failure emit a signal
    // that makes the main window show a warning message

    // unload current Project, if needed
    if(m_currentProject != nullptr){
        this->unloadProject();
    }
    Q_ASSERT(m_currentProject == nullptr);
    // load component hierarchy
    // load documents
}

void
ApplicationContext::slot_unloadProject(){
    if(!this->hasCurrentProject()){
        return;
    }
    this->unloadProject();
}
