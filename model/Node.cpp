#include "Node.h"

#include "Component.h"

using namespace q2d::model;

Node::Node(Model* parent) : ModelElement(parent) {
    this->driver = nullptr;
    this->drivenElements = QList<ModelElement*>();
}

Port::Port(PortDirection direction, Component* topLevel, Model* parent) : Node(parent) {
    Q_CHECK_PTR(topLevel);
    Q_CHECK_PTR(parent);

    this->direction = direction;

    if (direction == IN) {
        this->addDrivenElement(topLevel);
    } else if (direction == OUT) {
        this->addDriver(topLevel);
    }

    // TODO how to handle INOUT?
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
