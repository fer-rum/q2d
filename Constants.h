#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace q2d {
namespace constants {

// internally used constants


// File extensions for saving and loading

extern QString EXTENSION_DOCFILE;

/**
 * @brief FILE_COMPONENT_TREE is the file name,
 * that will be given to files containing the component hierarchy upon saving
 * a project.
 * It needs to be prefixed with the path of the project folder it refers to.
 */
extern QString FILE_COMPONENT_TREE;

extern QString GENERAL_TYPE_COMPONENT;
extern QString GENERAL_TYPE_PORT;
extern QString GENERAL_TYPE_WIRE;
extern QString GENERAL_TYPE_UNDEFINED;

/**
 * @brief HIERARCHY_PATH_SEPERATOR is used when fetching the hierarchy names
 * of ComponentDescriptors to split th seperate levels of the hierarchy.
 * It also is applied when seperating the ids of port instances
 * from their component parents.
 */
extern QString HIERARCHY_SEPERATOR;

// JSON keywords
extern QString JSON_COMPONENT_NAME;

// Configuration bit group details
extern QString JSON_CONFIG_BIT_GROUP_NAME;
extern QString JSON_CONFIG_BIT_GROUP_SIZE;

// Im-/Export of Document entries
extern QString JSON_DOCENTRY;
extern QString JSON_DOCENTRY_CONFIG_BITS;
extern QString JSON_DOCENTRY_ID;
extern QString JSON_DOCENTRY_MODEL_ELEMENT;
extern QString JSON_DOCENTRY_PARENT;
extern QString JSON_DOCENTRY_SCHEMATIC_ELEMENT;
extern QString JSON_DOCENTRY_TYPE;

extern QString JSON_PORTS;
extern QString JSON_PORT_DIRECTION;
extern QString JSON_PORT_NAME;
extern QString JSON_PORT_POSITION;

extern QString JSON_POSITION_X;
extern QString JSON_POSITION_Y;

// Im-/Export of SchematicsSceneChild enrties
extern QString JSON_DOCENTRY_TYPE;

extern QString JSON_HIERARCHY_CATEGORY_NAME;
extern QString JSON_HIERARCHY_CHILD;
extern QString JSON_HIERARCHY_SOURCE;
extern QString JSON_HIERARCHY_TYPE;
extern QString JSON_HIERARCHY_TYPE_CATEGORY;
extern QString JSON_HIERARCHY_TYPE_COMPONENT;

extern QString JSON_SCHEMATIC_SUB_TYPE;
extern QString JSON_SCHEMATIC_ADDITIONAL;
extern QString JSON_SCHEMATIC_POSITION;

extern QString JSON_SYMBOL_PATH;

extern QString JSON_WIRE_START;
extern QString JSON_WIRE_END;

// Keys for QSettings (application wide)
extern QString KEY_DIR_COMPONENTS;
extern QString KEY_DIR_PROJECTS;

extern QString KEY_FILE_BIT_GROUP;
extern QString KEY_FILE_PORT_IN;
extern QString KEY_FILE_PORT_INOUT;
extern QString KEY_FILE_PORT_OUT;

// custom MIME types
extern QString MIME_COMPONENT_TYPE;
extern QString MIME_WIRE_START_POS;

} // namespace constants
} // namespace q2d

#endif // CONSTANTS_H
