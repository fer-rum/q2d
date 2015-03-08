
#include "../DocumentEntry.h"
#include "Node.h"
#include "Component.h"

using namespace q2d::model;

Node::Node(DocumentEntry* relatedEntry) : ModelElement(relatedEntry) {
    this->driver = nullptr;
    this->drivenElements = QList<ModelElement*>();
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
