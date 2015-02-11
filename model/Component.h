#ifndef COMPONENT_H
#define COMPONENT_H

#include "Model.h"
#include "ModelElement.h"
#include "Node.h"

#include <QList>

namespace q2d {

namespace metamodel {
class ComponentDescriptor;
}

namespace model {

// ahead declaration
class Model;

// TODO documentation
// TODO a component should observe its internal model to be informed of changes
class Component : public ModelElement {
private:
    metamodel::ComponentDescriptor* m_descriptor;
    QList<Port*> m_ports;
    Model* m_internalModel;
public:
    Component(metamodel::ComponentDescriptor* descriptor,
              Model* parentModel, DocumentEntry* relatedEntry = nullptr, Model* internalModel = nullptr);

    void addPort(Port* port) {
        Q_CHECK_PTR(port);
        m_ports.append(port);
    }

    QStringList nodeVariables() const override;
    QStringList configVariables() const override;
    QStringList functions() const override;

    metamodel::ComponentDescriptor* descriptor() const;
};

} // namespace model
} // namespace q2d

#endif // COMPONENT_H
