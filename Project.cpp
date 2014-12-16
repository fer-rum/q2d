#include "Project.h"
#include "MainWindow.h"

#include <QMessageBox>

using namespace q2d;

Project::Project(QString name, ApplicationContext* parent) : QObject(parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    this->applicationContext = parent;
    this->name = name;

    // set the current document model as the model
    // for the document view in the main window.

    parent->getMainWindow()->setDocumentModel(&(this->documents));
}

void
Project::setupSignalsAndSlots(){
    // propagate changes of the project name if they happened without involvement of the
    // application context
    // TODO revisit nessecity
    connect(this, SIGNAL(signal_nameChanged(QString)), this->parent(), SLOT(slot_projectNameChanged(QString)));
    connect(this->applicationContext, SIGNAL(signal_createDocument()), this, SLOT(slot_newDocument()));
}

/**
 * @brief Project::createDocument
 *
 * This is seperated so the UI can use be directed here as well as loading functions.
 *
 * @param name
 *
 * Assumption: name is not empty
 */
void
Project::createDocument(QString name){

    Q_ASSERT(!name.isEmpty());

    Document* newDocument = new Document(name);
    Q_CHECK_PTR(newDocument);
    this->documents.appendRow(newDocument);

    // TODO select and show new document
}

void
Project::slot_newDocument(){

    gui::MainWindow* mainWindow = this->applicationContext->getMainWindow();

    // get name
    bool ok;
    QString name = QInputDialog::getText(mainWindow,
                                         tr("Document name required"),
                                         tr("Enter the name of the new document:"),
                                         QLineEdit::Normal, "", &ok);

    if(!ok){ // action canceled
        return;
    }

    // validate name
    if(name.isEmpty()){
        QMessageBox::critical(mainWindow,
                              tr("Error: Document name was empty"),
                              tr("The documents name must not be empty."),
                              QMessageBox::Ok);
        return;
    }

    this->createDocument(name);
}
