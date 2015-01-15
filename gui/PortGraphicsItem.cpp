#include "PortGraphicsItem.h"

#include <QCursor>

using namespace q2d::gui;

int PortGraphicsItem::DIAMETER = 8;
int PortGraphicsItem::RADIUS = DIAMETER / 2;

QPen PortGraphicsItem::INPUT_PORT_PEN  = QPen(Qt::darkGreen);
QPen PortGraphicsItem::IN_OUT_PORT_PEN = QPen(Qt::darkYellow);
QPen PortGraphicsItem::OUTPUT_PORT_PEN = QPen(Qt::darkRed);
QPen PortGraphicsItem::UNDEFINED_PORT_PEN = QPen(Qt::darkGray);
QPen PortGraphicsItem::HOVER_PORT_PEN = QPen(Qt::darkCyan);


QBrush PortGraphicsItem::INPUT_PORT_BRUSH  = QBrush(Qt::green);
QBrush PortGraphicsItem::IN_OUT_PORT_BRUSH = QBrush(Qt::yellow);
QBrush PortGraphicsItem::OUTPUT_PORT_BRUSH = QBrush(Qt::red);
QBrush PortGraphicsItem::UNDEFINED_PORT_BRUSH = QBrush(Qt::gray);
QBrush PortGraphicsItem::HOVER_PORT_BRUSH = QBrush(Qt::cyan);

PortGraphicsItem::PortGraphicsItem(
        QString text,
        QPoint relativeCenterPosition,
        model::PortDirection direction,
        QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent) {
    this->setToolTip(text);
    this->setRect(relativeCenterPosition.x() - RADIUS,
                  relativeCenterPosition.y() - RADIUS,
                  DIAMETER, DIAMETER);

    // select the Pen based on the Port direction
    switch(direction){
    case model::PortDirection::IN:
        this->defaultPen = INPUT_PORT_PEN;
        this->defaultBrush = INPUT_PORT_BRUSH;
        break;
    case model::PortDirection::IN_OUT:
        this->defaultPen = IN_OUT_PORT_PEN;
        this->defaultBrush = IN_OUT_PORT_BRUSH;
        break;
    case model::PortDirection::OUT:
        this->defaultPen = OUTPUT_PORT_PEN;
        this->defaultBrush = OUTPUT_PORT_BRUSH;
        break;
    default:
        this->defaultPen = UNDEFINED_PORT_PEN;
        this->defaultBrush = UNDEFINED_PORT_BRUSH;
        break;
    }

    this->setPen(this->defaultPen);
    this->setBrush(this->defaultBrush);

    this->setAcceptHoverEvents(true);
}

void
PortGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    this->setPen(HOVER_PORT_PEN);
    this->setBrush(HOVER_PORT_BRUSH);
    QGraphicsEllipseItem::hoverEnterEvent(event);
    this->setCursor(QCursor(Qt::CrossCursor));
}

void
PortGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    this->setPen(this->defaultPen);
    this->setBrush(this->defaultBrush);
    this->setCursor(QCursor(Qt::ArrowCursor));
    QGraphicsEllipseItem::hoverEnterEvent(event);
}
