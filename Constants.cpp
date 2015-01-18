#include "Constants.h"

namespace q2d {
namespace constants {

QString HIERARCHY_SEPERATOR    = "/";

QString KEY_COMPONENTS_DIR  = "paths/componentsFolder";
QString KEY_PROJECTS_DIR    = "paths/projectsFolder";

QString KEY_PORT_IN_FILE    = "paths/symbols/port_in";
QString KEY_PORT_OUT_FILE   = "paths/symbols/port_out";
QString KEY_PORT_INOUT_FILE = "paths/symbols/port_inout";

QString JSON_COMPONENT_NAME = "name";
QString JSON_PORTS          = "ports";
QString JSON_PORT_DIRECTION = "direction";
QString JSON_PORT_NAME      = "name";
QString JSON_PORT_POSITION  = "pos";
QString JSON_PORT_POSITION_X    = "x";
QString JSON_PORT_POSITION_Y    = "y";
QString JSON_SYMBOL_PATH    = "symbolFile";

QString MIME_COMPONENT_TYPE = "application/component-type";
QString MIME_WIRE_START_POS = "application/wire-start-pos";
} // namespace constants
} // namespace q2d
