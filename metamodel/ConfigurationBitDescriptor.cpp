#include "ConfigurationBitDescriptor.h"

#include "ComponentType.h"

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
ConfigBitGroupDescriptor::ConfigBitGroupDescriptor(QString groupName, int memberCount, ComponentType *parent) :
    QObject(parent),
    QStandardItem(groupName + "(" + memberCount + " bit)") {

    for(int count = 0; count < memberCount; ++count){
        ConfigBitDescriptor* descriptor = new ConfigBitDescriptor(groupName + "_" + count, this);
        this->appendRow(descriptor);
    }
}
