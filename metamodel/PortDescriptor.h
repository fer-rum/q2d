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
    Q_OBJECT
public:
    explicit PortDescriptor(QString name,
                            model::enums::PortDirection direction,
                            QPoint position,
                            metamodel::ComponentDescriptor* parent = nullptr);

    QPoint position();
    void setPosition(QPoint position);
    model::enums::PortDirection direction();

    virtual int type() const {
        return (int)enums::ElementType::PORT;
    }
};

} // namespace metamodel
} // namespace q2d
#endif // PORTDESCRIPTOR_H
