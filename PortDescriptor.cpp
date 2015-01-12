#include "PortDescriptor.h"

#include "Application.h"
#include "ComponentDescriptor.h"
#include "ComponentType.h"
#include "Constants.h"

#include <QSettings>

using namespace q2d;
using namespace q2d::constants;
using namespace q2d::model;

PortDescriptor::PortDescriptor(QString name,
                        PortDirection direction,
                        QPoint position,
                        ComponentType* parent)
    : QObject(parent), QStandardItem(name) {

    this->setData(direction, ComponentDescriptorRole::PORT_DIRECTION);
    this->setData(position, ComponentDescriptorRole::PORT_POSITION);

    // find and set the icon

    QString setting;
    switch(direction){
    case IN :
        setting = KEY_PORT_IN_FILE; break;
    case OUT :
        setting = KEY_PORT_OUT_FILE; break;
    case IN_OUT :
        setting = KEY_PORT_INOUT_FILE; break;
    default:
        setting = QString();
    }

    QString fileName = Application::instance()->getSetting(setting).toString();

    if(!fileName.isEmpty()){
        QIcon icon = QIcon(fileName);
        this->setIcon(icon);
    }
}
