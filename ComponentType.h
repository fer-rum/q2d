#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include "ComponentDescriptor.h"
#include "model/PortDirection.h"

#include <QGraphicsSvgItem>
#include <QIcon>

namespace q2d {

    class ComponentCategory;

// TODO support seperate Icon files as determined by json
/**
* @brief The ComponentType class contains common elements of all components of a certain type.
*
* A component type is the abstraction of component instances that share the same functionality and behaviour.
*/
class ComponentType : public ComponentDescriptor {
    // TODO signals and slots
    // TODO port information
private:
    void loadCircuitSymbol(QString symbolFilePath);
    // TODO setPortInformation

public:
    explicit ComponentType(QString name, ComponentCategory* parent = 0);

    void setSymbolPath(QString symbolPath);
    void addPort(QString name, QPoint relativePosition, q2d::model::PortDirection direction);
};

} // namespace q2d

#endif // COMPONENTTYPE_H
