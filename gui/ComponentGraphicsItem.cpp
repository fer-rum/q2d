#include "ComponentGraphicsItem.h"

#include "SchematicsScene.h"

using namespace q2d::gui;

ComponentGraphicsItem::ComponentGraphicsItem(QString file, SchematicsScene* scene, QPoint position) :
    QGraphicsSvgItem(file) {
    this->scene = scene;
    this->setPos(position);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}
