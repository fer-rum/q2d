#include "WireGraphicsItem.h"

#include "PortGraphicsItem.h"

#include <QLineF>
#include <QPainter>
#include <QtDebug>

using namespace q2d::gui;

QPen WireGraphicsItem::PEN_DEFAULT = QPen(Qt::black, 0);
QPen WireGraphicsItem::PEN_HOVER = QPen(Qt::darkRed, 4);

const QPointF WireGraphicsItem::m_startPoint = QPointF(0, 0);

/**
 * @brief WireGraphicsItem::WireGraphicsItem
 * Internally, the wire starts at (0, 0) in item coordinates.
 *
 * @param start the starting point of the wire in scene coordinates
 * @param end the end point of the wire in scene coordinates
 * @param scene
 */
WireGraphicsItem::WireGraphicsItem(
        QPointF start, QPointF end, SchematicsScene* scene) :
    SchematicsSceneChild(scene){
    qDebug() << "Wire Constructor: start = " << start
                << " end = " << end;

    this->setPos(this->mapFromScene(start));
    m_endPoint = this->mapFromScene(end);
    this->route();
    this->setVisible(true);
    // move this to the background to be overdrawn by the ports
    this->setZValue(-1);
}

WireGraphicsItem::WireGraphicsItem(PortGraphicsItem* start, PortGraphicsItem* end)
    : WireGraphicsItem(
          start->scenePos() + PortGraphicsItem::centerOffset(),
          end->scenePos() + PortGraphicsItem::centerOffset(),
          start->SchematicsSceneChild::scene()){}

/**
 * @brief WireGraphicsItem::addChild is a convenience method
 * for adding child lines and setting them up properly.
 *
 * @param start in item coordinates
 * @param end in item coordinates
 */
void
WireGraphicsItem::addChild(QPointF start, QPointF end){

    QGraphicsLineItem* newLine = new WireGraphicsLineItem(start, end, this);
    this->addActual(newLine);
}

/**
 * @brief WireGraphicsItem::route (re-)creates the wire routing
 * from the start point to the end point of the wire.
 */
void
WireGraphicsItem::route(){

    this->prepareGeometryChange();
    // choose a routing algorithm
    if(m_endPoint.x() > m_startPoint.x()){ // end point right of start)
        this->routeLeftToRight();
        return;
    }

    this->routeStraight();
}

void
WireGraphicsItem:: routeStraight(){

    this->clearActuals();
   this->addChild(m_startPoint, m_endPoint);
    Q_ASSERT(this->countActuals() == 1);
}

void
WireGraphicsItem::routeLeftToRight(){

    this->clearActuals();

    qreal intermediateX = (m_startPoint.x() + m_endPoint.x()) / 2;
    QPointF routingPoint0 = QPointF(intermediateX, m_startPoint.y());
    QPointF routingPoint1 = QPointF(intermediateX, m_endPoint.y());

    this->addChild(m_startPoint, routingPoint0);
    this->addChild(routingPoint0, routingPoint1);
    this->addChild(routingPoint1, m_endPoint);

    Q_ASSERT(this->countActuals() == 3);

}

/**
 * @brief WireGraphicsItem::slot_setHovered should be called if any child is hovered.
 * This will cause all children of this item to change its appearence according to the parameter.
 * @param isHovered
 */
void
WireGraphicsItem::slot_setHovered(bool isHovered){

    if(isHovered){
        for(QGraphicsItem* actual : this->actuals()){
            QGraphicsLineItem* lineActual =
                    dynamic_cast<QGraphicsLineItem*>(actual);
            Q_CHECK_PTR(lineActual);
            lineActual->setPen(PEN_HOVER);
        }
    } else {
        for(QGraphicsItem* actual : this->actuals()){
            QGraphicsLineItem* lineActual =
                    dynamic_cast<QGraphicsLineItem*>(actual);
            Q_CHECK_PTR(lineActual);
            lineActual->setPen(PEN_DEFAULT);
        }
    }
}

WireGraphicsLineItem::WireGraphicsLineItem(
        QPointF start, QPointF end, WireGraphicsItem* parent) :
    QGraphicsLineItem(QLineF(start, end), parent){

    Q_CHECK_PTR(parent);
    m_parent = parent;

    this->setAcceptHoverEvents(true);
}

void
WireGraphicsLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    m_parent->slot_setHovered(true);
    event->accept();
}

void
WireGraphicsLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    m_parent->slot_setHovered(false);
    event->accept();
}
