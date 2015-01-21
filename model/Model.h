#ifndef MODEL_H
#define MODEL_H

#include "Component.h"
#include "Conductor.h"
#include "Node.h"

#include <QList>
#include <QObject>
#include <QString>


namespace q2d {

    // forward declaration
    class Document;

namespace model {

    // forward declaration
    class Component;
    class Conductor;
    class Port;

// TODO documentation
// TODO visitor-pattern
// TODO utility functions
class Model : public QObject {
    Q_OBJECT

private:
    QString name;
    QList<Component*> components;
    QList<Conductor*> conductors;
    QList<Port*> outsidePorts;
public:
    Model(Document* parent);

    void addComponent(Component* toAdd);
    Conductor* connect(Node* start, Node* end);
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
