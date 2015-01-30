#ifndef PORTDESCRIPTOR_H
#define PORTDESCRIPTOR_H

#include "Enumerations.h"
#include "model/PortDirection.h"

#include <QStandardItem>
#include <QPoint>
#include <QObject>

namespace q2d {
namespace metamodel {

    // forward declaration
    class ComponentType;

class PortDescriptor :
        public QObject,
        public QStandardItem {
    Q_OBJECT
public:
    explicit PortDescriptor(QString name,
                            model::PortDirection direction,
                            QPoint position,
                            ComponentType* parent);

    QPoint position();
    model::PortDirection direction();

    virtual int type() const
    { return ComponentDescriptorType::PORT_DESCRIPTOR; }
};

} // namespace metamodel
} // namespace q2d
#endif // PORTDESCRIPTOR_H
