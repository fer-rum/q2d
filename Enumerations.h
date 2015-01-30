#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <QStandardItem>

namespace q2d {

/**
 * @brief The ComponentDescriptorRole enum lists all roles
 * that can be fulfilled by data of an item in the component hierarchy.
 */
enum ComponentDescriptorRole {
    CIRCUIT_SYMBOL_FILE = Qt::UserRole + 2000,
    DESCRIPTOR_FILE,    // path to the descriptor file that was used for instantiating
    PORT_DIRECTION,
    PORT_POSITION,
    HIERARCHY_NAME
};

/**
 * @brief The ComponentDescriptorType enum lists all types
 * of which items in the component hierarchy can be.
 */
enum ComponentDescriptorType {
    COMPONENT_TYPE = QStandardItem::UserType + 2000,
    COMPONENT_CATEGORY,
    PORT_DESCRIPTOR
};

} // namespace q2d
#endif // ENUMERATIONS_H
