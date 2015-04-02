#include "Document.h"

#include "factories/DocumentEntryFactory.h"
#include "gui/ComponentGraphicsItem.h"
#include "gui/Schematic.h"
#include "gui/SchematicElement.h"
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
using namespace q2d::core;
using namespace q2d::factories;
using namespace q2d::metamodel;


Document::Document(QString name, Project* parent) :
    QObject(parent),
    QStandardItem(name),
    Identifiable(name) {

    Q_CHECK_PTR(parent);
    Q_ASSERT(this->text() == name);

    // obtain the component factory
    ApplicationContext* context =
        dynamic_cast<ApplicationContext*>(parent->parent());
    Q_CHECK_PTR(context);
    this->m_componentFactory = context->componentFactory();

    this->setData(QVariant::fromValue(new model::Model(this)),
                  DocumentRole::MODEL);
    this->setData(QVariant::fromValue(new gui::Schematic(this)),
                  DocumentRole::SCHEMATIC);
}

/**
 * @brief Document::getSchematicView is a getter for convenience
 * @return
 */
gui::Schematic*
Document::schematic() {
    return this->data(DocumentRole::SCHEMATIC).value<gui::Schematic*>();
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
 * Also all component ports will be initialized accordingly.
 *
 * @param typeId is the full id path of the ComponentType
 * in the component hierarchy.
 * @param position of the component at which it is placed in the schematic.
 */
void
Document::addComponent(QString typeId, QPoint position) {

    metamodel::ComponentDescriptor* type = m_componentFactory->getTypeForHierarchyName(typeId);
    Q_CHECK_PTR(type);

    DocumentEntryFactory::instantiateComponent(this, type, position);
}


void
Document::addInputPort(QString id, QPointF pos) {
    DocumentEntryFactory::instantiateInputPort(this, pos, id);
}

void
Document::addOutputPort(QString id, QPointF pos) {
    DocumentEntryFactory::instantiateOutputPort(this, pos, id);
}

/**
 * @brief Document::entry searches for an document entry given by an id string.
 * @param id
 * @return The entry identified by id or a nullptr if there is no such entry.
 */
DocumentEntry*
Document::entryForFullId(const QString fullId) const {
    Q_ASSERT(!fullId.isEmpty());

    for (DocumentEntry * entry : m_entries) {
        if (entry->fullId() == fullId) {
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
    DocumentEntry* sender = this->entryForFullId(senderNodeId);
    DocumentEntry* receiver = this->entryForFullId(receiverNodeId);

    DocumentEntryFactory::instantiateWire(this, sender, receiver);
}

void
Document::addEntry(DocumentEntry* entry) {
    Q_CHECK_PTR(entry);
    qDebug() << "Added document entry" << entry->fullId();
    m_entries.append(entry);
}

void
Document::save(QDir saveDir) {
    Q_ASSERT(saveDir.exists());
    qDebug() << "Saving Document" << this->text();

    // create the JSON document
    // the name is implicitly in the file name
    QJsonDocument jsonDocument = QJsonDocument();
    jsonDocument.setObject(json::fromDocument(this));

    QString path = saveDir.absolutePath() + "/"
                   + this->text() + EXTENSION_DOCFILE;
    json::writeJsonFile(path, jsonDocument);
}
