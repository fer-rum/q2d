#include "ComponentElement.h"
#include "Type.h"

using namespace q2d::metamodel;

ComponentElement::ComponentElement(QString name, metamodel::Type* parent)
    : Element(name, parent){
    // set UI interactions
    this->setSelectable(false);
    this->setDragEnabled(false);
}

Type* ComponentElement::parent() const{
    return static_cast<metamodel::Type*>(QObject::parent());
}

void
ComponentElement::setParent(metamodel::Type* parent){
    QObject::setParent(parent);
}
