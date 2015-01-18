#include "ComponentGraphicsItem.h"

#include "PortGraphicsItem.h"
#include "SchematicsScene.h"
#include "metamodel/ComponentType.h"
#include "metamodel/PortDescriptor.h"

using namespace q2d::gui;
using namespace q2d::metamodel;

ComponentGraphicsItem::ComponentGraphicsItem(ComponentType* type, SchematicsScene* scene, QPoint position) :
    QGraphicsSvgItem(type->symbolPath()) {
    this->parentScene = scene;
    this->setPos(position);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

SchematicsScene*
ComponentGraphicsItem::scene() const {
    return this->parentScene;
}
