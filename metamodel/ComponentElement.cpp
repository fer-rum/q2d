#include "ComponentElement.h"
#include "ComponentDescriptor.h"

using namespace q2d::metamodel;

ComponentElement::ComponentElement(QString name, metamodel::ComponentDescriptor* parent)
    : Element(name, parent) {
    // set UI interactions
    this->setSelectable(false);
    this->setDragEnabled(false);
}

ComponentDescriptor* ComponentElement::parent() const {
    return static_cast<metamodel::ComponentDescriptor*>(QObject::parent());
}

void
ComponentElement::setParent(metamodel::ComponentDescriptor* parent) {
    QObject::setParent(parent);
}
