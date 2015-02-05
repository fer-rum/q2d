#include "ConfigurationBitDescriptor.h"

#include "../Application.h"
#include "../Constants.h"
#include "../Util.h"
#include "Type.h"

using namespace q2d::constants;
using namespace q2d::metamodel;


ConfigBitDescriptor::ConfigBitDescriptor(QString name, ConfigBitGroupDescriptor* parent) :
    QObject(parent),
    QStandardItem(name){}

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
ConfigBitGroupDescriptor::ConfigBitGroupDescriptor(QString groupName, int memberCount, metamodel::Type *parent) :
    QObject(parent),
    QStandardItem(groupName + "(" + util::intToString(memberCount) + " bit)") {

    for(int count = 0; count < memberCount; ++count){
        ConfigBitDescriptor* descriptor = new ConfigBitDescriptor(groupName + "_"
                                              + util::intToString(count, 4),
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
