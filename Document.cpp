#include "Document.h"

#include "gui/ComponentGraphicsItem.h"
#include "gui/SchematicsScene.h"
#include "gui/PortGraphicsItem.h"
#include "gui/WireGraphicsItem.h"
#include "metamodel/ComponentType.h"
#include "metamodel/PortDescriptor.h"
#include "model/Node.h"
#include "ApplicationContext.h"
#include "ComponentFactory.h"
#include "Constants.h"
#include "Project.h"

#include <QGraphicsEllipseItem>

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
 * @param parent the Project the document belongs to; Must not be null.
 */
Document::Document(QString name, Project* parent) :
    QObject(parent),
    QStandardItem(name) {

        Q_CHECK_PTR(parent);

    // obtain the component factory
    ApplicationContext* context = dynamic_cast<ApplicationContext*>(parent->parent());
    Q_CHECK_PTR(context);
    this->componentFactory = context->getComponentFactory();

    this->setData(QVariant::fromValue(new model::Model(this)), DocumentRole::MODEL);
    this->setData(QVariant::fromValue(new gui::SchematicsScene(this)), DocumentRole::SCHEMATIC);
}

/**
 * @brief Document::getSchematicView is a getter for convenience
 * @return
 */
gui::SchematicsScene*
Document::schematic(){
    return this->data(DocumentRole::SCHEMATIC).value<gui::SchematicsScene*>();
}

/**
 * @brief Document::getDescribedModel is a convenience function
 * @return
 */
model::Model*
Document::model(){
    return this->data(DocumentRole::MODEL).value<model::Model*>();
}

/**
 * @brief Document::addComponent instantiates a new component from a ComponentType,
 * given by its path in the component hierarchy.
 * The new component will be placed at the given position in the schematic.
 *
 * @param path is the path of the ComponentType in the component hierarchy.
 * @param position of the component at which it is placed in the schematic.
 */
void
Document::addComponent(QString path, QPoint position){

    // TODO modify
    // this function should let the component factory do all the work and only
    // collect a list of DocumentEntries

    // get needed information from the ComponentFactory
    ComponentType* type = this->componentFactory->getTypeForHierarchyName(path);
    Q_CHECK_PTR(type);

    QString id = type->generateId();

    // add component graphics to Schematic
    gui::ComponentGraphicsItem* schematicComponent = new gui::ComponentGraphicsItem(
                                            type, this->schematic(), position);
    this->schematic()->addItem(schematicComponent);

    // add the component to the model
    model::Component* modelComponent = new model::Component(type, this->model());
    this->model()->addComponent(modelComponent);

    // connect model and component element
    DocumentEntry* entry = new DocumentEntry(id, modelComponent, schematicComponent);
    m_entries.append(entry);
    schematicComponent->setToolTip(entry->id());

    // also add the ports
    this->addComponentPorts(type, id, modelComponent, schematicComponent);
}

void
Document::addComponentPorts(ComponentType* type,
                            QString componentId,
                            model::Component* modelComponent,
                            gui::ComponentGraphicsItem* schematicComponent){

    for(QObject* child : type->children()){

        PortDescriptor* descriptor = dynamic_cast<PortDescriptor*>(child);
        if(descriptor == nullptr){continue;}

        // build the unique id
        QString id = componentId + HIERARCHY_SEPERATOR + descriptor->text();

        // add port graphics to schematic
        gui::PortGraphicsItem* schematicPort = new gui::PortGraphicsItem(
                                                   descriptor->position(),
                                                   descriptor->direction(),
                                                   schematicComponent);
        // no need to add this to the scene, since the parent already is
        // in the scene and the child inherits this
        schematicPort->setToolTip(id);

        // add port to model
        model::Port* modelPort = new model::Port(
                                     descriptor->direction(),
                                     modelComponent,
                                     this->model());
        // create and add the document entry
        DocumentEntry* entry = new DocumentEntry(id, modelPort, schematicPort);
        m_entries.append(entry);
        // since the ports are linked to the component,
        // they are implicitly added to the model by adding the component
    }


}

DocumentEntry*
Document::entry(const QString id) const{
    Q_ASSERT(!id.isEmpty());

    for(DocumentEntry* entry : m_entries){
       if(entry->id() == id){
           return entry;
       }
    }
    return nullptr;
}

DocumentEntry*
Document::entry(const QGraphicsItem* schematicElement) const {
    for(DocumentEntry* entry : m_entries){
        if(entry->schematicElement() == schematicElement){
            return entry;
        }
    }
    return nullptr;
}

DocumentEntry*
Document::entry(const model::ModelElement* modelElement) const {
    for(DocumentEntry* entry : m_entries){
        if(entry->modelElement() == modelElement){
            return entry;
        }
    }
    return nullptr;
}

void
Document::addWire(QString senderNodeId, QString receiverNodeId){
    DocumentEntry* sender = this->entry(senderNodeId);
    DocumentEntry* receiver = this->entry(receiverNodeId);

    Q_CHECK_PTR(sender);
    Q_CHECK_PTR(receiver);

    QString id = "wire from " + senderNodeId + " to " + receiverNodeId;

    // create the wire graphics
    gui::WireGraphicsItem* schematicWire = new gui::WireGraphicsItem(
                                               sender->schematicElement()->pos(),
                                               receiver->schematicElement()->pos(),
                                               this->schematic());
    this->schematic()->addItem(schematicWire);

    // connect the nodes in the model
    model::Node* startNode = dynamic_cast<model::Node*>(sender->modelElement());
    model::Node* endNode = dynamic_cast<model::Node*>(receiver->modelElement());

    Q_CHECK_PTR(startNode);
    Q_CHECK_PTR(endNode);

    model::Conductor* modelWire = this->model()->connect(startNode, endNode);

    // add the document entry
    DocumentEntry* entry = new DocumentEntry(id, modelWire, schematicWire);
    m_entries.append(entry);
}
