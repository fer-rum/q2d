
#include "../Constants.h"
#include "../Document.h"
#include "../DocumentEntry.h"
#include "../gui/ModulePortGI.h"
#include "../gui/PortGraphicsItem.h"
#include "../gui/ComponentGraphicsItem.h"
#include "../gui/WireGraphicsItem.h"
#include "../metamodel/ComponentDescriptor.h"
#include "../metamodel/PortDescriptor.h"
#include "../model/Component.h"
#include "../model/Conductor.h"
#include "../model/ModelElement.h"
#include "../model/ModuleInterface.h"
#include "../model/Port.h"

#include "DocumentEntryFactory.h"

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::factories;
using namespace q2d::metamodel;

QMap<QString, unsigned>
DocumentEntryFactory::instanceCount = QMap<QString, unsigned>();

unsigned int
DocumentEntryFactory::countInstance(QString typeName){
    unsigned int count = instanceCount.value(typeName, 0);
    instanceCount.insert(typeName, ++count);
    return count;
}

QString
DocumentEntryFactory::generateComponentId(
        metamodel::ComponentDescriptor* type){
    Q_CHECK_PTR(type);

    QString typeName = type->text();

    return typeName + QString::number(DocumentEntryFactory::countInstance(typeName));
}

DocumentEntry*
DocumentEntryFactory::instantiateComponent(Document* document,
        metamodel::ComponentDescriptor* type,
        QPointF scenePosition,
        QString id, bool autoInstancePorts) {

    Q_CHECK_PTR(document);
    Q_CHECK_PTR(type);

    if(id.isEmpty()){
        id = DocumentEntryFactory::generateComponentId(type);
    } else {
        // TODO validity check
        // if the id is given and valid, we increase the counter for that type to avoid name clashes
        countInstance(type->text());
    }

    DocumentEntry* entry = new DocumentEntry(id, enums::DocumentEntryType::COMPONENT, document);
    Q_CHECK_PTR(entry);

    gui::ComponentGraphicsItem* schematicComponent =
            new gui::ComponentGraphicsItem(scenePosition, entry, type);
    Q_CHECK_PTR(schematicComponent);
    document->schematic()->addItem(schematicComponent);

    // add the component to the model
    model::Component* modelComponent = new model::Component(type, entry);
    Q_CHECK_PTR(modelComponent);
    document->model()->addComponent(modelComponent);

    // connect model and gui element
    entry->setModelElement(modelComponent);
    entry->setSchematicElement(schematicComponent);

    // finishing touch
    schematicComponent->setToolTip(entry->id());
    document->addEntry(entry);

    if(autoInstancePorts){
        DocumentEntryFactory::instantiatePorts(document, type, entry);
    }

    return entry;
}

QList<DocumentEntry*>
DocumentEntryFactory::instantiatePorts(
        Document* document,
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

        DocumentEntry* entry = DocumentEntryFactory::instantiatePort(document, parentComponent,
                               descriptor->position(),
                               descriptor->direction(), id);
        result.append(entry);
    }

    return result;
}

// TODO this function needs code cleaning
DocumentEntry*
DocumentEntryFactory::instantiatePort(
        Document* document,
        DocumentEntry* parentDocumentEntry,
        QPointF position,
        model::enums::PortDirection direction,
        QString id) {

    DocumentEntry* entry;
    model::Port* modelPort;


    model::ModelElement* parentME = parentDocumentEntry->modelElement();

    // check, what kind of paren we add a port to and act accordingly
    switch(parentDocumentEntry->type()){
    case enums::DocumentEntryType::COMPONENT : {
        entry = new DocumentEntry(id, enums::DocumentEntryType::COMPONENT_PORT,
                                  document, parentDocumentEntry);
        modelPort  = new model::ComponentPort(direction, entry,
                                              dynamic_cast<model::Component*>(parentME));
    } break;
    case enums::DocumentEntryType::MODULE_INTERFACE : {
        entry = new DocumentEntry(id, enums::DocumentEntryType::OUTSIDE_PORT,
                                  document, parentDocumentEntry);
        modelPort  = new model::ModulePort(direction, entry,
                      dynamic_cast<model::ModuleInterface*>(parentME));
    } break;
    default:
        Q_ASSERT(false); // should not happen
    }
    Q_CHECK_PTR(entry);

    gui::ParentSchematicElement* schematicComponent =
            qobject_cast<gui::ParentSchematicElement*>(parentDocumentEntry->schematicElement());
    Q_CHECK_PTR(schematicComponent);

    // create port graphics
    gui::PortGraphicsItem* schematicPort = new gui::PortGraphicsItem(position, entry, direction);
    Q_CHECK_PTR(schematicPort);

    // connect signals and slots
    // inform the port if it has moved due to the parent moving
    QObject::connect(schematicComponent, &gui::ParentSchematicElement::signal_posChanged,
            schematicPort, &gui::PortGraphicsItem::signal_posChanged);

    // no need to add this to the scene, since the parent already is
    // in the scene and the child inherits this
    schematicPort->setToolTip(id);

    // add port to model
    // check, what should be added

    entry->setModelElement(modelPort);
    entry->setSchematicElement(schematicPort);

    // create and add the document entry

    document->addEntry(entry);

    return entry;
}

DocumentEntry*
DocumentEntryFactory::instantiateModuleInterface(
        Document* document,
        QPointF position,
        model::enums::PortDirection direction,
        QString id){

    DocumentEntry* entry = new DocumentEntry(id, enums::DocumentEntryType::MODULE_INTERFACE, document);
    Q_CHECK_PTR(entry);

    gui::ModulePortGI* schematicPort =
        new gui::ModulePortGI(position, entry, direction);
    document->schematic()->addItem(schematicPort);

    model::ModuleInterface* moduleInterface = new model::ModuleInterface(entry, direction);

    entry->setModelElement(moduleInterface);
    entry->setSchematicElement(schematicPort);

    // instantiate the actual
    instantiatePort(document, entry, QPointF(0,0), model::enums::invert(direction), id);

    document->addEntry(entry);
    return entry;
}

DocumentEntry*
DocumentEntryFactory::instantiateInputPort(
        Document* document,
        QPointF position,
        QString id) {

    DocumentEntry* entry = instantiateModuleInterface(document, position, model::enums::PortDirection::IN, id);
    document->model()->addInputPort(static_cast<model::ModuleInterface*>(entry->modelElement()));
    return entry;
}

DocumentEntry*
DocumentEntryFactory::instantiateOutputPort(
        Document* document,
        QPointF position,
        QString id) {

    DocumentEntry* entry = instantiateModuleInterface(document, position, model::enums::PortDirection::OUT, id);
    document->model()->addOutputPort(static_cast<model::ModuleInterface*>(entry->modelElement()));
    return entry;
}

DocumentEntry*
DocumentEntryFactory::instantiateWire(
        Document* document,
        DocumentEntry* sender,
        DocumentEntry* receiver,
        QString id) {
    Q_CHECK_PTR(sender);
    Q_CHECK_PTR(receiver);
    Q_ASSERT(!id.isEmpty());

    DocumentEntry* entry = new DocumentEntry(id, enums::DocumentEntryType::WIRE, document);

    // create the wire graphics
    gui::PortGraphicsItem* senderItem =
        dynamic_cast<gui::PortGraphicsItem*>(sender->schematicElement());
    Q_CHECK_PTR(senderItem);

    gui::PortGraphicsItem* receiverItem =
        dynamic_cast<gui::PortGraphicsItem*>(receiver->schematicElement());
    Q_CHECK_PTR(receiverItem);

    gui::WireGraphicsItem* schematicWire =
        new gui::WireGraphicsItem(senderItem, receiverItem, entry);
    Q_CHECK_PTR(schematicWire);

    document->schematic()->addItem(schematicWire);

    // connect the nodes in the model
    model::Node* startNode = dynamic_cast<model::Node*>(sender->modelElement());
    Q_CHECK_PTR(startNode);
    model::Node* endNode = dynamic_cast<model::Node*>(receiver->modelElement());
    Q_CHECK_PTR(endNode);

    model::Conductor* modelWire = new model::Conductor(startNode, endNode, entry);
    Q_CHECK_PTR(modelWire);
    document->model()->addConductor(modelWire);

    entry->setModelElement(modelWire);
    entry->setSchematicElement(schematicWire);

    document->addEntry(entry);

    return entry;
}
