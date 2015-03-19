#ifndef COMPONENT_H
#define COMPONENT_H

#include "ModelElement.h"

#include <QList>

namespace q2d {

namespace metamodel {
class ComponentDescriptor;
}

namespace model {
class Model;
class ComponentPort;

// TODO documentation
// TODO a component should observe its internal model to be informed of changes
class Component : public ModelElement {
private:
    metamodel::ComponentDescriptor* m_descriptor;
    QList<ComponentPort*> m_ports;
    Model* m_internalModel;
public:
    Component(metamodel::ComponentDescriptor* descriptor,
              DocumentEntry* relatedEntry,
              Model* internalModel = nullptr);

    void addPort(ComponentPort* port) {
        Q_CHECK_PTR(port);
        m_ports.append(port);
    }

    QList<ComponentPort*>* inputPorts();
    QList<ComponentPort*>* outputPorts();

    QStringList nodeVariables() const override;
    QStringList configVariables() const override;
    QStringList functions() const override;

    metamodel::ComponentDescriptor* descriptor() const;
};

} // namespace model
} // namespace q2d

#endif // COMPONENT_H
