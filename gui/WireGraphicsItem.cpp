#include "WireGraphicsItem.h"

#include <QLineF>
#include <QPainter>
#include <QtDebug>

using namespace q2d::gui;

WireGraphicsItem::WireGraphicsItem(
        QPointF start, QPointF end, SchematicsScene* scene) :
    QGraphicsItem(),
    SchematicsSceneChild(scene){
    m_startPoint = start;
    m_endPoint = end;

    this->route();
    this->setVisible(true);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    qDebug() << "Creating WireGraphicsItem";
}

/**
 * @brief WireGraphicsItem::route (re-)creates the wire routing
 * from the start point to the end point of the wire.
 */
void
WireGraphicsItem::route(){

    // TODO improve
    m_children.append(QLineF(m_startPoint, m_endPoint));
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

    painter->drawLines(m_children.toVector());
}
