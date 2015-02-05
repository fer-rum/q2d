#include "Constants.h"

namespace q2d {
namespace constants {

QString HIERARCHY_SEPERATOR    = "/";

QString KEY_DIR_COMPONENTS  = "paths/componentsFolder";
QString KEY_DIR_PROJECTS    = "paths/projectsFolder";

QString KEY_FILE_BIT_GROUP  = "paths/symbols/bit_group";
QString KEY_FILE_PORT_IN    = "paths/symbols/port_in";
QString KEY_FILE_PORT_OUT   = "paths/symbols/port_out";
QString KEY_FILE_PORT_INOUT = "paths/symbols/port_inout";

QString JSON_DESC_CONFIG_BIT_GROUP_NAME  = "bitGroup_name";
QString JSON_DESC_CONFIG_BIT_GROUP_SIZE = "bitGroup_size";

QString JSON_HIERARCHY_TYPE_CATEGORY    = "componentCategory";
QString JSON_HIERARCHY_TYPE_COMPONENT   = "componentType";
QString JSON_HIERARCHY_CATEGORY_NAME    = "name";
QString JSON_HIERARCHY_TYPE      = "hierarchy_type";
QString JSON_HIERARCHY_CHILD    = "child";
QString JSON_HIERARCHY_SOURCE   = "descriptorPath";
QString JSON_DESC_COMPONENT_NAME = "name";
QString JSON_PORTS          = "ports";
QString JSON_PORT_DIRECTION = "direction";
QString JSON_PORT_NAME      = "name";
QString JSON_PORT_POSITION  = "pos";
QString JSON_POSITION_X    = "x";
QString JSON_POSITION_Y    = "y";
QString JSON_SYMBOL_PATH    = "symbolFile";
QString JSON_DESC_CONFIG_BIT_GROUP     = "descriptor_configBits";
QString JSON_DOCENTRY                   = "entry";
QString JSON_DOCENTRY_ID                = "entry_id";
QString JSON_DOCENTRY_MODEL_ELEMENT     = "entry_model";
QString JSON_DOCENTRY_SCHEMATIC_ELEMENT = "entry_schematic";
QString JSON_DOCENTRY_PARENT            = "entry_parent_id";
QString JSON_DOCENTRY_TYPE              = "entry_type";
QString JSON_SCHEMATIC_SUB_TYPE         = "schematicSubType";
QString JSON_SCHEMATIC_ADDITIONAL       = "additionalInfo";
QString JSON_SCHEMATIC_POSITION         = "scenePos";
QString JSON_WIRE_START                 = "wire_start";
QString JSON_WIRE_END                   = "wire_end";

QString GENERAL_TYPE_COMPONENT  = "component";
QString GENERAL_TYPE_PORT       = "port";
QString GENERAL_TYPE_WIRE       = "wire";
QString GENERAL_TYPE_UNDEFINED  = "undefined";

QString MIME_COMPONENT_TYPE = "application/component-type";
QString MIME_WIRE_START_POS = "application/wire-start-pos";

QString FILE_COMPONENT_TREE    = "/components.q2tree";
QString EXTENSION_DOCFILE           = ".q2doc";
} // namespace constants
} // namespace q2d
