#include "ComponentDescriptor.h"

#include "../Enumerations.h"
#include "../Util.h"

#include "Category.h"
#include "ConfigurationBitDescriptor.h"
#include "PortDescriptor.h"

#include <QtDebug>
#include <QtSvg/QtSvg>

using namespace q2d::metamodel;

ComponentDescriptor::ComponentDescriptor(QString name,
        Category* parent) :
    HierarchyElement(name, parent) {
    m_instanceIndex = 0;
}

/**
 * @brief ComponentType::setCircuitSymbol sets the circuit symbol from a given svg file
 * and derives an icon from it
 * @param symbolFilePath
 */
void
ComponentDescriptor::loadCircuitSymbol(QString symbolFilePath) {

    QGraphicsSvgItem* symbol = new QGraphicsSvgItem(symbolFilePath);
    Q_CHECK_PTR(symbol);

    // Create Icon for UI from Svg
    QIcon* icon = new QIcon(symbolFilePath);
    Q_CHECK_PTR(icon);
    this->setIcon(*icon);
}

/**
 * @brief ComponentType::symbolPath is a getter for convenience.
 * @return the path to the symbol file
 */
QString
ComponentDescriptor::symbolPath() {
    return this->data((int)ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE).toString();
}

void
ComponentDescriptor::setSymbolPath(QString symbolPath) {
    Q_ASSERT(!(symbolPath.isEmpty()));

    this->setData(QVariant::fromValue(symbolPath), (int)ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
    this->loadCircuitSymbol(symbolPath); // update the circuit symbol
}

/**
 * @brief ComponentType::descriptorPath fetches the absolute path at which the type descriptor file resides.
 * @return
 */
QString
ComponentDescriptor::descriptorPath() const {
    return this->data((int)ComponentDescriptorRole::DESCRIPTOR_FILE).toString();
}

void
ComponentDescriptor::setDescriptorPath(const QString path) {
    Q_ASSERT(!path.isEmpty());
    this->setData(QVariant::fromValue(path), (int)ComponentDescriptorRole::DESCRIPTOR_FILE);
}

// FIXME make sure port names are unique within a component descriptor
void
ComponentDescriptor::addPort(QString name, QPointF relativePosition,
                             q2d::model::enums::PortDirection direction) {
    PortDescriptor* portDescriptor = new PortDescriptor(name, direction, relativePosition, this);
    this->appendRow(portDescriptor);
}

/**
 * @brief ComponentType::addConfigBits adds a group of configuration bit descriptors.
 * @param groupName
 *      must not be empty
 * @param memberCount
 *      must be greater then 0
 */
void
ComponentDescriptor::addConfigBitGroup(ConfigBitGroupDescriptor* configBitGroup) {
    Q_CHECK_PTR(configBitGroup);

    configBitGroup->setParent(this);
    this->appendRow(configBitGroup);

    QString groupName = configBitGroup->name();
    for (unsigned int i = 0; i < configBitGroup->memberCount(); ++i) {
        QString varName = groupName + "_" + util::intToString(i);
        if (m_configVariables.contains(varName)) {
            qWarning() << "Possible duplicate variable name" << varName;
        } else {
            m_configVariables.append(varName);
        }
    }
}

void
ComponentDescriptor::addFunction(QString function) {
    m_functions.append(function);
}

QString
ComponentDescriptor::generateId() {
    QString id = this->text() + QString::number(m_instanceIndex);
    ++m_instanceIndex;
    return id;
}

QStringList
ComponentDescriptor::configVariables() const {
    return m_configVariables;
}

QStringList
ComponentDescriptor::functions() const {
    return m_functions;
}
