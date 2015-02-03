#include "Component.h"

#include "metamodel/ComponentType.h"

using namespace q2d::model;
using namespace q2d::metamodel;

Component::Component(ComponentType* type, Model* model, Model* internalModel)
    : ModelElement(model) {
    Q_CHECK_PTR(type);

    m_internalModel = internalModel;
    m_type = type;
    m_ports = QList<Port*>();
}

/**
 * @brief Component::createPort creates a new port with the given parameters
 * and adds it to the component.
 *
 * @param name
 * @param direction
 * @return the newly created port
 */
Port*
Component::createPort(PortDirection direction) {
    Port* newPort = new Port(direction, this, this->model());
    m_ports.append(newPort);
    return newPort;
}

ComponentType*
Component::type() const {
    return m_type;
}
