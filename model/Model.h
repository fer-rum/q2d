#ifndef MODEL_H
#define MODEL_H

#include "Component.h"
#include "Conductor.h"
#include "Node.h"

#include <QString>
#include <QList>

namespace q2d {
namespace model {

    // ahead declaration
    class Component;
    class Conductor;
    class Port;

// TODO documentation
// TODO visitor-pattern
// TODO utility functions
class Model {
private:
    QString name;
    QList<Component*> components;
    QList<Conductor*> conductors;
    QList<Port*> outsidePorts;
public:
    Model(QString name);
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
