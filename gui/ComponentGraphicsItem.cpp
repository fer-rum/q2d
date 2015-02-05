#include "ComponentGraphicsItem.h"

#include "PortGraphicsItem.h"
#include "SchematicsScene.h"
#include "metamodel/Type.h"
#include "metamodel/PortDescriptor.h"

using namespace q2d::gui;
using namespace q2d::metamodel;

ComponentGraphicsItem::ComponentGraphicsItem(metamodel::Type* type,
        SchematicsScene* scene,
        QPointF position)
    : SchematicsSceneChild(scene,
                           new QGraphicsSvgItem(type->symbolPath())) {
    Q_CHECK_PTR(type);
    Q_CHECK_PTR(scene);

    m_type = type;
    this->setPos(position);
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
