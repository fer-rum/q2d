#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include "SchematicsSceneChild.h"
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QObject>
#include <QPointF>

namespace q2d {
namespace gui {

class PortGraphicsItem;

/**
 * @brief The WireGraphicsItem class
 * The start is always (0, 0) in local coordinates.
 */
class WireGraphicsItem :
        public SchematicsSceneChild {
    Q_OBJECT
private:

    static QPen PEN_DEFAULT;
    static QPen PEN_HOVER;

    static QBrush BRUSH_DEFAULT;
    static QBrush BRUSH_HOVER;

    static const QPointF m_startPoint;
    QPointF m_endPoint;

    void addChild(QPointF start, QPointF end);

    // routing algorithms
    void routeLeftToRight();
    void routeStraight();
protected:
    virtual QString specificType();
public:
    WireGraphicsItem(QPointF start, QPointF end, SchematicsScene* scene);
    WireGraphicsItem(PortGraphicsItem* start, PortGraphicsItem* end);

    // required overrides
    //virtual QRectF boundingRect() const;
    //virtual void paint(QPainter *painter,
    //                   const QStyleOptionGraphicsItem *option,
    //                   QWidget *widget);

    void route();
signals:

public slots:
   void slot_setHovered(bool isHovered);

};

class WireGraphicsLineItem :
        public QGraphicsLineItem {
private:
    WireGraphicsItem* m_parent;
public:
    WireGraphicsLineItem(QPointF start, QPointF end, WireGraphicsItem* parent);

    // cosmetic overrides
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
};

} // namespace gui
} // namespace q2d

#endif // WIREGRAPHICSITEM_H
