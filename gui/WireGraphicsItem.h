#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include "SchematicsSceneChild.h"
#include <QGraphicsItem>
#include <QGraphicsLineItem>

namespace q2d {
namespace gui {

class WireGraphicsItem :
        public QGraphicsItem,
        public SchematicsSceneChild {
private:
    QPointF m_startPoint;
    QPointF m_endPoint;

    QList<QLineF> m_children;

    void clear();
public:
    explicit WireGraphicsItem(QPointF start, QPointF end, SchematicsScene* scene);

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
