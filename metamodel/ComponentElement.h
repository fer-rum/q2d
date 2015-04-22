#ifndef COMPONENTELEMENT_H
#define COMPONENTELEMENT_H

#include "Element.h"
#include "ComponentDescriptor.h"

#include <QObject>

namespace q2d {
namespace metamodel {

// forward declaration
class ComponentDescriptor;

class ComponentElement :
    public Element {
    Q_OBJECT
public:
    explicit ComponentElement(QString name, ComponentDescriptor* parent);

    virtual ComponentDescriptor* parent() const;
    virtual void setParent(ComponentDescriptor* parent);

    virtual int type() const override = 0;
};


} // namespace metamodel
} // namespace q2d

#endif // COMPONENTELEMENT_H
