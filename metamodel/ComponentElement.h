#ifndef COMPONENTELEMENT_H
#define COMPONENTELEMENT_H

#include "Element.h"
#include "ComponentDescriptor.h"

namespace q2d {
namespace metamodel {

// forward declaration
class ComponentDescriptor;

class ComponentElement :
    public Element {
public:
    explicit ComponentElement(QString name, metamodel::ComponentDescriptor* parent);

    virtual metamodel::ComponentDescriptor* parent() const;
    virtual void setParent(metamodel::ComponentDescriptor* parent);

    virtual int type() const override = 0;
};


} // namespace metamodel
} // namespace q2d

#endif // COMPONENTELEMENT_H
