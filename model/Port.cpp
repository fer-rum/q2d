#include "../DocumentEntry.h"
#include "../Enumerations.h"
#include "../factories/ToolTipFactory.h"
#include "Component.h"
#include "ModelElement.h"
#include "ModuleInterface.h"
#include "Port.h"

using namespace q2d::model;

Port::Port(enums::PortDirection direction, DocumentEntry* relatedEntry, InterfacingME* interfaced)
    : Node(relatedEntry) {
    Q_ASSERT(direction == enums::PortDirection::IN
             || direction == enums::PortDirection::OUT);
    m_direction = direction;

    interfaced->addPort(this);

    switch (m_direction) {
    case enums::PortDirection::IN :
        this->addDrivenElement(interfaced);
        break;
    case enums::PortDirection::OUT :
        this->addDriver(interfaced);
        break;
    default: // this should not happen
        Q_ASSERT(false);
    }
}

QMap<QString, QString>
Port::propertyMap() const {
    return factories::ToolTipFactory::propertyMap(this);
}

QStringList
ComponentPort::nodeVariables() const {
    return QStringList(this->relatedEntry()->fullId());
}

ComponentPort::ComponentPort(enums::PortDirection direction, DocumentEntry* relatedEntry,
                             Component* interfacedComponent)
    : Port(direction, relatedEntry, interfacedComponent) {
    Q_CHECK_PTR(interfacedComponent);

    m_component = interfacedComponent;
}

Component*
ComponentPort::component() const {
    return m_component;
}

ModulePort::ModulePort(enums::PortDirection direction, DocumentEntry* relatedEntry,
                       ModuleInterface* moduleInterface)
    : Port(direction, relatedEntry, moduleInterface) {
    Q_CHECK_PTR(relatedEntry);
    Q_ASSERT(m_direction == enums::PortDirection::IN
             || m_direction == enums::PortDirection::OUT);
}

/**
 * @brief ModulePort::inputVariables
 * If the instances direction is out, the associated module interface has an IN direction.
 * Therefore the port is to be represented by an input variable.
 * @return
 */
QStringList
ModulePort::inputVariables() const {
    if (m_direction == enums::PortDirection::OUT) {
        return QStringList(relatedEntry()->localId());
    } else {
        return Port::inputVariables();
    }
}

QStringList
ModulePort::nodeVariables() const {
    if (m_direction == enums::PortDirection::IN) {
        return QStringList(relatedEntry()->localId());
    } else {
        return Port::nodeVariables();
    }
}

QStringList
ModulePort::functions() const {
    return QStringList(relatedEntry()->localId() + " = " + relatedEntry()->fullId());
}
