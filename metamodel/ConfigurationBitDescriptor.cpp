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
                     static_cast<metamodel::ComponentDescriptor*>(parent->parent())) {}

/**
 * @brief ConfigBitGroupDescriptor::ConfigBitGroupDescriptor
 * The group will be extended and all concrete ConfigurationBitDescriptors will be created and added as subitems.
 * In the item model, the group forms a new subitem of the ComponentType, containing all members
 * of the group as subitems themself.
 * Group members are named after the group followed by an underscore and a incremental index.
 * The index is padded with zeroes up to the size of the maximal index length.
 * This is purely for aesthetics.
 * @param groupName
 * @param memberCount
 * @param parent
 */
ConfigBitGroupDescriptor::ConfigBitGroupDescriptor(QString groupName, unsigned int memberCount,
        metamodel::ComponentDescriptor* parent) :
    ComponentElement(groupName + "(" + util::intToString(memberCount) + " bit)", parent) {

    Q_ASSERT(!groupName.isEmpty());
    m_name = groupName;
    m_memberCount = memberCount;

    int maxPadding = QString::number(memberCount).size();

    for (unsigned int count = 0; count < memberCount; ++count) {
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

QString
ConfigBitGroupDescriptor::name() const {
    return m_name;
}

unsigned int
ConfigBitGroupDescriptor::memberCount() const {
    return m_memberCount;
}
