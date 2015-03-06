#include "../DocumentEntry.h"
#include "Component.h"
#include "Port.h"

using namespace q2d::model;

Port::Port(enums::PortDirection direction, Component* topLevel, Model* parent,
           DocumentEntry* relatedEntry) : Node(parent, relatedEntry) {
    Q_CHECK_PTR(parent);

    m_direction = direction;

    if (topLevel != nullptr) {
        if (m_direction == enums::PortDirection::IN) {
            this->addDrivenElement(topLevel);
        } else if (m_direction == enums::PortDirection::OUT) {
            this->addDriver(topLevel);
        }
        topLevel->addPort(this);
    }
}

QStringList
Port::nodeVariables() const {
    return QStringList(this->relatedEntry()->id());
}
