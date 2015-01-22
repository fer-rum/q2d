#include "PortGraphicsItem.h"

#include "../Constants.h"
#include "../Document.h"
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
QPointF PortGraphicsItem::CENTER_OFFSET = QPointF(RADIUS, RADIUS);

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

bool PortGraphicsItem::m_wireDrawingMode = false;
QGraphicsLineItem*  PortGraphicsItem::m_wireDrawingLineItem = nullptr;
QPointF PortGraphicsItem::m_wireDrawingStart = QPoint();
QPointF PortGraphicsItem::m_wireDrawingEnd = QPoint();
QLineF* PortGraphicsItem::m_wireDrawingLine = nullptr;

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
        QPoint relativeCenterPosition,
        model::PortDirection direction,
        ComponentGraphicsItem *parent)
    : QObject(parent),
      QGraphicsEllipseItem(parent),
      SchematicsSceneChild(parent->SchematicsSceneChild::scene()) {

    Q_CHECK_PTR(parent);
    Q_CHECK_PTR(parent->SchematicsSceneChild::scene());

    this->setPos(relativeCenterPosition.x() - RADIUS,
                  relativeCenterPosition.y() - RADIUS);
    this->setRect(0, 0, DIAMETER, DIAMETER);


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
        m_dragStartPosition = event->scenePos();
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

/**
 * @brief PortGraphicsItem::id is a convenience function
 * @return
 */
QString
PortGraphicsItem::id() const {
    // TODO asserts
    Document* container = m_scene->document();
    return container->entry(this)->id();
}

void
PortGraphicsItem::performDrag() {

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();

    // create the payload

    QString payloadText = this->id();

    mimeData->setData(MIME_WIRE_START_POS, payloadText.toUtf8());

    drag->setMimeData(mimeData);

    m_wireDrawingMode = true;
    m_wireDrawingEnd = QPointF();
    m_wireDrawingLine = new QLineF(QPointF(), m_wireDrawingEnd);
    m_wireDrawingLineItem = m_scene->addLine(*m_wireDrawingLine);
    m_wireDrawingLineItem->setPos(this->mapToScene(RADIUS, RADIUS));
    m_wireDrawingLineItem->setVisible(true);

    // TODO the returned Action should be LINK?
    drag->exec();
}

void
PortGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent* event){
    QMimeData const * mimeData = event->mimeData();

    if(mimeData->hasFormat(MIME_WIRE_START_POS)){
        this->setCursor(QCursor(Qt::CrossCursor));
        this->m_dragOver = true;
        event->accept();
    } else {
        QGraphicsEllipseItem::dragEnterEvent(event);
    }
}

void
PortGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver && m_wireDrawingMode){
            Q_CHECK_PTR(m_wireDrawingLine);
            Q_CHECK_PTR(m_wireDrawingLineItem);
            QPointF itemCoordinate =
                    m_wireDrawingLineItem->mapFromScene(event->scenePos());
            m_wireDrawingLine->setP2(itemCoordinate);
            m_wireDrawingLineItem->setLine(*m_wireDrawingLine);
            event->accept();
            emit m_scene->sceneRectChanged(m_wireDrawingLineItem->boundingRect());
    }
}

void
PortGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent* event){

    if(m_dragOver){
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

    if(m_dragOver && m_wireDrawingMode){
        m_dragOver = false;

        QString senderId = QString::fromUtf8(
                               event->mimeData()->data(MIME_WIRE_START_POS));
        m_scene->document()->addWire(senderId, this->id());

        event->accept();
        this->update(); // TODO better emit this->changed?
    } else {
        QGraphicsEllipseItem::dropEvent(event);
    }

    m_wireDrawingMode = false;
    this->QGraphicsItem::scene()->removeItem(m_wireDrawingLineItem);
}
