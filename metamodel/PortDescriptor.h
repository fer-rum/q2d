#ifndef PORTDESCRIPTOR_H
#define PORTDESCRIPTOR_H

#include "model/PortDirection.h"

#include <QStandardItem>
#include <QPoint>
#include <QObject>

namespace q2d {

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
};

} // namespace q2d
#endif // PORTDESCRIPTOR_H
