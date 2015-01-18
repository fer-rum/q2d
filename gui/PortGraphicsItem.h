#ifndef PORTGRAPHICSITEM_H
#define PORTGRAPHICSITEM_H

#include "../model/PortDirection.h"

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
    class SchematicsScene;

class PortGraphicsItem
        : public QObject,
        public QGraphicsEllipseItem {
    Q_OBJECT

private:
    // TODO make these changeable via the settings
    static int DIAMETER;
    static int RADIUS;

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
    SchematicsScene*    m_scene;

    void performDrag();

public:
    explicit PortGraphicsItem(QString text,
                              QPoint relativeCenterPosition,
                              model::PortDirection direction,
                              ComponentGraphicsItem* parent = 0);

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

signals:

public slots:

};

} // namespace gui
} // namespace q2d

#endif // PORTGRAPHICSITEM_H
