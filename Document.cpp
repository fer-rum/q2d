#include "Document.h"

#include "gui/ComponentGraphicsItem.h"
#include "gui/SchematicsScene.h"
#include "gui/SchematicsSceneChild.h"
#include "gui/PortGraphicsItem.h"
#include "gui/WireGraphicsItem.h"
#include "metamodel/ComponentDescriptor.h"
#include "metamodel/PortDescriptor.h"
#include "model/Node.h"
#include "ApplicationContext.h"
#include "ComponentFactory.h"
#include "Constants.h"
#include "JsonHelpers.h"
#include "Project.h"

#include <QFile>
#include <QGraphicsEllipseItem>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::metamodel;

/**
 * @brief Document::Document
 *
 * Upon creation of a document an empty described model
 * and an empty schematic view are created.
 *
 * @param name is the name of the document and also the name of the component
 * which is described by the document.
 *
 * @param parent the Project the document belongs to; Must not be null,
 * since the component factory is cached from it
 */
Document::Document(QString name, Project* parent) :
    QObject(parent),
    QStandardItem(name) {
    Q_CHECK_PTR(parent);
    Q_ASSERT(this->text() == name);
    qDebug() << "Create document with name" << name;

    // obtain the component factory
    ApplicationContext* context =
        dynamic_cast<ApplicationContext*>(parent->parent());
    Q_CHECK_PTR(context);
    this->m_componentFactory = context->componentFactory();

    this->setData(QVariant::fromValue(new model::Model(this)),
                  DocumentRole::MODEL);
    this->setData(QVariant::fromValue(new gui::SchematicsScene(this)),
                  DocumentRole::SCHEMATIC);
}

/**
 * @brief Document::getSchematicView is a getter for convenience
 * @return
 */
gui::SchematicsScene*
Document::schematic() {
    return this->data(DocumentRole::SCHEMATIC).value<gui::SchematicsScene*>();
}

/**
 * @brief Document::getDescribedModel is a convenience function
 * @return
 */
model::Model*
Document::model() const {
    return this->data(DocumentRole::MODEL).value<model::Model*>();
}

ComponentFactory*
Document::componentFactory() const {
    return m_componentFactory;
}

/**
 * @brief Document::addComponent instantiates a new component from a ComponentType,
 * given by its path in the component hierarchy.
 * The new component will be placed at the given position in the schematic.
 *
 * @param typeId is the full id path of the ComponentType
 * in the component hierarchy.
 * @param position of the component at which it is placed in the schematic.
 */
void
Document::addComponent(QString typeId, QPoint position) {

    metamodel::ComponentDescriptor* type = m_componentFactory->getTypeForHierarchyName(typeId);
    Q_CHECK_PTR(type);

    DocumentEntry* entry =
        m_componentFactory->instantiateComponent(this, type, position);

    // also add the ports
    m_componentFactory->instantiatePorts(this, type, entry);
}


void
Document::addInputPort(QString id, QPointF pos) {
    m_componentFactory->instantiateInputPort(this, pos, id);
}

void
Document::addOutputPort(QString id, QPointF pos) {
    m_componentFactory->instantiateOutputPort(this, pos, id);
}

/**
 * @brief Document::entry searches for an document entry given by an id string.
 * @param id
 * @return The entry identified by id or a nullptr if there is no such entry.
 */
DocumentEntry*
Document::entry(const QString id) const {
    Q_ASSERT(!id.isEmpty());

    for (DocumentEntry * entry : m_entries) {
        if (entry->id() == id) {
            return entry;
        }
    }
    return nullptr;
}

DocumentEntry*
Document::entry(const gui::SchematicsSceneChild* schematicElement) const {
    Q_CHECK_PTR(schematicElement);

    for (DocumentEntry * entry : m_entries) {
        if (entry->schematicElement() == schematicElement) {
            return entry;
        }
    }
    return nullptr;
}

DocumentEntry*
Document::entry(const model::ModelElement* modelElement) const {
    Q_CHECK_PTR(modelElement);

    for (DocumentEntry * entry : m_entries) {
        if (entry->modelElement() == modelElement) {
            return entry;
        }
    }
    return nullptr;
}

QList<DocumentEntry*>
Document::entries() const {
    return m_entries;
}


void
Document::addWire(QString senderNodeId, QString receiverNodeId) {
    DocumentEntry* sender = this->entry(senderNodeId);
    DocumentEntry* receiver = this->entry(receiverNodeId);

    QString id = "wire:" + senderNodeId + "--" + receiverNodeId;

    m_componentFactory->instantiateWire(this, sender, receiver, id);
}

void
Document::addEntry(DocumentEntry* entry) {
    Q_CHECK_PTR(entry);
    m_entries.append(entry);
}

void
Document::save(QDir saveDir) {
    Q_ASSERT(saveDir.exists());
    qDebug() << "Saving Document" << this->text();

    // create the JSON document
    // the name is implicitly in the file name
    // TODO: should this be written in the JSON too?
    // TODO: should the component Factories state be saved?
    // maybe in project…
    QJsonDocument jsonDocument = QJsonDocument();
    jsonDocument.setObject(json::fromDocument(this));

    QString path = saveDir.absolutePath() + "/"
                   + this->text() + EXTENSION_DOCFILE;
    json::writeJsonFile(path, jsonDocument);
}
