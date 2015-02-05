#ifndef CONFIGURATIONBITDESCRIPTOR_H
#define CONFIGURATIONBITDESCRIPTOR_H

#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

// forward declaration
class Type;

class ConfigBitGroupDescriptor :
        public QObject,
        public QStandardItem
{
    Q_OBJECT
public:
    explicit ConfigBitGroupDescriptor(QString groupName, int memberCount, metamodel::Type* parent = nullptr);
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
