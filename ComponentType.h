#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include "ComponentDescriptor.h"

#include <QGraphicsSvgItem>
#include <QIcon>

namespace q2d {

    class ComponentCategory;

    /**
     * @brief The ComponentType class contains common elements of all components of a certain type.
     *
     * A component type is the abstraction of component instances that share the same functionality and behaviour.
     */
class ComponentType : public ComponentDescriptor {
        // TODO signals and slots
private:
    void setSymbolPath(QString symbolPath);
    void loadCircuitSymbol(QString symbolFilePath);
    // TODO setPortInformation

public:
    explicit ComponentType(QString descriptionFile, ComponentCategory* parent = 0);
};

} // namespace q2d

#endif // COMPONENTTYPE_H
