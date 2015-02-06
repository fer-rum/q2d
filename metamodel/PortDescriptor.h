#ifndef PORTDESCRIPTOR_H
#define PORTDESCRIPTOR_H

#include "../Enumerations.h"
#include "ComponentElement.h"

#include <QStandardItem>
#include <QPoint>
#include <QObject>

namespace q2d {
namespace metamodel {

// forward declaration
class ComponentDescriptor;

class PortDescriptor :
    public ComponentElement {
public:
    explicit PortDescriptor(QString name,
                            model::enums::PortDirection direction,
                            QPointF position,
                            metamodel::ComponentDescriptor* parent);

    QPoint position();
    model::enums::PortDirection direction();

    virtual int type() const {
        return (int)ComponentDescriptorType::PORT_DESCRIPTOR;
    }
};

} // namespace metamodel
} // namespace q2d
#endif // PORTDESCRIPTOR_H
