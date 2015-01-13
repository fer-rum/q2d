#include "ComponentCategory.h"

using namespace q2d;

ComponentCategory::ComponentCategory(QString name, ComponentCategory* parent) :
    ComponentDescriptor(name, parent) {}

void
ComponentCategory::addSubItem (ComponentDescriptor *toAdd){

    Q_CHECK_PTR(toAdd);

    this->appendRow (toAdd);
}
