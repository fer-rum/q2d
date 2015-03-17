#include "PortDescriptor.h"

#include "Application.h"
#include "Constants.h"
#include "Enumerations.h"
#include "HierarchyElement.h"
#include "ComponentDescriptor.h"
#include <QSettings>

using namespace q2d::metamodel;
using namespace q2d::constants;

/**
 * @brief PortDescriptor::PortDescriptor
 * @param name is ithe pure port name without any hierarchy information attached.
 * @param direction
 * @param position
 * @param parent is the ComponentType this PortDescriptor belongs to.
 */
PortDescriptor::PortDescriptor(QString name,
                               model::enums::PortDirection direction,
                               QPoint position,
                               metamodel::ComponentDescriptor* parent)
    : ComponentElement(name, parent) {

    this->setData(q2d::model::enums::PortDirectionToString(direction),
                  ComponentDescriptorRole::PORT_DIRECTION);
    this->setPosition(position);

    // find and set the icon
    QString setting;
    switch (direction) {
    case model::enums::PortDirection::IN :
        this->setIcon(QIcon(":/icons/ressources/icons/port_in.svg"));
        break;
    case model::enums::PortDirection::OUT :
        this->setIcon(QIcon(":/icons/ressources/icons/port_out.svg"));
        break;
    case model::enums::PortDirection::IN_OUT :
        this->setIcon(QIcon(":/icons/ressources/icons/port_inout.svg"));
        break;
    default:
        setting = QString();
    }
}

/**
 * @brief PortDescriptor::position is a convenience getter.
 * @return
 */
QPoint
PortDescriptor::position() {
    return this->data(ComponentDescriptorRole::PORT_POSITION).toPoint();
}

void
PortDescriptor::setPosition(QPoint position){
    this->setData(position, ComponentDescriptorRole::PORT_POSITION);
}

/**
 * @brief PortDescriptor::direction is a convenience getter.
 * @return
 */
q2d::model::enums::PortDirection
PortDescriptor::direction() {
    return q2d::model::enums::StringToPortDirection(this->data(
                ComponentDescriptorRole::PORT_DIRECTION).toString());
}
