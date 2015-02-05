#include "ComponentElement.h"
#include "Type.h"

using namespace q2d::metamodel;

ComponentElement::ComponentElement(QString name, metamodel::Type* parent)
    : Element(name, parent){}

ComponentElement* ComponentElement::parent() const{
    return static_cast<ComponentElement*>(QObject::parent());
}

void
ComponentElement::setParent(ComponentElement* parent){
    QObject::setParent(parent);
}
