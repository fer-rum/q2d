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
    : ModelElement(relatedEntry) {
    Q_CHECK_PTR(type);

    m_internalModel = internalModel;
    m_descriptor = type;
    m_ports = QList<ComponentPort*>();
}

ComponentDescriptor*
Component::descriptor() const {
    return m_descriptor;
}

QStringList
Component::configVariables() const {
    return m_descriptor->configVariables();
}

QStringList
Component::nodeVariables() const {

    QStringList result;

    for (Port * p : m_ports) {
        result.append((p->nodeVariables()));
    }
    return result;
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
Component::inputPorts(){
    QList<ComponentPort*>* result = new QList<ComponentPort*>();

    for(ComponentPort* port : m_ports){
        if(port->direction() == enums::PortDirection::IN){
            result->append(port);
        }
    }
    return result;
}

QList<ComponentPort*>*
Component::outputPorts(){
    QList<ComponentPort*>* result = new QList<ComponentPort*>();

    for(ComponentPort* port : m_ports){
        if(port->direction() == enums::PortDirection::OUT){
            result->append(port);
        }
    }
    return result;
}
