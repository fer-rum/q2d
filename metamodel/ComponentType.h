#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include "ComponentDescriptor.h"
#include "model/PortDirection.h"

#include <QGraphicsSvgItem>
#include <QIcon>

namespace q2d {
namespace metamodel {

class ComponentCategory;
class ConfigBitGroupDescriptor;

// TODO support seperate Icon files as determined by json
/**
* @brief The ComponentType class contains common elements of all components of a certain type.
*
* A component type is the abstraction of component instances that share the same functionality and behaviour.
*/
class ComponentType : public ComponentDescriptor {
    // TODO signals and slots
private:
    /**
     * @brief m_instanceIndex counts how often a component of this type has been
     * instantiated so far to be able to generate unique names.
     * The counting is done via tracking calls of generateId().
     */
    int m_instanceIndex;

    void loadCircuitSymbol(QString symbolFilePath);

public:
    explicit ComponentType(QString name, ComponentCategory* parent = 0);

    QString symbolPath();
    void setSymbolPath(QString symbolPath);

    QString descriptorPath() const;
    void setDescriptorPath(const QString path);

    // TODO transform
    // void addPort(PortDescriptor*);
    void addPort(QString name, QPoint relativePosition, model::PortDirection direction);
    void addConfigBitGroup(ConfigBitGroupDescriptor* configBitGroup);

    QString generateId();

    virtual int type() const {
        return (int)ComponentDescriptorType::COMPONENT_TYPE;
    }
};

} // namespace metamodel
} // namespace q2d

#endif // COMPONENTTYPE_H
