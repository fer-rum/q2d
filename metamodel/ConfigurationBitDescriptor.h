#ifndef CONFIGURATIONBITDESCRIPTOR_H
#define CONFIGURATIONBITDESCRIPTOR_H

#include "../Enumerations.h"
#include "ComponentElement.h"

#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

// forward declaration
class Type;

class ConfigBitGroupDescriptor :
        public ComponentElement {
public:
    explicit ConfigBitGroupDescriptor(
            QString groupName, int memberCount, metamodel::Type* parent = nullptr);
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
