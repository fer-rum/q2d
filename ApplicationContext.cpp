#include "ApplicationContext.h"

#include <QInputDialog>
#include <QMessageBox>

using namespace q2d;

ApplicationContext::ApplicationContext(Application *parent) : QObject(parent){
    this->currentProject = nullptr;
    // TODO load basic libraries
    // create the main window
    this->mainWindow = new gui::MainWindow(this);
    this->mainWindow->setupSignalsAndSlots();
    this->mainWindow->show();

}

/**
 * @brief ApplicationContext::createProject
 * @param name
 *
 * Assumption: Name is not empty
 * Assumption: There is no current project
 */
void
ApplicationContext::createProject(QString name){
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(this->currentProject == nullptr);

    Project* newProject = new Project(name, this);
    Q_CHECK_PTR(newProject);

    this->currentProject = newProject;
    newProject->setupSignalsAndSlots();
    emit this->signal_projectNameChanged(name);
    // TODO enable document menus
}

gui::MainWindow*
ApplicationContext::getMainWindow(){
    return this->mainWindow;
}

void
ApplicationContext::setupSignalsAndSlots(){
    Q_CHECK_PTR(this->mainWindow);

    connect(this, SIGNAL(signal_projectNameChanged(QString)), this->mainWindow, SLOT(slot_updateProjectName(QString)));
}

void
ApplicationContext::slot_newProject(){
    // get the main window to use as parent
    Application* app = qobject_cast<Application*>(this->parent());
    Q_CHECK_PTR(app);

    // get name
    bool ok;
    QString name = QInputDialog::getText(this->mainWindow,
                        tr("Project name required"),
                        tr("Enter the name of the new Project:"),
                        QLineEdit::Normal, "", &ok);

    if(!ok){ // action canceled
        return;
    }

    // validate name
    if(name.isEmpty()){
        QMessageBox::critical(this->mainWindow,
            tr("Error: Project name was empty"),
            tr("The projects name must not be empty."),
            QMessageBox::Ok);
        return;
    }
    // TODO unload current project
    // TODO unload unused component libraries
    // create new empty project
    this->createProject(name);
}

/**
 * @brief ApplicationContext::slot_projectNameChanged
 * Propagates forward a change in the current projects name.
 * @param newName
 */
void
ApplicationContext::slot_projectNameChanged(QString newName){
    emit this->signal_projectNameChanged(newName);
}
