#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

#include "ModelElement.h"

#include <QPoint>

namespace q2d {
namespace model {
class ModulePort;


class ModuleInterface
        : public InterfacingME {

    enums::PortDirection m_direction;

public:
    ModuleInterface(DocumentEntry* relatedEntry, enums::PortDirection moduleDirection)
        : InterfacingME(relatedEntry) {
        m_direction = moduleDirection;
    }

    void addPort(ModulePort* port);
    ModulePort* port();

    enums::PortDirection direction() {
        return m_direction;
    }
};

} // namespace model
} // namespace q2d

#endif // MODULEINTERFACE_H
