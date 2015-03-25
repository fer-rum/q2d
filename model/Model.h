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
class ModuleInterface;
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
    QList<ModuleInterface*> m_inputPorts;
    QList<ModuleInterface*> m_outputPorts;
public:
    Model(Document* parent);

    void addComponent(Component* toAdd);
    void addInputPort(ModuleInterface* inputPort);
    void addOutputPort(ModuleInterface* outputPort);
    void addConductor(model::Conductor* conductor);

    QList<Component*> components() const {
        return m_components;
    }

    QList<Conductor*> conductors() const {
        return m_conductors;
    }

    QList<ModulePort*> outsidePorts() const;
};

} // namespace model
} // namespace q2d

#endif // MODEL_H
