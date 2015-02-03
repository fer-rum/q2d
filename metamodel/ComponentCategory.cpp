#include "ComponentCategory.h"

using namespace q2d::metamodel;

ComponentCategory::ComponentCategory(QString name, ComponentCategory* parent) :
    ComponentDescriptor(name, parent) {}

void
ComponentCategory::addSubItem (ComponentDescriptor* toAdd) {

    Q_CHECK_PTR(toAdd);

    if (toAdd->QObject::parent() != this) {
        toAdd->QObject::setParent(this);
    }
    this->appendRow (toAdd);
}
