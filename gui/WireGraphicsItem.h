#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include "SchematicsSceneChild.h"
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPointF>

namespace q2d {
namespace gui {

class PortGraphicsItem;

/**
 * @brief The WireGraphicsItem class
 * The start is always (0, 0) in local coordinates.
 */
class WireGraphicsItem :
        public QGraphicsItem,
        public SchematicsSceneChild {
private:
    static const QPointF m_startPoint;
    QPointF m_endPoint;

    QList<QGraphicsLineItem*> m_children;

    // routing algorithms
    void routeLeftToRight();
    void routeStraight();
public:
    WireGraphicsItem(QPointF start, QPointF end, SchematicsScene* scene);
    WireGraphicsItem(PortGraphicsItem* start, PortGraphicsItem* end);

    // overrides
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

    void route();
signals:

public slots:

};

} // namespace gui
} // namespace q2d

#endif // WIREGRAPHICSITEM_H
