#include "ConfigurationBitDescriptor.h"

#include "../Application.h"
#include "../Constants.h"
#include "../Util.h"
#include "ComponentDescriptor.h"

using namespace q2d::constants;
using namespace q2d::metamodel;


ConfigBitDescriptor::ConfigBitDescriptor(QString name, ConfigBitGroupDescriptor* parent) :
    ComponentElement(name, parent == nullptr ?
                         nullptr :
                         static_cast<metamodel::ComponentDescriptor*>(parent->parent())){}

/**
 * @brief ConfigBitGroupDescriptor::ConfigBitGroupDescriptor
 * The group will be extended and all concrete ConfigurationBitDescriptors will be created and added as subitems.
 * In the item model, the group forms a new subitem of the ComponentType, containing all members
 * of the group as subitems themself.
 * Group members are named after the group followed by an underscore and a incremental index.
 * @param groupName
 * @param memberCount
 * @param parent
 */
ConfigBitGroupDescriptor::ConfigBitGroupDescriptor(QString groupName, int memberCount, metamodel::ComponentDescriptor *parent) :
    ComponentElement(groupName + "(" + util::intToString(memberCount) + " bit)", parent){

    int maxPadding = QString::number(memberCount).size();

    for(int count = 0; count < memberCount; ++count){
        ConfigBitDescriptor* descriptor = new ConfigBitDescriptor(groupName + "_"
                                              + util::intToString(count, maxPadding),
                                              this);
        this->appendRow(descriptor);
    }

    // fetch the icon for the group
    QString fileName = Application::instance()->getSetting(KEY_FILE_BIT_GROUP).toString();

    if (!fileName.isEmpty()) {
        QIcon icon = QIcon(fileName);
        this->setIcon(icon);
    }
}
