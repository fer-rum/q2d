#include "Component.h"

#include "metamodel/ComponentDescriptor.h"

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
