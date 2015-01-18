#ifndef COMPONENTDESCRIPTOR_H
#define COMPONENTDESCRIPTOR_H

#include <QGraphicsSvgItem>
#include <QObject>
#include <QStandardItem>

namespace q2d {
namespace metamodel {

    // forward declaration
    class ComponentCategory;

/**
 * @brief The ComponentDescriptorRole enum lists all roles, that can be fulfilled in describing an ComponentType.
 */
enum ComponentDescriptorRole {
    CIRCUIT_SYMBOL_FILE = Qt::UserRole + 2000,
    PORT_DIRECTION,
    PORT_POSITION,
    HIERARCHY_NAME
    // TODO custom parameters
    // TODO boolean function
};

class ComponentDescriptor :
        public QObject,
        public QStandardItem {
    Q_OBJECT
public:
    explicit ComponentDescriptor(QString name, ComponentCategory* parent = 0);

    QString hierarchyName();
};

} // namespace metamodel
} // namespace q2d

// Metatype declaration
Q_DECLARE_METATYPE(QGraphicsSvgItem*) // for circuit symbols
// TODO is this still used?

#endif // COMPONENTDESCRIPTOR_H
