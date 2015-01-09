#ifndef COMPONENTDESCRIPTOR_H
#define COMPONENTDESCRIPTOR_H

#include <QGraphicsSvgItem>
#include <QObject>
#include <QStandardItem>

namespace q2d {

    // forward declaration
    class ComponentCategory;

/**
 * @brief The ComponentDescriptorRole enum lists all roles, that can be fulfilled in describing an ComponentType.
 */
enum ComponentDescriptorRole {
    CIRCUIT_SYMBOL_FILE = Qt::UserRole + 2000,
    PORT_INFORMATION
    // TODO custom parameters
    // TODO boolean function
};

class ComponentDescriptor :
        public QObject,
        public QStandardItem {
    Q_OBJECT
public:
    explicit ComponentDescriptor(QString name, ComponentCategory* parent = 0);
};

} // namespace q2d

// Metatype declaration
Q_DECLARE_METATYPE(QGraphicsSvgItem*) // for circuit symbols

#endif // COMPONENTDESCRIPTOR_H
