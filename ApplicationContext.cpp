#include "ApplicationContext.h"

#include <QInputDialog>
#include <QMessageBox>

using namespace q2d;

ApplicationContext::ApplicationContext(Application *parent)
    : QObject(parent) {
    this->currentProject = nullptr;
    // TODO load basic libraries
    // create the main window
    this->mainWindow = new gui::MainWindow(this);
    this->mainWindow->setupSignalsAndSlots();
    this->mainWindow->show();

    this->setupSignalsAndSlots();

    QStandardItemModel* componentHierarchy = this->componentFactory.getComponentHierarchy();

    Q_CHECK_PTR(componentHierarchy);

    emit this->signal_componentModelChanged(componentHierarchy);

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
ApplicationContext::getComponentFactory() {
    return &(this->componentFactory);
}

void
ApplicationContext::setupSignalsAndSlots(){
    Q_CHECK_PTR(this->mainWindow);

    connect(this, SIGNAL(signal_projectNameChanged(QString)),
            this->mainWindow, SLOT(slot_updateProjectName(QString)));
    connect(this, SIGNAL(signal_canAddDocuments(bool)),
            this->mainWindow, SLOT(slot_enableDocumentMenus(bool)));
    connect(this, SIGNAL(signal_documentModelChanged(QStandardItemModel*)),
            this->mainWindow, SLOT(slot_setDocumentModel(QStandardItemModel*)));
    connect(this, SIGNAL(signal_componentModelChanged(QStandardItemModel*)),
            this->mainWindow, SLOT(slot_setComponentModel(QStandardItemModel*)));

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
    emit this->signal_projectNameChanged(name);
    // enable document menus
    emit this->signal_canAddDocuments(true);
    emit this->signal_documentModelChanged(newProject->getDocuments());
}

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
