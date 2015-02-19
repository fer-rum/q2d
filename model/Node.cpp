
#include "../DocumentEntry.h"
#include "Node.h"
#include "Component.h"

using namespace q2d::model;

Node::Node(Model* parent, DocumentEntry* relatedEntry) : ModelElement(parent, relatedEntry) {
    this->driver = nullptr;
    this->drivenElements = QList<ModelElement*>();
}

Port::Port(enums::PortDirection direction, Component* topLevel, Model* parent,
           DocumentEntry* relatedEntry) : Node(parent, relatedEntry) {
    Q_CHECK_PTR(parent);

    m_direction = direction;

    if(topLevel != nullptr){
    if (m_direction == enums::PortDirection::IN) {
        this->addDrivenElement(topLevel);
    } else if (m_direction == enums::PortDirection::OUT) {
        this->addDriver(topLevel);
    }
    }
}


void
Node::addDriver(ModelElement* driver) {
    Q_CHECK_PTR(driver);
    Q_ASSERT(this->driver == nullptr);
    // no driver must be set yet
    // multiple drivers per node are not allowed for now.

    this->driver = driver;
}

void
Node::addDrivenElement(ModelElement* drivenElement) {
    Q_CHECK_PTR(drivenElement);
    this->drivenElements.append(drivenElement);
}

QStringList
Port::nodeVariables() const {
    return QStringList(this->relatedEntry()->id());
}
