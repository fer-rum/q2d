#include "Project.h"
#include "MainWindow.h"

#include <QMessageBox>

using namespace q2d;

Project::Project(QString name, ApplicationContext* parent) : QObject(parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    this->applicationContext = parent;
    this->name = name;
}

void
Project::setupSignalsAndSlots(){
    // propagate changes of the project name if they happened without involvement of the
    // application context
    // TODO revisit nessecity
    connect(this, SIGNAL(signal_nameChanged(QString)), this->parent(), SLOT(slot_projectNameChanged(QString)));
    connect(this->applicationContext, SIGNAL(signal_createDocument(QString)), this, SLOT(slot_newDocument(QString)));
}

QStandardItemModel*
Project::getDocuments(){
    return &(this->documents);
}

/**
 * @brief Project::slot_newDocument
 *
 * This is seperated so the UI can use be directed here as well as loading functions.
 *
 * @param name
 *
 * Assumption: name is not empty
 */
void
Project::slot_newDocument(QString name){

    Q_ASSERT(!name.isEmpty());

    Document* newDocument = new Document(name);
    Q_CHECK_PTR(newDocument);
    this->documents.appendRow(newDocument);

    // TODO select and show new document
}
