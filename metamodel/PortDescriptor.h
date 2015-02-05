#ifndef PORTDESCRIPTOR_H
#define PORTDESCRIPTOR_H

#include "Enumerations.h"

#include <QStandardItem>
#include <QPoint>
#include <QObject>

namespace q2d {
namespace metamodel {

// forward declaration
class Type;

class PortDescriptor :
    public QObject,
    public QStandardItem {
    Q_OBJECT
public:
    explicit PortDescriptor(QString name,
                            model::enums::PortDirection direction,
                            QPointF position,
                            metamodel::Type* parent);

    QPoint position();
    model::enums::PortDirection direction();

    virtual int type() const {
        return (int)ComponentDescriptorType::PORT_DESCRIPTOR;
    }
};

} // namespace metamodel
} // namespace q2d
#endif // PORTDESCRIPTOR_H
