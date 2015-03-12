#include "ComponentGraphicsItem.h"
#include "PortGraphicsItem.h"
#include "Schematic.h"

#include "metamodel/ComponentDescriptor.h"
#include "metamodel/PortDescriptor.h"

using namespace q2d::gui;
using namespace q2d::metamodel;

ComponentGraphicsItem::ComponentGraphicsItem(
        QPointF position,
        DocumentEntry* relatedEntry,
        metamodel::ComponentDescriptor* type)
    : SchematicElement(position, relatedEntry) {
    Q_CHECK_PTR(type);

    m_type = type;
    this->addActual(new QGraphicsSvgItem(type->symbolPath()));
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

/**
 * @brief ComponentGraphicsItem::specificType
 * @return the hierarchy name of the type the component was instantiated from.
 */
QString
ComponentGraphicsItem::specificType() {
    return m_type->hierarchyName();
}
