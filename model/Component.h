#ifndef COMPONENT_H
#define COMPONENT_H

#include "Model.h"
#include "ModelElement.h"
#include "Node.h"

#include <QList>

namespace q2d {

namespace metamodel {
class Type;
}

namespace model {

// ahead declaration
class Model;

// TODO documentation
// TODO visitor-pattern
// TODO a component should observe its internal model to be informed of changes
class Component : public ModelElement {
private:
    metamodel::Type* m_type;
    QList<Port*> m_ports;
    Model* m_internalModel;
public:
    Component(metamodel::Type* type, Model* model, Model* internalModel = nullptr);

    Port* createPort(enums::PortDirection direction);

    metamodel::Type* type() const;
};

} // namespace model
} // namespace q2d

#endif // COMPONENT_H
