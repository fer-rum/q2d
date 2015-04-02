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
class Component
        : public InterfacingME {
private:
    metamodel::ComponentDescriptor* m_descriptor;
    Model* m_internalModel;
public:
    Component(metamodel::ComponentDescriptor* descriptor,
              DocumentEntry* relatedEntry,
              Model* internalModel = nullptr);

    /**
     * @brief addPort is a public facade to the accessor providing type specialization
     * @param port
     */
    void addPort(ComponentPort* port);

    QList<ComponentPort*>* inputPorts();
    QList<ComponentPort*>* outputPorts();

    QStringList configVariables() const override;
    QStringList functions() const override;

    metamodel::ComponentDescriptor* descriptor() const;

    virtual QPoint portPosition(QString portLocalId) override;
};

} // namespace model
} // namespace q2d

#endif // COMPONENT_H
