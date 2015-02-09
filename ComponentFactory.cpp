#include "ComponentFactory.h"

#include "ApplicationContext.h"
#include "Constants.h"
#include "Document.h"
#include "Enumerations.h"
#include "JsonHelpers.h"
#include "Util.h"

#include "gui/ComponentGraphicsItem.h"
#include "gui/SchematicsScene.h"
#include "gui/PortGraphicsItem.h"
#include "gui/WireGraphicsItem.h"

#include "metamodel/Category.h"
#include "metamodel/ConfigurationBitDescriptor.h"
#include "metamodel/ComponentDescriptor.h"
#include "metamodel/PortDescriptor.h"

#include "model/Component.h"
#include "model/Model.h"

#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::metamodel;

ComponentFactory::ComponentFactory(ApplicationContext* parent)
    : QObject(parent) {}

/**
 * @brief ComponentFactory::addCategory creates a new category and adds it to
 * the component hierarchy.
 * If the parent category is null, the item will be sorted directly below the
 * root.
 *
 * @param name
 * @param parent the parent category; May be null
 */
Category*
ComponentFactory::slot_addCategory(QString name, Category* parent) {
    // TODO ensure update signals are fired upon adding a category
    Q_ASSERT(!name.isEmpty ());
    qDebug() << "Adding category" << name << "with parent" << parent;


    Category* newCategory = new Category(name, parent);

    if (parent == nullptr) {
        this->componentHierarchy.invisibleRootItem()->appendRow(newCategory);
    } else {
        parent->addSubItem(newCategory);
    }
    return newCategory;
}

/**
 * @brief ComponentFactory::slot_loadType creates a new component type
 * and adds it to the component hierarchy.
 * If the parent category is null, the item will be sorted directly below the
 * root.
 *
 * @param filePath is the absolute path of the file that contains the component description as JSON
 * @param parent the parent category; May be null
 */
void
ComponentFactory::slot_loadType(QString filePath, Category* parent) {

    const QString logPrefix = "Project::slot_loadType(" + filePath + ", " + util::ptrToString(parent) + ")";

    QJsonDocument jsonDocument = json::readJsonFile(filePath);

    // validity check
    if (jsonDocument.isNull()) {
        qWarning() << logPrefix << "json document seems to be invalid";
        return;
    }

    ComponentDescriptor* newType = json::toComponentDescriptor(jsonDocument, filePath, parent);
    Q_CHECK_PTR(newType);

    // TODO later disallow items w/o category
    if (parent != nullptr) {
        parent->addSubItem(newType);
    } else {
        this->componentHierarchy.invisibleRootItem()->appendRow(newType);
    }
}

/**
 * @brief ComponentFactory::getCategoryForIndex attempts to get the ComponentCategory
 * for the given index.
 *
 * If the index is invalid or the indexed element is not a ComponentCategory, a nullptr will be returned.
 *
 * @param index
 * @return ; May return null
 */
Category*
ComponentFactory::getCategoryForIndex(const QModelIndex &index) {
    if (!index.isValid()) {
        return nullptr;
    }

    QStandardItem* item = this->componentHierarchy.itemFromIndex(index);
    return dynamic_cast<Category*>(item);
}

/**
 * @brief ComponentFactory::getTypeForIndex attempts to get the ComponentType
 * for the given index.
 *
 * If the index is invalid or the indexed element is not a ComponentType, a nullptr will be returned.
 *
 * @param index
 * @return ; May return null
 */
ComponentDescriptor*
ComponentFactory::getTypeForIndex(const QModelIndex &index) {

    if (!index.isValid()) {
        return nullptr;
    }

    QStandardItem* item = this->componentHierarchy.itemFromIndex(index);
    return static_cast<ComponentDescriptor*>(item);
}

ComponentDescriptor*
ComponentFactory::getTypeForHierarchyName(QString hierarchyName) {
    QStringList hierarchy = hierarchyName.split(HIERARCHY_SEPERATOR,
                            QString::SkipEmptyParts);
    // traverse the hierarchy and find the component
    // TODO use a more effective approach here, this is really a hack

    QStandardItem* currentItem = this->componentHierarchy.invisibleRootItem();

    while (!hierarchy.isEmpty()) {
        // iterate over the current hierarcy level
        for (int index = 0; index < currentItem->rowCount(); ++index) {
            QStandardItem* child = currentItem->child(index);
            if (child->text() == hierarchy.first()) {
                currentItem = child;
                hierarchy.removeFirst(); // down to the next level
                break;
            }
            if (index == currentItem->rowCount() - 1) {
                // found nothing in the last element searched
                qDebug() << hierarchyName << "not found in component hierarchy!";
                return nullptr;
            }
        }
    }

    return dynamic_cast<ComponentDescriptor*>(currentItem);
}

QStandardItemModel*
ComponentFactory::getComponentHierarchy() {
    return &(this->componentHierarchy);
}

DocumentEntry*
ComponentFactory::instantiateComponent(Document* document, QString hierarchyName,
                                       QPointF scenePosition,
                                       QString id) {
    Q_CHECK_PTR(document);

    ComponentDescriptor* type = this->getTypeForHierarchyName(hierarchyName);
    Q_CHECK_PTR(type);

    return this->instantiateComponent(document, type, scenePosition, id);
}

/**
 * @brief ComponentFactory::instantiateComponent
 * The instantiated Component will be wrapped into a DocumentEntry
 * and added to the document.
 * @param document
 * @param type
 * @param scenePosition
 * @param id
 * @return
 */
DocumentEntry*
ComponentFactory::instantiateComponent(Document* document,
                                       metamodel::ComponentDescriptor* type,
                                       QPointF scenePosition, QString id) {
    qDebug() << "Instantiating component" << id << "in" << document << "at" << scenePosition;

    // add component graphics to Schematic
    gui::SchematicsScene* scene = document->schematic();
    Q_CHECK_PTR(scene);

    if (id.isEmpty()) {
        id = type->generateId();
    } else {
        // TODO check if the given ID clashes with the generic type-based naming
        // if this is the case, set the index accordingly
    }

    gui::ComponentGraphicsItem* schematicComponent =
        new gui::ComponentGraphicsItem(type, scene, scenePosition);
    Q_CHECK_PTR(schematicComponent);

    scene->addItem(schematicComponent);

    // add the component to the model

    model::Model* model = document->model();
    Q_CHECK_PTR(model);

    model::Component* modelComponent = new model::Component(type, model);
    model->addComponent(modelComponent);

    // connect model and component element
    DocumentEntry* entry =
        new DocumentEntry(id, DocumentEntryType::COMPONENT,
                          modelComponent, schematicComponent);
    Q_CHECK_PTR(entry);
    schematicComponent->setToolTip(entry->id());
    document->addEntry(entry);

    return entry;
}

/**
 * @brief ComponentFactory::instantiatePorts
 * Freshly instantiates all ports of a given Component.
 * The newly instantiated Ports will be added to the document.
 *
 * @param parentComponent
 * @return
 */
QList<DocumentEntry*>
ComponentFactory::instantiatePorts(Document* document,
                                   ComponentDescriptor* type,
                                   DocumentEntry* parentComponent) {
    Q_CHECK_PTR(parentComponent);
    Q_CHECK_PTR(type);

    QList<DocumentEntry*> result = QList<DocumentEntry*>();

    for (QObject * child : type->children()) {

        metamodel::PortDescriptor* descriptor =
            dynamic_cast<metamodel::PortDescriptor*>(child);
        if (descriptor == nullptr) {
            continue;
        }
        Q_ASSERT(!descriptor->position().isNull());

        QString id = parentComponent->id()
                     + HIERARCHY_SEPERATOR + descriptor->text();

        DocumentEntry* entry = this->instantiatePort(document, parentComponent,
                               descriptor->position(),
                               descriptor->direction(), id);
        result.append(entry);
    }

    return result;
}

/**
 * @brief ComponentFactory::instentiatePort
 * Instantiates a single Port and adds it to the document as DocumentEntry.
 * @param parentComponent
 * @param position
 * @param direction
 * @param id
 * @return
 */
DocumentEntry*
ComponentFactory::instantiatePort(Document* document,
                                  DocumentEntry* parentComponent,
                                  QPointF position,
                                  model::enums::PortDirection direction,
                                  QString id) {

    gui::ComponentGraphicsItem* schematicComponent =
        dynamic_cast<gui::ComponentGraphicsItem*>
        (parentComponent->schematicElement());
    Q_CHECK_PTR(schematicComponent);

    qDebug() << "Instantiating port" << id << "at" << position
             << "with direction" << model::enums::PortDirectionToString(direction);

    // add port graphics to schematic
    gui::PortGraphicsItem* schematicPort = new gui::PortGraphicsItem(
        position,
        direction,
        schematicComponent);
    // no need to add this to the scene, since the parent already is
    // in the scene and the child inherits this
    schematicPort->setToolTip(id);

    model::Component* modelComponent =
        dynamic_cast<model::Component*>(parentComponent->modelElement());
    Q_CHECK_PTR(modelComponent);

    // add port to model
    model::Port* modelPort = new model::Port(
        direction,
        modelComponent,
        document->model());

    // create and add the document entry
    DocumentEntry* entry = new DocumentEntry(id, DocumentEntryType::PORT,
            modelPort, schematicPort,
            parentComponent);
    Q_CHECK_PTR(entry);
    document->addEntry(entry);

    return entry;
}
DocumentEntry*
ComponentFactory::instantiateWire(Document* document, DocumentEntry* sender,
                                  DocumentEntry* receiver, QString id) {
    Q_CHECK_PTR(sender);
    Q_CHECK_PTR(receiver);
    Q_ASSERT(!id.isEmpty());

    // create the wire graphics
    gui::PortGraphicsItem* senderItem =
        dynamic_cast<gui::PortGraphicsItem*>(sender->schematicElement());
    Q_CHECK_PTR(senderItem);

    gui::PortGraphicsItem* receiverItem =
        dynamic_cast<gui::PortGraphicsItem*>(receiver->schematicElement());
    Q_CHECK_PTR(receiverItem);

    gui::WireGraphicsItem* schematicWire =
        new gui::WireGraphicsItem(
        senderItem,
        receiverItem);
    Q_CHECK_PTR(schematicWire);

    document->schematic()->addItem(schematicWire);

    // connect the nodes in the model
    model::Node* startNode = dynamic_cast<model::Node*>(sender->modelElement());
    Q_CHECK_PTR(startNode);
    model::Node* endNode = dynamic_cast<model::Node*>(receiver->modelElement());
    Q_CHECK_PTR(endNode);

    model::Conductor* modelWire = document->model()->connect(startNode, endNode);
    Q_CHECK_PTR(modelWire);

    // add the document entry
    DocumentEntry* entry = new DocumentEntry(id, DocumentEntryType::WIRE,
            modelWire, schematicWire);
    document->addEntry(entry);

    return entry;
}

QJsonDocument
ComponentFactory::exportHierarchy() {
    QJsonDocument result = QJsonDocument();
    QJsonArray hierarchy = QJsonArray();

    QStandardItem* rootItem = componentHierarchy.invisibleRootItem();

    for (int rIndex = 0; rIndex < rootItem->rowCount(); ++rIndex) {
        for (int cIndex = 0; cIndex < rootItem->columnCount(); ++cIndex) {
            hierarchy.append(QJsonValue(
                                 this->entryToJson(rootItem->child(rIndex, cIndex))
                             ));
        }
    }

    result.setArray(hierarchy);
    return result;
}


void
ComponentFactory::importHierarchy(QJsonDocument source) {
    Q_ASSERT(!source.isNull());
    Q_ASSERT(source.isArray());

    QJsonArray hierarchy = source.array();

    for (int index = 0; index < hierarchy.count(); ++index) {
        jsonToEntry(hierarchy[index].toObject(), nullptr);
    }
}

void
ComponentFactory::jsonToCategoryEntry(QJsonObject json, Category* parent) {

    QString name = json.value(JSON_HIERARCHY_CATEGORY_NAME).toString();
    Category* result = this->slot_addCategory(name, parent);

    QJsonArray children = json.value(JSON_HIERARCHY_CHILD).toArray();

    for (int index = 0; index < children.count(); ++index) {
        jsonToEntry(children[index].toObject(), result);
    }


}

void
ComponentFactory::jsonToTypeEntry(QJsonObject json, Category* parent) {
    QString sourcePath = json.value(JSON_HIERARCHY_SOURCE).toString();
    Q_ASSERT(!sourcePath.isEmpty());

    this->slot_loadType(sourcePath, parent);
}

void
ComponentFactory::jsonToEntry(QJsonObject json, Category* parent) {
    QString type = json.value(JSON_HIERARCHY_TYPE).toString();
    if (type == JSON_HIERARCHY_TYPE_COMPONENT) {
        jsonToTypeEntry(json, parent);
    } else if (type == JSON_HIERARCHY_TYPE_CATEGORY) {
        jsonToCategoryEntry(json, parent);
    } else {
        Q_ASSERT(false);
    }
}


QJsonObject
ComponentFactory::categoryEntryToJson(QStandardItem* item) {
    Category* category = dynamic_cast<Category*>(item);
    Q_CHECK_PTR(category);

    QJsonObject result = QJsonObject();
    QJsonArray children = QJsonArray();
    result.insert(JSON_HIERARCHY_CATEGORY_NAME, QJsonValue(category->text()));
    // child recursion
    for (int rIndex = 0; rIndex < item->rowCount(); ++rIndex) {
        for (int cIndex = 0; cIndex < item->columnCount(); ++cIndex) {
            children.append(QJsonValue(
                                this->entryToJson(item->child(rIndex, cIndex))
                            ));
        }
    }
    result.insert(JSON_HIERARCHY_CHILD, children);
    return result;
}

/**
 * @brief ComponentFactory::typeEntryToJson converts a QStandardItem describing a ComponentType
 * into a QJsonObject
 * @param item
 * @return
 */
QJsonObject
ComponentFactory::typeEntryToJson(QStandardItem* item) {
    QJsonObject result = QJsonObject();
    ComponentDescriptor* componentType = dynamic_cast<ComponentDescriptor*>(item);
    Q_CHECK_PTR(componentType);

    result.insert(JSON_HIERARCHY_SOURCE,
                  QJsonValue(componentType->descriptorPath()));
    return result;
}

QJsonObject
ComponentFactory::entryToJson(QStandardItem* item) {

    QJsonObject result;

    switch (item->type()) {
    case COMPONENT_TYPE:
        result = typeEntryToJson(item);
        result.insert(JSON_HIERARCHY_TYPE, QJsonValue(JSON_HIERARCHY_TYPE_COMPONENT));
        break;
    case COMPONENT_CATEGORY:
        result = categoryEntryToJson(item);
        result.insert(JSON_HIERARCHY_TYPE, QJsonValue(JSON_HIERARCHY_TYPE_CATEGORY));
        break;
    case PORT_DESCRIPTOR:
        // nothing to save, since they are bound to the component
        // this should not happen anyways
        Q_ASSERT(false);
    default:; // nothing useful to do, we should not end up here
        Q_ASSERT(false);
        result = QJsonObject();
    }

    return result;
}

void
ComponentFactory::slot_clearHierarchy() {
    componentHierarchy.clear();
}
