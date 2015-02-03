#include "PortDescriptor.h"

#include "Application.h"
#include "ComponentDescriptor.h"
#include "ComponentType.h"
#include "Constants.h"

#include <QSettings>

using namespace q2d::metamodel;
using namespace q2d::constants;
using namespace q2d::model;

/**
 * @brief PortDescriptor::PortDescriptor
 * @param name is ithe pure port name without any hierarchy information attached.
 * @param direction
 * @param position
 * @param parent is the ComponentType this PortDescriptor belongs to.
 */
PortDescriptor::PortDescriptor(QString name,
                               PortDirection direction,
                               QPoint position,
                               ComponentType* parent)
    : QObject(parent), QStandardItem(name) {

    this->setData(direction, ComponentDescriptorRole::PORT_DIRECTION);
    this->setData(position, ComponentDescriptorRole::PORT_POSITION);

    // find and set the icon
    QString setting;
    switch (direction) {
    case IN :
        setting = KEY_PORT_IN_FILE;
        break;
    case OUT :
        setting = KEY_PORT_OUT_FILE;
        break;
    case IN_OUT :
        setting = KEY_PORT_INOUT_FILE;
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
PortDirection
PortDescriptor::direction() {
    return static_cast<model::PortDirection>(
               this->data(ComponentDescriptorRole::PORT_DIRECTION).toInt());
}
