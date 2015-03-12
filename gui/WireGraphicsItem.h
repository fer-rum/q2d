#ifndef WIREGRAPHICSITEM_H
#define WIREGRAPHICSITEM_H

#include "SchematicElement.h"

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QObject>
#include <QPointF>

namespace q2d {
namespace gui {

class PortGraphicsItem;

/**
 * @brief The WireGraphicsItem class
 * A WireGraphicsItem is composited from one or multiple WireGraphicsLineItem instances.
 * These are created when routing.
 * The start is always (0, 0) in local coordinates.
 */
class WireGraphicsItem :
    public SchematicElement {
    Q_OBJECT
private:

    static QPen PEN_DEFAULT;
    static QPen PEN_HOVER;

    static QBrush BRUSH_DEFAULT;
    static QBrush BRUSH_HOVER;

    static const QPointF m_startPoint;
    QPointF m_endPoint;

    // caches additional Info as JSON
    // maybe not so memory efficient
    QJsonObject m_additionalInfo;

    void addChild(QPointF start, QPointF end);

    // routing algorithms
    void routeLeftToRight();
    void routeStraight();
protected:
    virtual QString specificType();
    virtual QJsonObject additionalJson();
public:

    /**
     * @brief WireGraphicsItem::WireGraphicsItem
     * Internally, the wire starts at (0, 0) in item coordinates.
     *
     * @param start the starting PortGraphicsItem of the wire
     * @param end the ending PortGraphicsItem of the wire
     * @param scene
     */
    WireGraphicsItem(PortGraphicsItem* start, PortGraphicsItem* end, DocumentEntry* relatedEntry);

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
