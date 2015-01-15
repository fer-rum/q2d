#include "Node.h"

using namespace q2d::model;

int Node::DEFAULT_NAME_INDEX = 0;

Node::Node() : Node("node " + DEFAULT_NAME_INDEX) {}

Node::Node(QString name) : ModelElement(name){
    this->driver = nullptr;
    this->drivenElements = QList<ModelElement*>();
    ++DEFAULT_NAME_INDEX;
}

Port::Port(QString name, PortDirection direction) : Node(name) {
    this->direction = direction;
}


void
Node::addDriver(ModelElement* driver){
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
