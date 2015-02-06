#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <QStandardItem>

namespace q2d {

// FIXME deprecated
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

// FIXME deprecated
// replace with metamodel::enums::Type
enum ComponentDescriptorType {
    COMPONENT_TYPE = QStandardItem::UserType + 2000,
    COMPONENT_CATEGORY,
    PORT_DESCRIPTOR
};

namespace metamodel {
namespace enums {

/**
 * @brief The Type enum lists all concrete types of which a metamodel element can be.
 * Purely virtual types are ommitted.
 */
enum class ElementType {
    CATEGORY = QStandardItem::UserType + 2000,
    COMPONENT,
    CONFIG_BIT_GROUP,
    CONFIG_BIT,
    PORT,
    INVALID
};

int elementTypeToInt(ElementType t);
ElementType intToElementType(int i);

} // namespace enums
} // namespace metamodel

namespace model {
namespace enums {

enum class PortDirection {
    IN,
    OUT,
    IN_OUT,
    UNSPECIFIED
};

PortDirection StringToPortDirection(const QString string);
QString PortDirectionToString(const PortDirection direction);

/**
 * @brief The ConfigurationBitState enum
 * Represents the state of an q2d::model::ConfigurationBit
 *
 * Usually, the state is NOT_SET and may be changed to TRUE or FALSE after solving the SAT-problem
 * that is posed by the schematic, by the means of backward annotation.
 */
enum class ConfigurationBitState {
    FALSE,
    TRUE,
    NOT_SET
};

} // namespace enums
} // namespace model

} // namespace q2d
#endif // ENUMERATIONS_H
