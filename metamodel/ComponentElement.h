#ifndef COMPONENTELEMENT_H
#define COMPONENTELEMENT_H

#include "Element.h"
#include "Type.h"

namespace q2d {
namespace metamodel {

// forward declaration
class Type;

class ComponentElement :
        public Element{
public:
    explicit ComponentElement(QString name, metamodel::Type* parent);

    virtual metamodel::Type* parent() const;
    virtual void setParent(metamodel::Type* parent);

    virtual int type() const override = 0;
};


} // namespace metamodel
} // namespace q2d

#endif // COMPONENTELEMENT_H
