#include "../DocumentEntry.h"
#include "Component.h"
#include "Port.h"

using namespace q2d::model;

Port::Port(enums::PortDirection direction, DocumentEntry *relatedEntry)
    : Node(relatedEntry){
    Q_ASSERT(direction == enums::PortDirection::IN
             || direction == enums::PortDirection::OUT);
    m_direction = direction;
}

QStringList
ComponentPort::nodeVariables() const {
    return QStringList(this->relatedEntry()->id());
}

ComponentPort::ComponentPort(enums::PortDirection direction, Component *interfacedComponent, DocumentEntry *relatedEntry)
    : Port(direction, relatedEntry) {
    Q_CHECK_PTR(interfacedComponent);

    m_component = interfacedComponent;
    m_component->addPort(this);

    switch(m_direction){
    case enums::PortDirection::IN :
        this->addDrivenElement(interfacedComponent);
        break;
    case enums::PortDirection::OUT :
        this->addDriver(interfacedComponent);
        break;
    default: // this should not happen
        Q_ASSERT(false);
    }
}

Component*
ComponentPort::component() const {
    return m_component;
}

ModulePort::ModulePort(enums::PortDirection direction, DocumentEntry* relatedEntry)
    : Port(enums::invert(direction), relatedEntry){
    Q_CHECK_PTR(relatedEntry);
    Q_ASSERT(m_direction == enums::PortDirection::IN
             || m_direction == enums::PortDirection::OUT);
}

QStringList
ModulePort::inputVariables() const {
    if(m_direction == enums::PortDirection::OUT){
        return QStringList(this->relatedEntry()->id());
    } else {
        return Port::inputVariables();
    }
}

QStringList
ModulePort::nodeVariables() const {
    if(m_direction == enums::PortDirection::IN){
        return QStringList(this->relatedEntry()->id());
    } else {
        return Port::nodeVariables();
    }
}
