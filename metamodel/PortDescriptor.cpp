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
                               QPointF position,
                               metamodel::ComponentDescriptor* parent)
    : ComponentElement(name, parent) {

    this->setData(q2d::model::enums::PortDirectionToString(direction),
                  ComponentDescriptorRole::PORT_DIRECTION);
    this->setData(position, ComponentDescriptorRole::PORT_POSITION);

    // find and set the icon
    QString setting;
    switch (direction) {
    case model::enums::PortDirection::IN :
        setting = KEY_FILE_PORT_IN;
        break;
    case model::enums::PortDirection::OUT :
        setting = KEY_FILE_PORT_OUT;
        break;
    case model::enums::PortDirection::IN_OUT :
        setting = KEY_FILE_PORT_INOUT;
        break;
    default:
        setting = QString();
    }

    QString fileName = Application::instance()->getSetting(setting).toString();

    if (!fileName.isEmpty()) {
        QIcon icon = QIcon(fileName);
        this->setIcon(icon);
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

/**
 * @brief PortDescriptor::direction is a convenience getter.
 * @return
 */
q2d::model::enums::PortDirection
PortDescriptor::direction() {
    return q2d::model::enums::StringToPortDirection(this->data(
                ComponentDescriptorRole::PORT_DIRECTION).toString());
}
