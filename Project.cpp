#include "Project.h"

#include "Application.h"
#include "ApplicationContext.h"
#include "Constants.h"
#include "JsonHelpers.h"
#include "gui/MainWindow.h"

#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;

Project::Project(QString name, ApplicationContext* parent)
    : QObject(parent) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(!name.isEmpty());

    m_applicationContext = parent;
    m_name = name;
}

void
Project::setupSignalsAndSlots() {
    // propagate changes of the project name if they happened without involvement of the
    // application context
    // TODO revisit nessecity
    connect(this, &Project::signal_nameChanged,
            m_applicationContext, &ApplicationContext::slot_projectNameChanged);
    connect(m_applicationContext, &ApplicationContext::signal_createDocument,
            this, &Project::slot_newDocument);
    connect(this, &Project::signal_showDocument,
            m_applicationContext, &ApplicationContext::signal_showDocument);
    connect(m_applicationContext, &ApplicationContext::signal_saveProject,
            this, &Project::slot_save);
}

QStandardItemModel*
Project::getDocuments() {
    return &m_documents;
}


void
Project::save(QDir projectDirectory) {
    Q_ASSERT(projectDirectory.exists());
    qDebug() << "Saving project";

    // Check if there already is a folder with the projec name present
    // If not create one.
    if (!projectDirectory.exists(m_name)) {
        bool ok = projectDirectory.mkdir(m_name);
        Q_ASSERT(ok);
    }
    // switch to that folder
    // NOTE why?
    bool ok = projectDirectory.cd(m_name);
    Q_ASSERT(ok);

    // TODO Save the project settings

    // make sure the component tree in use is saved
    QString hierarchyFilePath = projectDirectory.absolutePath() + FILE_COMPONENT_TREE;

    // TODO proper signal/slot usage
    m_applicationContext->componentFactory()->slot_saveHierarchy(hierarchyFilePath);

    // TODO make sure the component tree is rebuild before loading documents

    // For each Document:
    // Create a save file (folder?)
    for (int index = 0; index < m_documents.rowCount(); ++index) {
        Document* document = dynamic_cast<Document*>(m_documents.item(index));
        Q_CHECK_PTR(document);
        document->save(projectDirectory);
    }

}

Document*
Project::createDocument(QString name) {
    Document* newDocument = new Document(name, this);
    Q_CHECK_PTR(newDocument);
    m_documents.appendRow(newDocument);
    return newDocument;
}

/**
 * @brief Project::slot_newDocument
 *
 * This is seperated so the UI can be directed here as well as can loading functions.
 *
 * @param name
 *
 * Assumption: name is not empty
 */
void
Project::slot_newDocument(QString name) {
    Q_ASSERT(!name.isEmpty());

    Document* newDocument = this->createDocument(name);

    emit signal_showDocument(newDocument);
}

void
Project::slot_save() {
    QString savePath =
        Application::instance()->getSetting(KEY_DIR_PROJECTS).toString();
    QDir projectsDirectory = QDir(savePath);
    Q_ASSERT(projectsDirectory.exists());
    this->save(projectsDirectory);
}

/**
 * @brief Project::loadDocument
 * @param path the absolute path to the file
 */
void
Project::loadDocument(QString path) {

    QJsonDocument jsonDocument = json::readJsonFile(path);

    QString docName = path.split("/").last();
    docName.chop(EXTENSION_DOCFILE.length());

    Document* document = json::toDocument(jsonDocument.object(), docName, this);

    Q_CHECK_PTR(document);
    m_documents.appendRow(document);
}
