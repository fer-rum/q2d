#include "Category.h"

using namespace q2d::metamodel;

Category::Category(QString name, Category* parent) :
    HierarchyElement(name, parent) {
    // set UI interactions
    this->setDragEnabled(false);
}

void
Category::addSubItem (HierarchyElement* toAdd) {
    Q_CHECK_PTR(toAdd);

    if (toAdd->QObject::parent() != this) {
        toAdd->QObject::setParent(this);
    }
    this->appendRow(toAdd);
}

int
Category::type() const {
    return enums::elementTypeToInt(enums::ElementType::CATEGORY);
}
