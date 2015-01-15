#ifndef PORTGRAPHICSITEM_H
#define PORTGRAPHICSITEM_H

#include "../model/PortDirection.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPen>

namespace q2d {
namespace gui {

class PortGraphicsItem
        : public QGraphicsEllipseItem {
private:
    // TODO make this changeable via the settings
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

    QPen defaultPen;
    QBrush defaultBrush;

public:
    explicit PortGraphicsItem(QString text,
                              QPoint relativeCenterPosition,
                              model::PortDirection direction,
                              QGraphicsItem* parent = 0);

    // cosmetic overrides
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:

public slots:

};

} // namespace gui
} // namespace q2d

#endif // PORTGRAPHICSITEM_H
