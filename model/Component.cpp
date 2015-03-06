#include "../Constants.h"
#include "../DocumentEntry.h"
#include "Component.h"
#include "Port.h"
#include "metamodel/ComponentDescriptor.h"

using namespace q2d::constants;
using namespace q2d::model;
using namespace q2d::metamodel;

Component::Component(ComponentDescriptor* type, Model* parentModel, DocumentEntry* relatedEntry,
                     Model* internalModel)
    : ModelElement(parentModel, relatedEntry) {
    Q_CHECK_PTR(type);

    m_internalModel = internalModel;
    m_descriptor = type;
    m_ports = QList<Port*>();
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
