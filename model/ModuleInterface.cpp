#include "ModuleInterface.h"
#include "Port.h"

#include <QList>

using namespace q2d::model;

void
ModuleInterface::addPort(ModulePort* port) {
    InterfacingME::addPort(port);
}

ModulePort*
ModuleInterface::port() {
    return static_cast<ModulePort*>(m_ports.first());
}
