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
class ModulePort;
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
    QList<ModulePort*> m_inputPorts;
    QList<ModulePort*> m_outputPorts;
public:
    Model(Document* parent);

    void addComponent(Component* toAdd);
    void addInputPort(ModulePort* inputPort);
    void addOutputPort(ModulePort* outputPort);
    void addConductor(model::Conductor* conductor);

    QList<Component*> components() const {
        return m_components;
    }

    QList<Conductor*> conductors() const {
        return m_conductors;
    }

    QList<ModulePort*> outsidePorts() const {
        QList<ModulePort*> result = QList<ModulePort*>(m_inputPorts);
        result.append(m_outputPorts);
        return result;
    }
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
