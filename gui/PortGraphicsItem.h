#ifndef PORTGRAPHICSITEM_H
#define PORTGRAPHICSITEM_H

#include "../model/PortDirection.h"
#include "SchematicsSceneChild.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPen>
#include <QPointF>

namespace q2d {
namespace gui {

    // forward declaration
    class ComponentGraphicsItem;

class PortGraphicsItem :
        public QObject,
        public QGraphicsEllipseItem,
        public SchematicsSceneChild {
    Q_OBJECT

private:
    // TODO make these changeable via the settings
    static int DIAMETER;
    static int RADIUS;
    static QPointF CENTER_OFFSET;



    static QPen INPUT_PORT_PEN;
    static QPen IN_OUT_PORT_PEN;
    static QPen OUTPUT_PORT_PEN;
    static QPen UNDEFINED_PORT_PEN;
    static QPen HOVER_PORT_PEN;

    static QBrush INPUT_PORT_BRUSH;
    static QBrush IN_OUT_PORT_BRUSH;
    static QBrush OUTPUT_PORT_BRUSH;
    static QBrush UNDEFINED_PORT_BRUSH;
    static QBrush HOVER_PORT_BRUSH;

    QPen    m_defaultPen;
    QBrush  m_defaultBrush;
    QPointF m_dragStartPosition;

    bool    m_dragOver;
    static bool    m_wireDrawingMode;
    static QGraphicsLineItem*  m_wireDrawingLineItem;
    static QPointF m_wireDrawingStart;
    static QPointF m_wireDrawingEnd;
    static QLineF* m_wireDrawingLine;

    void performDrag();

public:

    static QPointF centerOffset() { return CENTER_OFFSET; }

    explicit PortGraphicsItem(QPoint relativeCenterPosition,
                              model::PortDirection direction,
                              ComponentGraphicsItem* parent);

    // ovverride for custom dragging
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);

    // cosmetic overrides
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    static bool wireDrawingMode();
    static void setWireDrawingMode(bool mode, QPointF* origin = nullptr);

    QString id() const;
signals:

public slots:

};

} // namespace gui
} // namespace q2d

#endif // PORTGRAPHICSITEM_H
