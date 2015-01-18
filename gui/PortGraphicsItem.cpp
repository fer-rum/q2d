#include "PortGraphicsItem.h"

#include "../Constants.h"
#include "ComponentGraphicsItem.h"
#include "SchematicsScene.h"

#include <QApplication>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QtDebug>

using namespace q2d::gui;
using namespace q2d::constants;

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

/**
 * @brief PortGraphicsItem::PortGraphicsItem
 * The item will automatically be added to the scene, its parent belongs to.
 *
 * @param text
 * @param relativeCenterPosition is the center position of this instance
 * in coordinates relative to the the center of its parent.
 * @param direction
 * @param parent
 */
PortGraphicsItem::PortGraphicsItem(
        QString text,
        QPoint relativeCenterPosition,
        model::PortDirection direction,
        ComponentGraphicsItem *parent)
    : QObject(parent), QGraphicsEllipseItem(parent) {

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(parent->scene());
    this->m_scene = parent->scene();

    this->setToolTip(text);
    this->setRect(relativeCenterPosition.x() - RADIUS,
                  relativeCenterPosition.y() - RADIUS,
                  DIAMETER, DIAMETER);

    // select the Pen based on the Port direction
    switch(direction){
    case model::PortDirection::IN:
        this->m_defaultPen = INPUT_PORT_PEN;
        this->m_defaultBrush = INPUT_PORT_BRUSH;
        break;
    case model::PortDirection::IN_OUT:
        this->m_defaultPen = IN_OUT_PORT_PEN;
        this->m_defaultBrush = IN_OUT_PORT_BRUSH;
        break;
    case model::PortDirection::OUT:
        this->m_defaultPen = OUTPUT_PORT_PEN;
        this->m_defaultBrush = OUTPUT_PORT_BRUSH;
        break;
    default:
        this->m_defaultPen = UNDEFINED_PORT_PEN;
        this->m_defaultBrush = UNDEFINED_PORT_BRUSH;
        break;
    }

    this->setPen(this->m_defaultPen);
    this->setBrush(this->m_defaultBrush);

    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptDrops(true);
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
    this->setPen(this->m_defaultPen);
    this->setBrush(this->m_defaultBrush);
    this->setCursor(QCursor(Qt::ArrowCursor));
    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void
PortGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
             this->m_dragStartPosition = event->pos();
        event->setAccepted(true);
    } else {
        // propagate event to superclass
        QGraphicsEllipseItem::mousePressEvent(event);
    }
}

void
PortGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    // check if we are dragging something
    if (!(event->buttons() & Qt::LeftButton)) {
             return;
    }
    if ((event->pos() - m_dragStartPosition).manhattanLength()
              < QApplication::startDragDistance()) {
             return;
    }

    this->performDrag();

    // propagate event to superclass
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void
PortGraphicsItem::performDrag() {

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    // create the payload
    QString payloadText = ""; /* TODO */

    mimeData->setData(MIME_WIRE_START_POS, payloadText.toUtf8());

    drag->setMimeData(mimeData);

    this->m_scene->setWireDrawingMode(true, &(this->m_dragStartPosition));
    qDebug() << "Start dragging line from Port";

    // TODO the returned Action should be LINK
    drag->exec();
}

void
PortGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    QMimeData const * mimeData = event->mimeData();

    if(mimeData->hasFormat(MIME_WIRE_START_POS)){
        this->m_dragOver = true;
        event->accept();
        qDebug() << "Port drag enter event";
    } else {
        QGraphicsEllipseItem::dragEnterEvent(event);
    }
}

void
PortGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent* event){

    if(this->m_dragOver){
        qDebug() << "Port drag move event";
        event->accept();
    } else {
        QGraphicsEllipseItem::dragMoveEvent(event);
    }
}

void
PortGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver){
        qDebug() << "Port drag leave event";
        event->accept();
        this->m_dragOver = false;
    } else {
        QGraphicsEllipseItem::dragLeaveEvent(event);
    }
}

void
PortGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent* event){

    // TODO
    // make sure target is not source
    // inform the document about the happenings via signal/slot

    qDebug() << "Port received drop event";

    this->m_dragOver = false;
    this->m_scene->setWireDrawingMode(false);


    this->update(); // TODO better emit this->changed?
    QGraphicsEllipseItem::dropEvent(event);
}
