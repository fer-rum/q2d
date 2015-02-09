#ifndef CONFIGURATIONBITDESCRIPTOR_H
#define CONFIGURATIONBITDESCRIPTOR_H

#include "../Enumerations.h"
#include "ComponentElement.h"

#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

// forward declaration
class ComponentDescriptor;

class ConfigBitGroupDescriptor :
        public ComponentElement {
private:
    QString m_name;
    unsigned int m_memberCount;

public:
    explicit ConfigBitGroupDescriptor(
            QString groupName,
            unsigned int memberCount,
            metamodel::ComponentDescriptor* parent = nullptr);

    QString name() const;
    unsigned int memberCount() const;

    virtual int type() const {
        return enums::elementTypeToInt(enums::ElementType::CONFIG_BIT_GROUP);
    }
};

class ConfigBitDescriptor :
        public ComponentElement {
public:
    explicit ConfigBitDescriptor(QString name, ConfigBitGroupDescriptor* parent);

    virtual int type() const {
        return enums::elementTypeToInt(enums::ElementType::CONFIG_BIT);
    }
};

} // namespace metamodel
} // namespace q2d

#endif // CONFIGURATIONBITDESCRIPTOR_H
