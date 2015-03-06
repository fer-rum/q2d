#ifndef PORT_H
#define PORT_H

#include "Node.h"

namespace q2d {
namespace model {

// TODO documentation
class Port : public Node {
private:
    enums::PortDirection m_direction;
public:
    /**
     * @brief Port
     * @param direction
     * @param topLevel may be nullptr in case this is an outside port
     * @param parent
     * @param relatedEntry
     */
    Port(enums::PortDirection direction, Component* topLevel, Model* parent,
         DocumentEntry* relatedEntry = nullptr);

    enums::PortDirection direction() const {
        return m_direction;
    }

    virtual QStringList nodeVariables() const override;
};

} // namespace model
} // namewspace q2d

#endif // PORT_H
