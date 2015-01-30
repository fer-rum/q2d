#include "ComponentType.h"

#include "ComponentCategory.h"
#include "PortDescriptor.h"

#include <QtDebug>
#include <QtSvg/QtSvg>

using namespace q2d::metamodel;

ComponentType::ComponentType(QString name,
                             ComponentCategory* parent) :
    ComponentDescriptor(name, parent) {
    m_instanceIndex = 0;
}

/**
 * @brief ComponentType::setCircuitSymbol sets the circuit symbol from a given svg file
 * and derives an icon from it
 * @param symbolFilePath
 */
void
ComponentType::loadCircuitSymbol(QString symbolFilePath){

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
ComponentType::symbolPath(){
    return this->data(ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE).toString();
}

void
ComponentType::setSymbolPath(QString symbolPath){
    Q_ASSERT(!(symbolPath.isEmpty()));

    this->setData(QVariant::fromValue(symbolPath), ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
    this->loadCircuitSymbol(symbolPath); // update the circuit symbol
}

/**
 * @brief ComponentType::descriptorPath fetches the absolute path at which the type descriptor file resides.
 * @return
 */
QString
ComponentType::descriptorPath() const{
    return this->data(ComponentDescriptorRole::DESCRIPTOR_FILE).toString();
}

void
ComponentType::setDescriptorPath(const QString path){
    Q_ASSERT(!path.isEmpty());
    this->setData(QVariant::fromValue(path), ComponentDescriptorRole::DESCRIPTOR_FILE);
}

void
ComponentType::addPort(QString name, QPoint relativePosition, q2d::model::PortDirection direction){

    qDebug() << "Creating Port " << name
             << " at" << relativePosition
             << " with direction " << direction;

    PortDescriptor* portDescriptor
            = new PortDescriptor(name, direction, relativePosition, this);
    this->appendRow(portDescriptor);
}

QString
ComponentType::generateId(){
    QString id = this->text() + " " + QString::number(m_instanceIndex);
    ++m_instanceIndex;
    return id;
}
