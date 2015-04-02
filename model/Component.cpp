#include "../Constants.h"
#include "../DocumentEntry.h"
#include "Component.h"
#include "Model.h"
#include "Port.h"
#include "metamodel/ComponentDescriptor.h"

using namespace q2d::constants;
using namespace q2d::model;
using namespace q2d::metamodel;

Component::Component(ComponentDescriptor* type, DocumentEntry* relatedEntry,
                     Model* internalModel)
    : InterfacingME(relatedEntry) {
    Q_CHECK_PTR(type);

    m_internalModel = internalModel;
    m_descriptor = type;
}

ComponentDescriptor*
Component::descriptor() const {
    return m_descriptor;
}

QStringList
Component::configVariables() const {
    return m_descriptor->configVariables();
}

/**
 * @brief Component::functions
 * The returned functions use the component-local namespace.
 * @return
 */
QStringList
Component::functions() const {
    return m_descriptor->functions();
}

QList<ComponentPort*>*
Component::inputPorts() {
    QList<ComponentPort*>* result = new QList<ComponentPort*>();

    for (Port * port : m_ports) {
        if (port->direction() == enums::PortDirection::IN) {
            result->append(static_cast<ComponentPort*>(port));
        }
    }
    return result;
}

QList<ComponentPort*>*
Component::outputPorts() {
    QList<ComponentPort*>* result = new QList<ComponentPort*>();

    for (Port * port : m_ports) {
        if (port->direction() == enums::PortDirection::OUT) {
            result->append(static_cast<ComponentPort*>(port));
        }
    }
    return result;
}

void
Component::addPort(ComponentPort* port) {
    InterfacingME::addPort(port);
}

QPoint
Component::portPosition(QString portLocalId) {
    return m_descriptor->portPosition(portLocalId);
}
