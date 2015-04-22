#include "ComponentDescriptor.h"

#include "../Constants.h"
#include "../Enumerations.h"
#include "../Util.h"

#include "Category.h"
#include "ConfigurationBitDescriptor.h"
#include "FunctionDescriptor.h"
#include "PortDescriptor.h"

#include <QtDebug>
#include <QtSvg/QtSvg>

using namespace q2d::constants;
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
 * @return the path to the symbol file or an empty string.
 */
QString
ComponentDescriptor::symbolPath() {
    return this->data((int)ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE).toString();
}

void
ComponentDescriptor::setSymbolPath(QString symbolPath) {
    Q_ASSERT(!(symbolPath.isEmpty()));

    if (symbolPath == NO_SYMBOL_FILE) {
        this->setData(QVariant::Invalid, (int)ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
    } else {
        this->setData(QVariant::fromValue(symbolPath),
                      (int)ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
        this->loadCircuitSymbol(symbolPath); // update the circuit symbol
    }
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
void ComponentDescriptor::addPort(PortDescriptor* port) {
    Q_CHECK_PTR(port);
    port->setParent(this);
    this->appendRow(port);
}

QList<PortDescriptor*>
ComponentDescriptor::ports() {

    QList<PortDescriptor*> result = QList<PortDescriptor*>();

    for (QObject * child : this->children()) {
        PortDescriptor* casted = qobject_cast<PortDescriptor*>(child);
        if (casted != nullptr) {
            result.append(casted);
        }
    }

    return result;
}

/**
 * @brief ComponentType::addConfigBits adds a group of configuration bit descriptors.
 * @param groupName
 *      must not be empty
 * @param memberCount
 *      must be greater than 0
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

    // also create a function descripor item
    FunctionDescriptor* funcDes = new FunctionDescriptor(function, this);
    this->appendRow(funcDes);
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

QPoint
ComponentDescriptor::portPosition(QString portName){

    // FIXME this is a hack. Fix, when IDs are re-implemented
    portName = portName.split(HIERARCHY_SEPERATOR).last();

    qDebug() << "Looking for port" << portName;

    for(QObject* child :  this->children()){
        PortDescriptor* port = qobject_cast<PortDescriptor*>(child);
        if(port == nullptr){
            continue;
        }

        qDebug() << "Found port" << port->name();

        if(port->name() == portName){
            return port->position();
        }
    }
    return QPoint();
}
