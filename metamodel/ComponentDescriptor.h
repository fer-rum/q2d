#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H


#include "../Enumerations.h"
#include "HierarchyElement.h"

#include <QGraphicsSvgItem>
#include <QIcon>
#include <QStringList>

namespace q2d {
namespace metamodel {

class Category;
class ConfigBitGroupDescriptor;
class PortDescriptor;

/**
* @brief The ComponentType class contains common elements of all components of a certain type.
*
* A component type is the abstraction of component instances that share the same functionality and behaviour.
*/
class ComponentDescriptor :
    public HierarchyElement {
private:
    /**
     * @brief m_instanceIndex counts how often a component of this type has been
     * instantiated so far to be able to generate unique names.
     * The counting is done via tracking calls of generateId().
     */
    int m_instanceIndex; // FIXME deprecated

    /**
     * @brief m_variables contains all variable names that are valid  in the context of the described component.
     * This is the case for ports and configuration bits.
     */
    QStringList m_configVariables;
    QStringList m_functions;
    // TODO move this into the appropriate descriptors

    void loadCircuitSymbol(QString symbolFilePath);

public:
    explicit ComponentDescriptor(QString name, Category* parent = nullptr);

    QString symbolPath();
    void setSymbolPath(QString symbolPath); // TODO better use QPath?

    QString descriptorPath() const;
    void setDescriptorPath(const QString path); // TODO better use QPath?

    void addPort(PortDescriptor* port);
    void addConfigBitGroup(ConfigBitGroupDescriptor* configBitGroup);
    void addFunction(QString function);

    QList<PortDescriptor*> ports();

    QStringList configVariables() const;
    QStringList functions() const;

    // FIXME deprecated
    QString generateId();

    virtual int type() const {
        return enums::elementTypeToInt(enums::ElementType::COMPONENT);
    }

    QPoint portPosition(QString portName);
};

} // namespace metamodel
} // namespace q2d

#endif // COMPONENTTYPE_H
