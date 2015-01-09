#include "ComponentType.h"

#include "ComponentCategory.h"

#include <QtDebug>
#include <qt5/QtSvg/QtSvg>

using namespace q2d;

// TODO outsouce some of the calls
/**
 * @brief ComponentType::ComponentType
 *
 * @param descriptionFile
 * @param symbol ; May be null
 *
 * Assumption: name is not empty
 */
ComponentType::ComponentType(QString name, ComponentCategory* parent) :
    ComponentDescriptor(name, parent) {}

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

void
ComponentType::setSymbolPath(QString symbolPath){
    Q_ASSERT(!(symbolPath.isEmpty()));

    this->setData(QVariant::fromValue(symbolPath), ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
    this->loadCircuitSymbol(symbolPath); // update the circuit symbol
}

void
ComponentType::addPort(QString name, QPoint relativePosition, q2d::model::PortDirection direction){
    // TODO implement
    qDebug() << "Creating Port " << name << " at" << relativePosition << " with direction " << direction;
}
