#include "WireGraphicsItem.h"

#include "PortGraphicsItem.h"

#include <QLineF>
#include <QPainter>
#include <QtDebug>

using namespace q2d::gui;

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
    QGraphicsItem(),
    SchematicsSceneChild(scene){
    qDebug() << "Wire Constructor: start = " << start
                << " end = " << end;

    this->setPos(this->mapFromScene(start));
    m_endPoint = this->mapFromScene(end);
    this->route();
    this->setVisible(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    // move this to the background to be overdrawn by the ports
    this->setZValue(-1);
}

WireGraphicsItem::WireGraphicsItem(PortGraphicsItem* start, PortGraphicsItem* end)
    : WireGraphicsItem(
          start->scenePos() + PortGraphicsItem::centerOffset(),
          end->scenePos() + PortGraphicsItem::centerOffset(),
          start->SchematicsSceneChild::scene()){}

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

    m_children.clear();
    m_children.append(
              new QGraphicsLineItem(QLineF(m_startPoint, m_endPoint), this));
    Q_ASSERT(m_children.count() == 1);
}

void
WireGraphicsItem::routeLeftToRight(){

    m_children.clear();

    qreal intermediateX = (m_startPoint.x() + m_endPoint.x()) / 2;
    QPointF routingPoint0 = QPointF(intermediateX, m_startPoint.y());
    QPointF routingPoint1 = QPointF(intermediateX, m_endPoint.y());

    m_children.append(
              new QGraphicsLineItem(QLineF(m_startPoint, routingPoint0), this));
    m_children.append(
               new QGraphicsLineItem(QLineF(routingPoint0, routingPoint1), this));
    m_children.append(
               new QGraphicsLineItem(QLineF(routingPoint1, m_endPoint), this));

    Q_ASSERT(m_children.count() == 3);

}


QRectF
WireGraphicsItem::boundingRect() const {
    return QRectF(m_startPoint, m_endPoint);
}

void
WireGraphicsItem::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}
