#ifndef CONFIGURATIONBITDESCRIPTOR_H
#define CONFIGURATIONBITDESCRIPTOR_H

#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

// NOTE: in the future this might also be used to describe a whole set of config bits

// forward declaration
class ComponentType;

class ConfigBitGroupDescriptor :
        public QObject,
        public QStandardItem
{
    Q_OBJECT
public:
    explicit ConfigBitGroupDescriptor(QString groupName, int memberCount, ComponentType* parent = nullptr);
};

class ConfigBitDescriptor :
        public QObject,
        public QStandardItem
{
    Q_OBJECT
public:
    explicit ConfigBitDescriptor(QString name, ConfigBitGroupDescriptor* parent);
};

} // namespace metamodel
} // namespace q2d

#endif // CONFIGURATIONBITDESCRIPTOR_H
