#include "Constants.h"

namespace q2d {
namespace constants {

QSize ICON_SIZE = QSize(48, 48);

QString HIERARCHY_SEPERATOR = "/";
QString NO_SYMBOL_FILE      = "(None)";

QString KEY_DIR_COMPONENTS  = "paths/componentsFolder";
QString KEY_DIR_PROJECTS    = "paths/projectsFolder";

QString KEY_FILE_BIT_GROUP  = "paths/symbols/bit_group";
QString KEY_FILE_PORT_IN    = "paths/symbols/port_in";
QString KEY_FILE_PORT_OUT   = "paths/symbols/port_out";
QString KEY_FILE_PORT_INOUT = "paths/symbols/port_inout";
QString KEY_FILE_OPORT_IN   = "paths/symbols/outside_port_in";
QString KEY_FILE_OPORT_OUT  = "paths/symbols/outside_port_out";

QString JSON_GENERAL_NAME = "name";
QString JSON_GENERAL_SIZE = "size";
QString JSON_GENERAL_POSITION  = "pos";
QString JSON_GENERAL_POSITION_X    = "x";
QString JSON_GENERAL_POSITION_Y    = "y";

QString JSON_FUNCTIONS  = "functions";

QString JSON_HIERARCHY_TYPE_CATEGORY    = "componentCategory";
QString JSON_HIERARCHY_TYPE_COMPONENT   = "componentType";
QString JSON_HIERARCHY_CATEGORY_NAME    = "name";
QString JSON_HIERARCHY_TYPE      = "hierarchy_type";
QString JSON_HIERARCHY_CHILD    = "child";
QString JSON_HIERARCHY_SOURCE   = "descriptorPath";
QString JSON_PORTS              = "ports";
QString JSON_PORT_DIRECTION     = "direction";
QString JSON_SYMBOL_PATH        = "symbolFile";
QString JSON_CONFIG_BIT_GROUP     = "configBits";
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

QString MIME_COMPONENT_TYPE = "application/component-type";
QString MIME_PORT_PLACEMENT = "application/port-placement";
QString MIME_WIRE_START_POS = "application/wire-start-pos";

QString FILE_COMPONENT_TREE    = "/components.q2tree";
QString EXTENSION_DOCFILE           = ".q2doc";
} // namespace constants
} // namespace q2d
