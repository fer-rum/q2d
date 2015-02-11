#ifndef MODEL_H
#define MODEL_H

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
class Node;
class Port;

// TODO documentation
class Model : public QObject {
    Q_OBJECT

private:
    QString m_name;
    QList<Component*> m_components;
    QList<Conductor*> m_conductors;
    QList<Port*> m_outsidePorts;
public:
    Model(Document* parent);

    void addComponent(Component* toAdd);
    Conductor* connect(Node* start, Node* end);

    QList<Component*> components() const {
        return m_components;
    }
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
