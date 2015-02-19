#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QObject>
#include <QString>


namespace q2d {

// forward declaration
class Document;

namespace model {
class Component;
class Conductor;
class Node;
class Port;

namespace enums {
enum class PortDirection;
}

// TODO documentation
class Model : public QObject {
    Q_OBJECT

private:
    QString m_name;
    QList<Component*> m_components;
    QList<Conductor*> m_conductors;
    QList<Port*> m_inputPorts;
    QList<Port*> m_outputPorts;
public:
    Model(Document* parent);

    void addComponent(Component* toAdd);
    void addInputPort(Port* inputPort);
    void addOutputPort(Port* outputPort);

    Conductor* connect(Node* start, Node* end);

    QList<Component*> components() const {
        return m_components;
    }

    QList<Conductor*> conductors() const {
        return m_conductors;
    }

    QList<Port*> outsidePorts() const {
        QList<Port*> result = QList<Port*>(m_inputPorts);
        result.append(m_outputPorts);
        return result;
    }
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
